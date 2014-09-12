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
#include <Renderer/OGL/GLFont.hpp>
#include <Game/GameState.hpp>
#include <cstring>

namespace Gunslinger
{
	GameStateManager::GameStateManager( ) :
		m_RenderFPS( ZED_FALSE ),
		m_RenderFrameTime( ZED_FALSE ),
		m_RenderBuildInfo( ZED_FALSE ),
		m_RenderBeatTime( ZED_FALSE ),
		m_RenderElapsedTime( ZED_FALSE ),
		m_pOverlayFont( ZED_NULL ),
		m_WindowWidth( 0 ),
		m_WindowHeight( 0 )
	{
	}

	GameStateManager::~GameStateManager( )
	{
		zedSafeDelete( m_pOverlayFont );
	}

	ZED_UINT32 GameStateManager::Initialise( )
	{
		zedTrace( "GameStateManager: Initialise\n" );
		if( ZED::Game::GameStateManager::Initialise( ) != ZED_OK )
		{
			zedTrace( "[Gunslinger::GameStateManager::Initiailse] <ERROR> "
				"Failed to initialise the base Game State Manager\n" );
			return ZED_FAIL;
		}

		if( !m_pRenderer )
		{
			zedTrace( "[Gunslinger::GameStateManager::Initialise] <ERROR> "
				"Renderer not yet set\n" );
			return ZED_FAIL;
		}

		m_pOverlayFont = new ZED::Renderer::GLFont(
			GameStateManager::GetInstance( ).GetRenderer( ) );

		ZED_CHAR8 *pFontFile = new ZED_CHAR8[ ZED_MAX_PATH ];

		if( m_pOverlayFont->Load( "test.zed" ) != ZED_OK )
		{
			zedSafeDeleteArray( pFontFile );
			zedTrace( "Failed to open test.zed\n" );
			return ZED_FAIL;
		}

		zedSafeDeleteArray( pFontFile );

		zedTrace( "Loaded font: \"test.zed\"\n" );

		m_pOverlayFont->SetViewport( 0.0f, 0.0f,
			static_cast< ZED_FLOAT32 >( m_WindowWidth ),
			static_cast< ZED_FLOAT32 >( m_WindowHeight ) );

		m_OverlayText.SetFont( m_pOverlayFont );

		m_Running = ZED_TRUE;

		m_OverlayText.SetScale( 1.0f );

		m_FrameReset = 0ULL;
		m_FrameCount = 0UL;
		m_DrawFrameRate = ZED_FALSE;

		return ZED_OK;
	}

	ZED_UINT32 GameStateManager::Update( const ZED_UINT64 p_DeltaTime )
	{
		m_GameStateStack.top( )->Update( p_DeltaTime );
		m_FrameReset += p_DeltaTime;
		if( m_FrameReset > 1000000ULL )
		{
			m_DrawFrameRate = ZED_TRUE;
			m_FrameReset = 0ULL;
		}

		return ZED_OK;		
	}

	ZED_UINT32 GameStateManager::Render( )
	{
		ZED_UINT64 StartFrameTime = ZED::System::GetTimeMiS( );

		m_GameStateStack.top( )->Render( );

		if( m_DrawFrameRate )
		{
			m_DrawFrameRate = ZED_FALSE;
			m_FrameRate = m_FrameCount;
			m_FrameCount = 0UL;
		}

		if( m_RenderBuildInfo )
		{
			if( this->RenderBuildInfo( ) != ZED_OK )
			{
				return ZED_FAIL;
			}
		}

		if( m_RenderElapsedTime )
		{
			if( this->RenderElapsedTime( ) != ZED_OK )
			{
				return ZED_FAIL;
			}
		}

		if( m_RenderBeatTime )
		{
			if( this->RenderBeatTime( ) != ZED_OK )
			{
				return ZED_FAIL;
			}
		}

		if( m_RenderFPS )
		{
			if( this->RenderFPS( ) != ZED_OK )
			{
				return ZED_FAIL;
			}
		}

		++m_FrameCount;

		ZED_UINT64 TotalFrameTime = ZED::System::GetTimeMiS( ) -
			StartFrameTime;

		if( m_RenderFrameTime )
		{
			if( this->RenderFrameTime( TotalFrameTime ) != ZED_OK )
			{
				return ZED_FAIL;
			}
		}

		return ZED_OK;
	}

	GameStateManager &GameStateManager::GetInstance( )
	{
		static GameStateManager Instance;

		return Instance;
	}

	void GameStateManager::SetWindowDimensions( const ZED_UINT32 p_Width,
		const ZED_UINT32 p_Height )
	{
		m_WindowWidth = p_Width;
		m_WindowHeight = p_Height;

		if( m_pOverlayFont )
		{
			m_pOverlayFont->SetViewport( 0.0f, 0.0f,
				static_cast< ZED_FLOAT32 >( m_WindowWidth ),
				static_cast< ZED_FLOAT32 >( m_WindowHeight ) );
		}
	}

	void GameStateManager::ShowFPS( )
	{
		m_RenderFPS = ZED_TRUE;
	}

	void GameStateManager::HideFPS( )
	{
		m_RenderFPS = ZED_FALSE;
	}

	void GameStateManager::ShowFrameTime( )
	{
		m_RenderFrameTime = ZED_TRUE;
	}

	void GameStateManager::HideFrameTime( )
	{
		m_RenderFrameTime = ZED_FALSE;
	}

	void GameStateManager::ShowBuildInfo( )
	{
		m_RenderBuildInfo = ZED_TRUE;
	}

	void GameStateManager::HideBuildInfo( )
	{
		m_RenderBuildInfo = ZED_FALSE;
	}

	void GameStateManager::ShowBeatTime( )
	{
		m_RenderBeatTime = ZED_TRUE;
	}

	void GameStateManager::HideBeatTime( )
	{
		m_RenderBeatTime = ZED_FALSE;
	}

	void GameStateManager::ShowElapsedTime( )
	{
		m_RenderElapsedTime = ZED_TRUE;
	}

	void GameStateManager::HideElapsedTime( )
	{
		m_RenderElapsedTime = ZED_FALSE;
	}

	void GameStateManager::ShowAllOverlays( )
	{
		m_RenderFPS = ZED_TRUE;
		m_RenderFrameTime = ZED_TRUE;
		m_RenderBuildInfo = ZED_TRUE;
		m_RenderBeatTime = ZED_TRUE;
		m_RenderElapsedTime = ZED_TRUE;
	}

	void GameStateManager::HideAllOverlays( )
	{
		m_RenderFPS = ZED_FALSE;
		m_RenderFrameTime = ZED_FALSE;
		m_RenderBuildInfo = ZED_FALSE;
		m_RenderBeatTime = ZED_FALSE;
		m_RenderElapsedTime = ZED_FALSE;
	}

	ZED_UINT32 GameStateManager::RenderFPS( )
	{
		ZED_FLOAT32 FPSWidth = 0.0f, FPSHeight = 0.0f;
		m_OverlayText.MeasureString( &FPSWidth, &FPSHeight, "[%d]",
			m_FrameRate );

		ZED_FLOAT32 FPSXPosition =
			static_cast< ZED_FLOAT32 >( m_WindowWidth ) - FPSWidth;
		ZED_FLOAT32 FPSYPosition = 0.0f + FPSHeight;

		ZED_COLOUR TextColour;
		TextColour.Alpha = 1.0f;

		if( m_FrameRate >= 30 )
		{
			TextColour.Red = 0.0f;
			TextColour.Green = 1.0f;
			TextColour.Blue = 0.0f;
		}
		else if( m_FrameRate >= 15 )
		{
			TextColour.Red = 1.0f;
			TextColour.Green = 1.0f;
			TextColour.Blue = 0.0f;
		}
		else
		{
			TextColour.Red = 1.0f;
			TextColour.Green = 0.0f;
			TextColour.Blue = 0.0f;
		}

		m_pOverlayFont->SetForegroundColour( TextColour );

		m_OverlayText.Render( FPSXPosition, FPSYPosition, "[%d]",
			m_FrameRate );

		return ZED_OK;
	}

	ZED_UINT32 GameStateManager::RenderFrameTime(
		const ZED_UINT64 p_FrameTime )
	{
		ZED_FLOAT32 FrameTimeXPos =
			static_cast< ZED_FLOAT32 >( m_WindowWidth );

		ZED_FLOAT32 FrameTimeYPos = 0.0f;

		ZED_FLOAT32 FrameTimeWidth = 0.0f, FrameTimeHeight = 0.0f;

		m_OverlayText.MeasureString( &FrameTimeWidth, &FrameTimeHeight,
			"(%lluus)", p_FrameTime );

		FrameTimeXPos -= FrameTimeWidth;

		FrameTimeYPos += FrameTimeHeight;

		if( m_RenderFPS )
		{
			FrameTimeYPos += FrameTimeHeight;
		}

		ZED_COLOUR TextColour = { 1.0f, 1.0f, 1.0f, 1.0f };
		
		m_pOverlayFont->SetForegroundColour( TextColour );

		m_OverlayText.Render( FrameTimeXPos, FrameTimeYPos, "(%lluus)",
			p_FrameTime );

		return ZED_OK;
	}

	ZED_UINT32 GameStateManager::RenderBuildInfo( )
	{
		ZED_FLOAT32 XPos = static_cast< ZED_FLOAT32 >( m_WindowWidth ) / 2.0f;
		ZED_FLOAT32 YPos = static_cast< ZED_FLOAT32 >( m_WindowHeight );
		ZED_FLOAT32 StringWidth = 0.0f;
		ZED_FLOAT32 StringHeight = 0.0f;
		m_OverlayText.MeasureString( &StringWidth, &StringHeight,
			"Gunslinger [Ver. %s] %s//%s",
			GIT_BUILD_VERSION,
#if defined ZED_BUILD_DEBUG
				"DEBUG",
#elif defined ZED_BUILD_RELEASE
				"RELEASE",
#elif defined ZED_BUILD_PROFILE
				"PROFILE",
#else
#error Unknown platform
#endif
			GIT_TAG_NAME );

		StringWidth /= 2.0f;

		ZED_COLOUR TextColour = { 1.0f, 1.0f, 1.0f, 1.0f };

		m_pOverlayFont->SetForegroundColour( TextColour );

		m_OverlayText.Render( XPos - StringWidth, YPos - StringHeight,
			"Gunslinger [Ver. %s] %s//%s",
			GIT_BUILD_VERSION,
			#if defined ZED_BUILD_DEBUG
				"DEBUG",
#elif defined ZED_BUILD_RELEASE
				"RELEASE",
#elif defined ZED_BUILD_PROFILE
				"PROFILE",
#else
#error Unknown platform
#endif
			GIT_TAG_NAME );

		return ZED_OK;
	}

	ZED_UINT32 GameStateManager::RenderBeatTime( )
	{
		ZED_FLOAT32 BeatTimeXPos = 0.0f;
		ZED_FLOAT32 BeatTimeYPos =
			static_cast< ZED_FLOAT32 >( m_WindowHeight );
		ZED_FLOAT32 BeatTimeWidth = 0.0f, BeatTimeHeight = 0.0f;
		ZED::System::BEAT_TIME BeatTime;

		if( ZED::System::GetBeatTime( BeatTime ) != ZED_OK )
		{
			return ZED_FAIL;
		}

		m_OverlayText.MeasureString( &BeatTimeWidth, &BeatTimeHeight, "@%03d",
			BeatTime.Beat );

		BeatTimeYPos -= BeatTimeHeight;

		ZED_COLOUR TextColour = { 1.0f, 1.0f, 1.0f, 1.0f };
		m_pOverlayFont->SetForegroundColour( TextColour );

		m_OverlayText.Render( BeatTimeXPos, BeatTimeYPos, "@%03d", BeatTime.Beat );

		ZED_FLOAT32 CentiBeatXPos = BeatTimeWidth;
		ZED_FLOAT32 CentiBeatYPos = BeatTimeYPos;

		ZED_FLOAT32 DotAdvance = 0.0f;

		ZED_FLOAT32 DotWidth, DotHeight;
		m_OverlayText.MeasureString( &DotWidth, &DotHeight, "." );

		TextColour = { 0.0f, 1.0f, 0.0f, 1.0f };
		m_pOverlayFont->SetForegroundColour( TextColour );

		for( ZED_UINT32 i = 0; i < BeatTime.CentiBeat; ++i )
		{
			m_OverlayText.Render( CentiBeatXPos + DotAdvance, CentiBeatYPos, "." );

			DotAdvance += DotWidth;
		}

		return ZED_OK;
	}

	ZED_UINT32 GameStateManager::RenderElapsedTime( )
	{
		static ZED_UINT64 MaxUInt64 = 0xFFFFFFFFFFFFFFFF;
		ZED_FLOAT32 TotalTimeXPos =
			static_cast< ZED_FLOAT32 >( m_WindowWidth );
		ZED_FLOAT32 TotalTimeYPos =
			static_cast< ZED_FLOAT32 >( m_WindowHeight );

		ZED_FLOAT32 TotalTimeWidth = 0.0f, TotalTimeHeight = 0.0f;
		m_OverlayText.MeasureString( &TotalTimeWidth, &TotalTimeHeight,
			"Elapsed Time: %lluus", m_TotalElapsedTime );

		TotalTimeXPos -= TotalTimeWidth;
		TotalTimeYPos -= TotalTimeHeight;

		ZED_COLOUR TextColour = { 1.0f, 1.0f, 1.0f, 1.0f };

		m_pOverlayFont->SetForegroundColour( TextColour );

		m_OverlayText.Render( TotalTimeXPos, TotalTimeYPos, "Elapsed Time: %lluus",
			m_TotalElapsedTime );

		TotalTimeXPos = static_cast< ZED_FLOAT32 >( m_WindowWidth );
		m_OverlayText.MeasureString( &TotalTimeWidth, ZED_NULL, "Time until "
			"wrap-around: %lluus", MaxUInt64 - m_TotalElapsedTime );

		TotalTimeXPos -= TotalTimeWidth;

		m_OverlayText.Render( TotalTimeXPos,
			TotalTimeYPos - ( TotalTimeHeight * 1.2f ),
			"Time until wrap-around: %lluus",
			MaxUInt64 - m_TotalElapsedTime );

		return ZED_OK;
	}
}

