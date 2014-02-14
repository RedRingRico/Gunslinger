#include <Game.hpp>
#include <cstring>
#include <System/Memory.hpp>
#include <System/Debugger.hpp>
#include <GitVersion.hpp>
#include <unistd.h>
#include <GameStateManager.hpp>
#include <System/Time.hpp>
#include <GameplayGameState.hpp>
#include <Events.hpp>
#include <System/Debugger.hpp>
#include <Configuration.hpp>

namespace Gunslinger
{
	Game::Game( )
	{
		m_pWindow = ZED_NULL;
		m_pRenderer = ZED_NULL;
		m_pInputManager = ZED_NULL;

		memset( &m_Canvas, 0, sizeof( m_Canvas ) );
		m_Running = ZED_FALSE;
	}

	Game::~Game( )
	{
		zedSafeDelete( m_pInputManager );
		zedSafeDelete( m_pRenderer );
		zedSafeDelete( m_pWindow );
	}

	ZED_UINT32 Game::Initialise( )
	{
		if( this->PreInitialise( ) != ZED_OK )
		{
			return ZED_FAIL;
		}

		ZED_CHAR8 *pTitle = new ZED_CHAR8[ 1024 ];
		sprintf( pTitle, "Gunslinger | Version %s [%s]", GIT_BUILD_VERSION,
			GIT_TAG_NAME );
		m_pWindow->Title( pTitle );
		zedSafeDeleteArray( pTitle );

		return ZED_OK;
	}

	ZED_UINT32 Game::Execute( )
	{
		if( GameStateManager::GetInstance( ).Initialise( ) != ZED_OK )
		{
			return ZED_FAIL;
		}

		GameStateManager::GetInstance( ).SetRenderer( m_pRenderer );

		GameplayGameState *pGameplay = new GameplayGameState( );
		GameStateManager::GetInstance( ).RegisterState( pGameplay );
		GameStateManager::GetInstance( ).PushState( "Gameplay" );

		ZED_KEYBOARDSTATE PreviousKeyboardState;
		memset( &PreviousKeyboardState, 0, sizeof( PreviousKeyboardState ) );
		ZED_MEMSIZE KeyCount =	sizeof( PreviousKeyboardState ) /
								sizeof( PreviousKeyboardState.Key[ 0 ] );

		m_Running = ZED_TRUE;

		m_pWindow->GrabKeyboard( );
		m_pWindow->GrabMouse( ZED_TRUE, ZED_TRUE );

		ZED_BOOL MouseControl = ZED_TRUE;
		ZED_SINT32 HalfWidth = 0, HalfHeight = 0;
		HalfWidth = m_pWindow->GetWidth( ) / 2;
		HalfHeight = m_pWindow->GetHeight( ) / 2;

		while( m_Running )
		{
			m_pWindow->Update( );
			m_pInputManager->Update( );
			m_pWindow->FlushEvents( ZED_WINDOW_FLUSH_NONE );

			ZED_KEYBOARDSTATE NewKeyboardState;
			m_Keyboard.State( &NewKeyboardState );

			if( m_pWindow->Resized( ) )
			{
				m_GameConfiguration.SetWidth( m_pWindow->GetWidth( ) );
				m_GameConfiguration.SetHeight( m_pWindow->GetHeight( ) );
			}

			if( m_pWindow->Moved( ) )
			{
				m_GameConfiguration.SetXPosition( m_pWindow->GetXPosition( ) );
				m_GameConfiguration.SetYPosition( m_pWindow->GetYPosition( ) );
			}

			for( ZED_MEMSIZE i = 0; i < KeyCount; ++i )
			{
				if( NewKeyboardState.Key[ static_cast< ZED_KEY >( i ) ] !=
					PreviousKeyboardState.Key[ static_cast< ZED_KEY >( i ) ] )
				{
					KeyboardInputEventData KeyboardData;
					KeyboardData.SetState( static_cast< ZED_KEY >( i ),
						NewKeyboardState.Key[ i ] );

					KeyboardEvent Keyboard( &KeyboardData );

					ZED::Utility::SendEvent( Keyboard );
				}
			}

			if( m_Keyboard.IsKeyDown( ZED_KEY_F12 ) )
			{
				m_pWindow->ReleaseMouse( );
				MouseControl = !MouseControl;
				m_pWindow->GrabMouse( MouseControl, ZED_FALSE );
			}

			if( m_Keyboard.IsKeyDown( ZED_KEY_ESCAPE ) &&
				m_Keyboard.IsKeyDown( ZED_KEY_CTRL ) )
			{
				m_Running = ZED_FALSE;
			}

			ZED_UINT32 X, Y;
			m_Mouse.Position( &X, &Y );
			if( X < HalfWidth )
			{
				m_pWindow->WarpPointer( HalfWidth, Y );
			}
			else if( X > HalfWidth )
			{
				m_pWindow->WarpPointer( HalfWidth, Y );
			}

			zedTrace( "X Difference: %i\n", X - HalfWidth );

			m_Mouse.Position( &X, &Y );

			if( Y < HalfHeight )
			{
				m_pWindow->WarpPointer( X, HalfHeight );
			}
			if( Y > HalfHeight )
			{
				m_pWindow->WarpPointer( X, HalfHeight );
			}

			zedTrace( "Y Difference: %i\n", Y - HalfHeight );

			GameStateManager::GetInstance( ).Execute( );

			if( GameStateManager::GetInstance( ).Running( ) == ZED_FALSE )
			{
				m_Running = ZED_FALSE;
			}
		}

		m_pWindow->ReleaseMouse( );
		m_pWindow->ReleaseKeyboard( );

		m_GameConfiguration.Write( );

		zedSafeDelete( pGameplay );

		return ZED_OK;
	}
}

