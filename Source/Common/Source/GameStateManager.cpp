#include <GameStateManager.hpp>

namespace Gunslinger
{
	GameStateManager::GameStateManager( )
	{
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
		return ZED_OK;
	}

	ZED_UINT32 GameStateManager::RegisterState(
		GameState * const &p_GameState )
	{
		return ZED_OK;
	}

	ZED_UINT32 GameStateManager::GetNumberOfStates( ) const
	{
		return 0;
	}

	ZED_CHAR8 *GameStateManager::GetStateName( const ZED_UINT32 p_Index ) const
	{
		return "NULL";
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

	GameStateManager &GameStateManager::GetInstance( )
	{
		static GameStateManager Instance;

		return Instance;
	}
}

