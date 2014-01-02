#include <GameStateManager.hpp>
#include <System/Time.hpp>
#include <GameState.hpp>
#include <cstring>

namespace Gunslinger
{
	GameStateManager::GameStateManager( )
	{
		m_Running = ZED_FALSE;
		ZED::System::StartTime( );
		m_StartTime = ZED::System::GetTimeMiS( );
	}

	GameStateManager::~GameStateManager( )
	{
	}

	ZED_UINT32 GameStateManager::Initialise( )
	{
		return ZED_OK;
	}

	ZED_UINT32 GameStateManager::Execute( )
	{
		if( m_GameStateStack.empty( ) )
		{
			this->Quit( );
			return ZED_FAIL;
		}

		ZED_UINT64 CurrentTimeElapsed = ZED::System::GetTimeMiS( );
		ZED_UINT64 TimeDifference = CurrentTimeElapsed - m_StartTime;
		m_StartTime = CurrentTimeElapsed;

		m_GameStateStack.top( )->Update( TimeDifference );
		m_GameStateStack.top( )->Render( );

		return ZED_OK;
	}

	ZED_UINT32 GameStateManager::RegisterState(
		GameState * const &p_pGameState )
	{
		m_GameStateRegistry.insert( p_pGameState );

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

	GameStateManager &GameStateManager::GetInstance( )
	{
		static GameStateManager Instance;

		return Instance;
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
}

