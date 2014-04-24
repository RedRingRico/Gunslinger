#include <GameStateManager.hpp>
#include <System/Time.hpp>
#include <System/Memory.hpp>
#include <System/Debugger.hpp>
#include <GameState.hpp>
#include <cstring>
#include <unistd.h>
#include <GameStateEvents.hpp>
#include <Events.hpp>
#include <GitVersion.hpp>
#include <System/Memory.hpp>

namespace Gunslinger
{
	GameStateManager::GameStateManager( )
	{
		m_Running = ZED_FALSE;
		ZED::System::StartTime( );
		m_StartTime = ZED::System::GetTimeMiS( );
		m_pInputListener = new GameStateInputListener( );
		m_pFont = ZED_NULL;
	}

	GameStateManager::~GameStateManager( )
	{
		zedSafeDelete( m_pFont );
	}

	ZED_UINT32 GameStateManager::Initialise( )
	{
		m_Running = ZED_TRUE;

		m_Text.SetScale( 1.5f );

		m_FrameReset = 0ULL;
		m_FrameCount = 0UL;
		m_DrawFrameRate = ZED_FALSE;

		return ZED_OK;
	}

	ZED_UINT32 GameStateManager::Execute( )
	{
		if( m_GameStateStack.empty( ) )
		{
			this->Quit( );
			return ZED_FAIL;
		}

		static ZED_UINT64 BeginTime = ZED::System::GetTimeMiS( );
		ZED_UINT64 CurrentTimeElapsed = ZED::System::GetTimeMiS( );
		ZED_UINT64 TimeDifference = CurrentTimeElapsed - m_StartTime;
		m_TotalElapsedTime = CurrentTimeElapsed - BeginTime;
		m_StartTime = CurrentTimeElapsed;

		m_GameStateStack.top( )->Update( TimeDifference );
		m_FrameReset += TimeDifference;

		if( m_FrameReset > 1000000ULL )
		{
			m_DrawFrameRate = ZED_TRUE;
			m_FrameReset = 0ULL;
		}

		m_pRenderer->BeginScene( ZED_TRUE, ZED_TRUE, ZED_TRUE );
		m_GameStateStack.top( )->Render( );
		ZED_FLOAT32 XPos = static_cast< ZED_FLOAT32 >( m_WindowWidth ) / 2.0f;
		ZED_FLOAT32 YPos = static_cast< ZED_FLOAT32 >( m_WindowHeight );
		ZED_FLOAT32 StringWidth = 0.0f;
		ZED_FLOAT32 StringHeight = 0.0f;
		m_Text.MeasureString( &StringWidth, &StringHeight,
			"Gunslinger [Ver. %s] //%s",
			GIT_BUILD_VERSION, GIT_TAG_NAME );

		StringWidth /= 2.0f;

		m_Text.Render( XPos - StringWidth, YPos - StringHeight,
			"Gunslinger [Ver. %s] //%s",
			GIT_BUILD_VERSION, GIT_TAG_NAME );

		if( m_DrawFrameRate )
		{
			m_DrawFrameRate = ZED_FALSE;
			m_FrameRate = m_FrameCount;
			m_FrameCount = 0UL;
		}

		ZED_FLOAT32 FPSWidth = 0.0f, FPSHeight = 0.0f;
		m_Text.MeasureString( &FPSWidth, &FPSHeight, "%d", m_FrameRate );

		ZED_FLOAT32 FPSXPosition =
			static_cast< ZED_FLOAT32 >( m_WindowWidth ) - FPSWidth;
		ZED_FLOAT32 FPSYPosition = 0.0f + FPSHeight;

		m_Text.Render( FPSXPosition, FPSYPosition, "%d", m_FrameRate );

		++m_FrameCount;
		m_pRenderer->EndScene( );

		return ZED_OK;
	}

	ZED_UINT32 GameStateManager::RegisterState(
		GameState * const &p_pGameState )
	{
		m_GameStateRegistry.insert( p_pGameState );

		zedTrace( "[Gunslinger::GamestateManager::RegisterState] "
			"<INFO> Added %s\n", p_pGameState->GetName( ) );

		return ZED_OK;
	}

	ZED_UINT32 GameStateManager::GetNumberOfStates( ) const
	{
		return m_GameStateRegistry.size( );
	}

	ZED_CHAR8 *GameStateManager::GetStateName( const ZED_UINT32 p_Index ) const
	{
		if( p_Index > m_GameStateRegistry.size( ) )
		{
			return "\0";
		}

		GameStateSet::const_iterator RegistryIterator =
			m_GameStateRegistry.begin( );

		for( ZED_UINT32 i = 0; i < p_Index; ++i )
		{
			++RegistryIterator;
		}

		return ( *RegistryIterator )->GetName( );
	}

	ZED_UINT32 GameStateManager::ChangeState(
		const ZED_CHAR8 *p_pGameStateName )
	{
		if( this->IsGameStateNameValid( p_pGameStateName ) == ZED_FALSE )
		{
			return ZED_FAIL;
		}

		this->PopState( );
		this->PushState( p_pGameStateName );

		return ZED_OK;
	}

	ZED_UINT32 GameStateManager::PushState( const ZED_CHAR8 *p_pGameStateName )
	{
		if( this->IsGameStateNameValid( p_pGameStateName ) == ZED_FALSE )
		{
			return ZED_FAIL;
		}

		GameStateSet::const_iterator RegistryIterator =
			m_GameStateRegistry.begin( );

		for( ; RegistryIterator != m_GameStateRegistry.end( );
			++RegistryIterator )
		{
			if( strcmp( ( *RegistryIterator )->GetName( ),
				p_pGameStateName ) == 0 )
			{
				break;
			}
		}
		
		m_GameStateStack.push( ( *RegistryIterator ) );

		if( m_GameStateStack.top( )->Enter( ) != ZED_OK )
		{
			this->PopState( );
			return ZED_FAIL;
		}

		m_GameStateStack.top( )->GetEventRouter( )->Add( m_pInputListener,
			KeyboardInputEventType );
		m_GameStateStack.top( )->GetEventRouter( )->Add( m_pInputListener,
			MousePositionInputEventType );
		m_GameStateStack.top( )->GetEventRouter( )->Add( m_pInputListener,
			ResolutionChangeEventType );

		return ZED_OK;
	}

	ZED_UINT32 GameStateManager::PopState( )
	{
		if( !m_GameStateStack.empty( ) )
		{
			m_GameStateStack.pop( );
		}

		return ZED_OK;
	}

	ZED_UINT32 GameStateManager::SetInputBinder(
		ZED::Utility::InputBinder * const &p_pInputBinder )
	{
		if( p_pInputBinder )
		{
			m_pInputListener->SetInputBinder( p_pInputBinder );
			return ZED_OK;
		}

		return ZED_FAIL;
	}

	void GameStateManager::Quit( )
	{
		while( !m_GameStateStack.empty( ) )
		{
			this->PopState( );
		}

		m_Running = ZED_FALSE;
	}

	ZED_BOOL GameStateManager::Running( ) const
	{
		return m_Running;
	}

	ZED::Renderer::Renderer * const GameStateManager::GetRenderer( )
	{
		return m_pRenderer;		
	}

	ZED_UINT32 GameStateManager::SetRenderer(
		ZED::Renderer::Renderer * const &p_pRenderer )
	{
		if( p_pRenderer )
		{
			m_pRenderer = p_pRenderer;
			m_pFont = new ZED::Renderer::GLFont(
				GameStateManager::GetInstance( ).GetRenderer( ) );

			if( m_pFont->Load( "test.zed" ) != ZED_OK )
			{
				zedTrace( "Failed to open test.zed\n" );
				return ZED_FAIL;
			}

			m_pFont->SetViewport( 0.0f, 0.0f,
				static_cast< ZED_FLOAT32 >( m_WindowWidth ),
				static_cast< ZED_FLOAT32 >( m_WindowHeight ) );

			m_Text.SetFont( m_pFont );

			return ZED_OK;
		}

		return ZED_FAIL;
	}

	GameStateManager &GameStateManager::GetInstance( )
	{
		static GameStateManager Instance;

		return Instance;
	}

	ZED_FLOAT64 GameStateManager::GetTotalElapsedTimeAsFloat64( ) const
	{
		return static_cast< ZED_FLOAT64 >( m_TotalElapsedTime ) *
			OneOverMillion;
	}

	ZED_UINT64 GameStateManager::GetTotalElapsedTimeAsUInt64( ) const
	{
		return m_TotalElapsedTime;
	}

	ZED_BOOL GameStateManager::IsGameStateNameValid(
		const ZED_CHAR8 *p_pGameStateName ) const
	{
		GameStateSet::const_iterator RegistryItr =
			m_GameStateRegistry.begin( );

		for( ; RegistryItr != m_GameStateRegistry.end( ); ++RegistryItr )
		{
			if( strcmp( ( *RegistryItr )->GetName( ), p_pGameStateName ) == 0 )
			{
				return ZED_TRUE;
			}
		}

		return ZED_FALSE;
	}

	void GameStateManager::SetWindowDimensions( const ZED_UINT32 p_Width,
		const ZED_UINT32 p_Height )
	{
		m_WindowWidth = p_Width;
		m_WindowHeight = p_Height;
	}
}

