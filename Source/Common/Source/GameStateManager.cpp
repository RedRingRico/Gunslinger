#include <GameStateManager.hpp>
#include <System/Time.hpp>
#include <GameState.hpp>

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

	ZED_UINT32 GameStateManager::ChangeState( const ZED_CHAR8 *p_pStateName )
	{
		return ZED_OK;
	}

	ZED_UINT32 GameStateManager::PushState( const ZED_CHAR8 *p_pStateName )
	{
		return ZED_OK;
	}

	ZED_UINT32 GameStateManager::PopState( )
	{
		return ZED_OK;
	}

	void GameStateManager::Quit( )
	{
		for( ZED_MEMSIZE i = 0; i < m_GameStateStack.size( ); ++i )
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
}

