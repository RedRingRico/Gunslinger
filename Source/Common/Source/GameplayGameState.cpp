#include <GameplayGameState.hpp>

namespace Gunslinger
{
	GameplayGameState::GameplayGameState( )
	{
	}

	GameplayGameState::~GameplayGameState( )
	{
	}

	ZED_UINT32 GameplayGameState::Enter( )
	{
		return ZED_OK;
	}

	void GameplayGameState::Render( )
	{
	}

	void GameplayGameState::Update( const ZED_UINT64 p_ElapsedTime )
	{
	}

	ZED_UINT32 GameplayGameState::Exit( )
	{
		return ZED_OK;
	}

	ZED_CHAR8 *GameplayGameState::GetName( ) const
	{
		return "Gameplay";
	}
}

