#include <GameplayEvents.hpp>
#include <GameplayGameState.hpp>
#include <Events.hpp>
#include <Actions.hpp>
#include <Arithmetic/Arithmetic.hpp>
#include <Arithmetic/Vector3.hpp>
#include <System/Debugger.hpp>

const ZED_FLOAT32 MaxSpeed = 5.0f;
const ZED_FLOAT32 MaxHorizontalLookSpeed = 0.5f;
const ZED_FLOAT32 MaxVerticalLookSpeed = 0.25f;
namespace Gunslinger
{
	GameplayInputListener::GameplayInputListener( ) :
		m_pGameplayGameState( ZED_NULL ),
		m_DebugCameraToggle( ZED_FALSE )
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
					if( ZED::Arithmetic::Equal( ActionValue, 1.0f ) )
					{
						if( m_DebugCameraToggle == ZED_FALSE )
						{
							m_pGameplayGameState->ToggleDebugCamera( );
							m_DebugCameraToggle = ZED_TRUE;
						}
					}

					if( ZED::Arithmetic::IsZero( ActionValue ) )
					{
						m_DebugCameraToggle = ZED_FALSE;
					}

					return ZED_TRUE;
				}

				case PLAYER_MOVE_FORWARD:
				{
					m_pGameplayGameState->GetPlayerCamera( )->Move(
						ZED::Arithmetic::Vector3(
							0.0f, 0.0f, -ActionValue * MaxSpeed ) );

					return ZED_TRUE;
				}

				case PLAYER_MOVE_BACKWARD:
				{
					m_pGameplayGameState->GetPlayerCamera( )->Move(
						ZED::Arithmetic::Vector3(
							0.0f, 0.0f, ActionValue * MaxSpeed ) );

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

				case PLAYER_LOOK_HORIZONTAL:
				{
					m_pGameplayGameState->GetPlayerCamera( )->Rotate(
						ActionValue * MaxHorizontalLookSpeed,
						ZED::Arithmetic::Vector3( 0.0f, 1.0f, 0.0f ) );
					return ZED_TRUE;
				}

				case PLAYER_LOOK_VERTICAL:
				{
					m_pGameplayGameState->GetPlayerCamera( )->Rotate(
						-( ActionValue * MaxVerticalLookSpeed ),
						ZED::Arithmetic::Vector3( 1.0f, 0.0f, 0.0f ) );
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

					case DEBUG_CAMERA_LOOK_HORIZONTAL:
					{
						m_pGameplayGameState->GetDebugCamera( )->Rotate(
							-( ActionValue * MaxHorizontalLookSpeed ),
							ZED::Arithmetic::Vector3( 0.0f, 1.0f, 0.0f ) );
						return ZED_TRUE;
					}

					case DEBUG_CAMERA_LOOK_VERTICAL:
					{
						m_pGameplayGameState->GetDebugCamera( )->Rotate(
							ActionValue * MaxVerticalLookSpeed,
							ZED::Arithmetic::Vector3( 1.0f, 0.0f, 0.0f ) );
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

