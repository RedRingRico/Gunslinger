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

		m_GameConfiguration.Read( );

		ZED_SINT32 X, Y;
		ZED_UINT32 Width, Height;
		ZED_SINT32 DisplayNumber, ScreenNumber;
		X = m_GameConfiguration.GetXPosition( );
		Y = m_GameConfiguration.GetYPosition( );
		Width = m_GameConfiguration.GetWidth( );
		Height = m_GameConfiguration.GetHeight( );
		DisplayNumber = m_GameConfiguration.GetDisplayNumber( );
		ScreenNumber = m_GameConfiguration.GetScreenNumber( );
		ZED_UINT32 WindowStyle = ZED_WINDOW_STYLE_MINIMISE |
			ZED_WINDOW_STYLE_CLOSE | ZED_WINDOW_STYLE_TITLEBAR |
			ZED_WINDOW_STYLE_MOVE;

		if( m_pWindow->Create( X, Y, Width, Height, DisplayNumber,
			ScreenNumber, WindowStyle ) !=
			ZED_OK )
		{
			zedTrace( "[Gunslinger::Game::Initialise] <ERROR> "
				"Failed to create window\n" );

			return ZED_FAIL;
		}

		m_Canvas.Width( Width );
		m_Canvas.Height( Height );
		m_Canvas.BackBufferCount( 1 );
		m_Canvas.ColourFormat( ZED_FORMAT_ARGB8 );
		m_Canvas.DepthStencilFormat( ZED_FORMAT_D24S8 );

		if( m_pRenderer->Create( m_Canvas, ( *m_pWindow ) ) != ZED_OK )
		{
			zedTrace( "[Gunslinger::Game::Initialise] <ERROR> "
				"Failed to create renderer\n" );
			
			return ZED_FAIL;
		}

		m_pRenderer->ClearColour( 0.14f, 0.0f, 0.14f );
		m_pRenderer->RenderState( ZED_RENDERSTATE_CULLMODE,
			ZED_CULLMODE_NONE );
		m_pRenderer->RenderState( ZED_RENDERSTATE_DEPTH, ZED_ENABLE );
		ZED::System::WINDOWDATA WindowData = m_pWindow->WindowData( );

		if( m_pInputManager->SetWindowData( m_pWindow->WindowData( ) ) !=
			ZED_OK )
		{
			zedTrace( "[Gunslinger::Game::Initialise] <ERROR> "
				"Failed to attach the window to the input manager\n" );

			return ZED_FAIL;
		}

		m_pInputManager->AddDevice( &m_Keyboard );
		m_pInputManager->AddDevice( &m_Mouse );

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

		ZED_SINT32 PreviousMouseX, PreviousMouseY;
		m_Mouse.GetPosition( PreviousMouseX, PreviousMouseY );

		ResolutionChangeEventData ResolutionData;
		ResolutionData.SetResolution( m_pWindow->GetWidth( ),
			m_pWindow->GetHeight( ) );

		ResolutionChangeEvent Resolution( &ResolutionData );

		ZED::Utility::SendEvent( Resolution );

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

				ResolutionChangeEventData ResolutionData;
				ResolutionData.SetResolution( m_pWindow->GetWidth( ),
					m_pWindow->GetHeight( ) );

				ResolutionChangeEvent Resolution( &ResolutionData );

				ZED::Utility::SendEvent( Resolution );
			}

			if( m_pWindow->Moved( ) )
			{
				m_GameConfiguration.SetXPosition( m_pWindow->GetXPosition( ) );
				m_GameConfiguration.SetYPosition( m_pWindow->GetYPosition( ) );
			}

			for( ZED_MEMSIZE i = 0; i < KeyCount; ++i )
			{
				ZED_KEY ZEDKey = static_cast< ZED_KEY >( i );
				KeyboardInputEventData KeyboardData;
				KeyboardData.SetState( ZEDKey,
					NewKeyboardState.Key[ i ] );

				KeyboardEvent Keyboard( &KeyboardData );
				ZED::Utility::SendEvent( Keyboard );
			}

			if( NewKeyboardState.Key[ ZED_KEY_F12 ] !=
				PreviousKeyboardState.Key[ ZED_KEY_F12 ] )
			{
				if( NewKeyboardState.Key[ ZED_KEY_F12 ] )
				{
					m_pWindow->ReleaseMouse( );
					MouseControl = !MouseControl;
					m_pWindow->GrabMouse( MouseControl, ZED_FALSE );
				}
			}

			if( m_Keyboard.IsKeyDown( ZED_KEY_ESCAPE ) &&
				m_Keyboard.IsKeyDown( ZED_KEY_CTRL ) )
			{
				m_Running = ZED_FALSE;
			}

			ZED_SINT32 MouseX, MouseY;
			m_Mouse.GetPosition( MouseX, MouseY );

			if( ( MouseX != PreviousMouseX ) || ( MouseY != PreviousMouseY ) )
			{
				MousePositionInputEventData MousePositionData;
				MousePositionData.SetPosition( MouseX, MouseY );
				MousePositionEvent MousePosition( &MousePositionData );
				ZED::Utility::SendEvent( MousePosition );
			}

			GameStateManager::GetInstance( ).Execute( );

			if( GameStateManager::GetInstance( ).Running( ) == ZED_FALSE )
			{
				m_Running = ZED_FALSE;
			}

			PreviousMouseX = MouseX;
			PreviousMouseY = MouseY;

			m_pWindow->WarpPointer( HalfWidth, HalfHeight );

			memcpy( &PreviousKeyboardState, &NewKeyboardState,
				sizeof( PreviousKeyboardState ) );
		}

		m_pWindow->ReleaseMouse( );
		m_pWindow->ReleaseKeyboard( );

		m_GameConfiguration.Write( );

		zedSafeDelete( pGameplay );

		return ZED_OK;
	}
}

