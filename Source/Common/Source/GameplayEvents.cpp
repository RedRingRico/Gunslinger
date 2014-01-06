#include <GameplayEvents.hpp>
#include <GameplayGameState.hpp>
#include <Events.hpp>
#include <Actions.hpp>
#include <Arithmetic/Arithmetic.hpp>
#include <Arithmetic/Vector3.hpp>
#include <System/Debugger.hpp>

namespace Gunslinger
{
	GameplayInputListener::GameplayInputListener( ) :
		m_pGameplayGameState( ZED_NULL )
	{
	}

	GameplayInputListener::~GameplayInputListener( )
	{
	}

	ZED_BOOL GameplayInputListener::HandleEvent(
		const ZED::Utility::Event &p_Event )
	{
		if( p_Event.Type( ).ID( ) == ActionInputEventType.ID( ) )
		{
			ActionInputEventData *pActionData =
				p_Event.Data< ActionInputEventData >( );

			ZED_UINT32 Action = 0;
			ZED_FLOAT32 ActionValue = 0.0f;

			pActionData->GetAction( Action, ActionValue );

			switch( Action )
			{
				case STATE_EXIT:
				{
					if( ZED::Arithmetic::Equal( ActionValue, 1.0f ) )
					{
						m_pGameplayGameState->Exit( );
					}

					return ZED_TRUE;
				}

				case DEBUG_CAMERA_MOVE_UP:
				{
					ZED::Arithmetic::Vector3 Up( 0.0f, ActionValue, 0.0f );
					m_pGameplayGameState->GetDebugCamera( )->Move( Up );
					return ZED_TRUE;
				}

				case DEBUG_CAMERA_MOVE_DOWN:
				{
					ZED::Arithmetic::Vector3 Down( 0.0f, -ActionValue, 0.0f );
					m_pGameplayGameState->GetDebugCamera( )->Move( Down );
					return ZED_TRUE;
				}

				default:
				{
					return ZED_FALSE;
				}
			}
		}

		return ZED_FALSE;
	}

	ZED_CHAR8 *GameplayInputListener::Name( ) const
	{
		return "Gameplay Input Listener";
	}

	ZED_UINT32 GameplayInputListener::SetGameplayGameState(
		GameplayGameState * const &p_pGameplayGameState )
	{
		if( p_pGameplayGameState )
		{
			m_pGameplayGameState = p_pGameplayGameState;
			return ZED_OK;
		}
		
		return ZED_FAIL;
	}
}

