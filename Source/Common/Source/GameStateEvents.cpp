#include <GameStateEvents.hpp>
#include <Events.hpp>
#include <Utility/EventRouter.hpp>
#include <System/Debugger.hpp>

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

				ZED_UINT32 ActionCount =
					m_pInputBinder->GetActionCountForKey( Key );

				if( ActionCount == 0 )
				{
					return ZED_FAIL;
				}
				else if( ActionCount == 1 )
				{				
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
				else
				{
					ZED_UINT32 ActionID[ ActionCount ];
					m_pInputBinder->GetActionsFromKey( Key, ActionID );

					for( ZED_UINT32 i = 0; i < ActionCount; ++i )
					{
						ZED_FLOAT32 ActionValue = KeyState ? 1.0f : 0.0f;
						ActionInputEventData ActionData;
						ActionData.SetAction( ActionID[ i ], ActionValue );
						ActionInputEvent Action( &ActionData );

						ZED::Utility::SendEvent( Action );
					}
					return ZED_TRUE;
				}
			}
		}


		if( p_Event.Type( ).ID( ) == MousePositionInputEventType.ID( ) )
		{
			if( m_pInputBinder )
			{
				MousePositionInputEventData *pMousePositionData =
					p_Event.Data< MousePositionInputEventData >( );
			
				ZED_SINT32 MouseX;
				ZED_SINT32 MouseY;
				ZED_BOOL Return = ZED_FALSE;

				pMousePositionData->GetPosition( MouseX, MouseY );
				ZED_FLOAT32 X = 0.0f, Y = 0.0f;
				
				if( MouseX != m_HalfScreenWidth )
				{
					ZED_UINT32 ActionCount =
						m_pInputBinder->GetActionCountForMouseAxis(
							ZED_MOUSE_AXIS_X );

					if( ActionCount != 0 )
					{
						if( ActionCount == 1 )
						{
							ZED_UINT32 ActionID =
								m_pInputBinder->GetActionFromMouseAxis(
									ZED_MOUSE_AXIS_X );

							if( ActionID != 0 )
							{
								ZED_FLOAT32 ActionValue =
									( static_cast< ZED_FLOAT32 >( MouseX ) /
										m_HalfScreenWidthF ) - 1.0f;
								ActionInputEventData ActionData;
								ActionData.SetAction( ActionID, ActionValue );
								ActionInputEvent Action( &ActionData );

								ZED::Utility::SendEvent( Action );
							}
						}
						else
						{
							ZED_UINT32 ActionID[ ActionCount ];
							m_pInputBinder->GetActionsFromMouseAxis(
								ZED_MOUSE_AXIS_X, ActionID );

							for( ZED_UINT32 i = 0; i < ActionCount; ++i )
							{
								ZED_FLOAT32 ActionValue =
									( static_cast< ZED_FLOAT32 >( MouseX ) /
										m_HalfScreenWidthF ) - 1.0f;
								ActionInputEventData ActionData;
								ActionData.SetAction( ActionID[ i ],
									ActionValue );
								ActionInputEvent Action( &ActionData );

								ZED::Utility::SendEvent( Action );
							}
						}
					}
					else
					{
					}
				}

				if( MouseY != m_HalfScreenHeight )
				{
					ZED_UINT32 ActionCount =
						m_pInputBinder->GetActionCountForMouseAxis(
							ZED_MOUSE_AXIS_Y );

					if( ActionCount != 0 )
					{
						if( ActionCount == 1 )
						{
							ZED_UINT32 ActionID =
								m_pInputBinder->GetActionFromMouseAxis(
									ZED_MOUSE_AXIS_Y );

							if( ActionID != 0 )
							{
								ZED_FLOAT32 ActionValue =
									-( ( static_cast< ZED_FLOAT32 >( MouseY ) /
										m_HalfScreenHeightF ) - 1.0f );

								ActionInputEventData ActionData;
								ActionData.SetAction( ActionID, ActionValue );
								ActionInputEvent Action( &ActionData );

								ZED::Utility::SendEvent( Action );
							}
						}
						else
						{
							ZED_UINT32 ActionID[ ActionCount ];
							m_pInputBinder->GetActionsFromMouseAxis(
								ZED_MOUSE_AXIS_Y, ActionID );

							for( ZED_UINT32 i = 0; i < ActionCount; ++i )
							{
								ZED_FLOAT32 ActionValue =
									-( ( static_cast< ZED_FLOAT32 >( MouseY ) /
										m_HalfScreenHeightF ) - 1.0f );

								ActionInputEventData ActionData;
								ActionData.SetAction( ActionID[ i ],
									ActionValue );
								ActionInputEvent Action( &ActionData );

								ZED::Utility::SendEvent( Action );
							}
						}
					}
				}

				return Return;
			}
		}

		if( p_Event.Type( ).ID( ) == ResolutionChangeEventType.ID( ) )
		{
			ResolutionChangeEventData *pResolutionData =
				p_Event.Data< ResolutionChangeEventData >( );
			
			ZED_UINT32 ScreenWidth = 0, ScreenHeight = 0;

			pResolutionData->GetResolution( ScreenWidth, ScreenHeight );

			if( ScreenWidth == 0 )
			{
				zedTrace( "[Gunslinger::GameStateInputListener::HandleEvent] "
					"<ERORR> Setting screen resolution failed, screen width "
					"is zero\n" );

				return ZED_FALSE;
			}

			if( ScreenHeight == 0 )
			{
				zedTrace( "[Gunslinger::GameStateInputListener::HandleEvent] "
					"<ERORR> Setting screen resolution failed, screen height "
					"is zero\n" );

				return ZED_FALSE;
			}

			m_ScreenWidth = ScreenWidth;
			m_ScreenHeight = ScreenHeight;
			m_HalfScreenWidth = ScreenWidth / 2;
			m_HalfScreenHeight = ScreenHeight / 2;
			m_HalfScreenWidthF =
				static_cast< ZED_FLOAT32 >( m_ScreenWidth ) / 2.0f;
			m_HalfScreenHeightF =
				static_cast< ZED_FLOAT32 >( m_ScreenHeight ) / 2.0f;

			return ZED_TRUE;
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

