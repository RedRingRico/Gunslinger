#include <GameplayEvents.hpp>
#include <GameplayGameState.hpp>
#include <Events.hpp>
#include <Actions.hpp>
#include <Arithmetic/Arithmetic.hpp>
#include <Arithmetic/Vector3.hpp>
#include <System/Debugger.hpp>

const ZED_FLOAT32 MaxSpeed = 5.0f;
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
				case DEBUG_CAMERA_TOGGLE:
				{
					// This still toggles quickly as there is no state checking
					// of the previous state with this one
					if( ZED::Arithmetic::Equal( ActionValue, 1.0f ) )
					{
						m_pGameplayGameState->ToggleDebugCamera( );
					}

					return ZED_TRUE;
				}

				case PLAYER_MOVE_FORWARD:
				{
					m_pGameplayGameState->GetPlayerCamera( )->Move(
						ZED::Arithmetic::Vector3(
							0.0f, 0.0f, ActionValue * MaxSpeed ) );

					return ZED_TRUE;
				}

				case PLAYER_MOVE_BACKWARD:
				{
					m_pGameplayGameState->GetPlayerCamera( )->Move(
						ZED::Arithmetic::Vector3(
							0.0f, 0.0f, -ActionValue * MaxSpeed ) );

					return ZED_TRUE;
				}

				case PLAYER_MOVE_LEFT:
				{
					m_pGameplayGameState->GetPlayerCamera( )->Move(
						ZED::Arithmetic::Vector3(
							-ActionValue * MaxSpeed, 0.0f, 0.0f ) );

					return ZED_TRUE;
				}

				case PLAYER_MOVE_RIGHT:
				{
					m_pGameplayGameState->GetPlayerCamera( )->Move(
						ZED::Arithmetic::Vector3(
							ActionValue * MaxSpeed, 0.0f, 0.0f ) );

					return ZED_TRUE;
				}

				default:
				{
					break;
				}
			}


			if( m_pGameplayGameState->DebugCameraActive( ) == ZED_TRUE )
			{
				switch( Action )
				{
					case DEBUG_CAMERA_MOVE_UP:
					{
						m_pGameplayGameState->GetDebugCamera( )->Move(
							ZED::Arithmetic::Vector3(
								0.0f, ActionValue * MaxSpeed, 0.0f ) );
						return ZED_TRUE;
					}

					case DEBUG_CAMERA_MOVE_DOWN:
					{
						m_pGameplayGameState->GetDebugCamera( )->Move(
							ZED::Arithmetic::Vector3(
								0.0f, -ActionValue * MaxSpeed, 0.0f ) );
						return ZED_TRUE;
					}

					case DEBUG_CAMERA_MOVE_FORWARD:
					{
						m_pGameplayGameState->GetDebugCamera( )->Move(
							ZED::Arithmetic::Vector3(
								0.0f, 0.0f, ActionValue * MaxSpeed ) );
						return ZED_TRUE;
					}

					case DEBUG_CAMERA_MOVE_BACKWARD:
					{
						m_pGameplayGameState->GetDebugCamera( )->Move(
							ZED::Arithmetic::Vector3(
								0.0f, 0.0f, -ActionValue * MaxSpeed ) );
						return ZED_TRUE;
					}

					case DEBUG_CAMERA_MOVE_LEFT:
					{
						m_pGameplayGameState->GetDebugCamera( )->Move(
							ZED::Arithmetic::Vector3(
								-ActionValue * MaxSpeed, 0.0f, 0.0f ) );
						return ZED_TRUE;
					}

					case DEBUG_CAMERA_MOVE_RIGHT:
					{
						m_pGameplayGameState->GetDebugCamera( )->Move(
							ZED::Arithmetic::Vector3(
								ActionValue * MaxSpeed, 0.0f, 0.0f ) );
						return ZED_TRUE;
					}

					case DEBUG_CAMERA_LOOK_UP:
					{
						m_pGameplayGameState->GetDebugCamera( )->Rotate(
							0.002f, 
							ZED::Arithmetic::Vector3(1.0f, 0.0f, 0.0f ) );
						return ZED_TRUE;
					}

					case DEBUG_CAMERA_LOOK_DOWN:
					{
						m_pGameplayGameState->GetDebugCamera( )->Rotate(
							-0.002f,
							ZED::Arithmetic::Vector3( 1.0f, 0.0f, 0.0f ) );
						return ZED_TRUE;
					}

					case DEBUG_CAMERA_LOOK_LEFT:
					{
						m_pGameplayGameState->GetDebugCamera( )->Rotate(
							0.002f,
							ZED::Arithmetic::Vector3( 0.0f, 1.0f, 0.0f ) );
						return ZED_TRUE;
					}

					case DEBUG_CAMERA_LOOK_RIGHT:
					{
						m_pGameplayGameState->GetDebugCamera( )->Rotate(
							-0.002f,
							ZED::Arithmetic::Vector3( 0.0f, 1.0f, 0.0f ) );
						return ZED_TRUE;
					}
				
					default:
					{
						break;
					}
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

