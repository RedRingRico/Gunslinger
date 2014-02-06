#include <Game.hpp>
#include <System/LinuxWindow.hpp>
#include <Renderer/LinuxRendererOGL3.hpp>
#include <System/LinuxInputManager.hpp>
#include <Renderer/OGL/GLTexture.hpp>
#include <System/Memory.hpp>

namespace Gunslinger
{
	ZED_UINT32 Game::PreInitialise( )
	{
		m_pWindow = new ZED::System::LinuxWindow( );

		if( !m_pWindow )
		{
			zedTrace( "[Gunslinger::Game::Initialise] <ERROR> "
				"Failed to create a new window\n" );
				
			return ZED_FAIL;
		}

		m_pRenderer = new ZED::Renderer::LinuxRendererOGL3( );

		if( !m_pRenderer )
		{
			zedTrace( "[Gunslinger::Game::Initialise] <ERROR> "
				"Failed to create a new renderer\n" );

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

		// TODO
		// The display and screen number should first be derived from the
		// cursor's position (Configuration should handle that)
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

		m_pInputManager = new ZED::System::LinuxInputManager( WindowData );

		if( !m_pInputManager )
		{
			zedTrace( "[Gunslinger::Game::Initialise] <ERROR> "
				"Failed to create new input manager\n" );
		}

		m_pInputManager->AddDevice( &m_Keyboard );

		return ZED_OK;
	}
}

