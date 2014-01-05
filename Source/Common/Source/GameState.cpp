#include <GameState.hpp>

namespace Gunslinger
{
	GameState::~GameState( )
	{
	}

	ZED::Utility::EventRouter * const GameState::GetEventRouter( )
	{
		return m_pEventRouter;
	}
}

