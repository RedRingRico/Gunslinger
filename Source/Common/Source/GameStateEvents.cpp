#include <GameStateEvents.hpp>

namespace Gunslinger
{
	GameStateInputListener::GameStateInputListener( )
	{
		m_pInputBinder = ZED_NULL;
	}

	GameStateInputListener::~GameStateInputListener( )
	{
	}

	ZED_BOOL GameStateInputListener::HandleEvent(
		const ZED::Utility::Event &p_Event )
	{
		return ZED_TRUE;
	}

	ZED_CHAR8 *GameStateInputListener::Name( ) const
	{
		return "GameStateInputListener";
	}

	ZED_UINT32 GameStateInputListener::SetInputBinder(
		ZED::Utility::InputBinder * const &p_pInputBinder )
	{
		m_pInputBinder = p_pInputBinder;

		return ZED_OK;
	}
}

