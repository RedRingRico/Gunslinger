#include <GameStateEvents.hpp>
#include <Events.hpp>
#include <Utility/EventRouter.hpp>

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
		if( p_Event.Type( ).ID( ) == KeyboardInputEventType.ID( ) )
		{
			if( m_pInputBinder )
			{
				KeyboardInputEventData *pKeyboardData =
					p_Event.Data< KeyboardInputEventData >( );

				ZED_KEY Key;
				ZED_BOOL KeyState = ZED_FALSE;

				pKeyboardData->GetState( Key, KeyState );

				ZED_UINT32 ActionID;
				ActionID = m_pInputBinder->GetActionFromKey( Key );

				if( ActionID != 0 )
				{
					ZED_FLOAT32 ActionValue = KeyState ? 1.0f : 0.0f;
					ActionInputEventData ActionData;
					ActionData.SetAction( ActionID, ActionValue );
					ActionInputEvent Action( &ActionData );

					ZED::Utility::SendEvent( Action );

					return ZED_TRUE;
				}
			}
		}
		
		return ZED_FALSE;
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

