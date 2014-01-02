#include <Game.hpp>
#include <cstring>
#include <System/Memory.hpp>
#include <System/Debugger.hpp>
#include <GitVersion.hpp>
#include <unistd.h>
#include <GameStateManager.hpp>
#include <System/Time.hpp>

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

		m_Running = ZED_TRUE;

		while( m_Running )
		{
			m_pWindow->Update( );
			m_pInputManager->Update( );
			m_pWindow->FlushEvents( );

			if( m_Keyboard.IsKeyDown( K_ESCAPE ) )
			{
				m_Running = ZED_FALSE;
			}

			GameStateManager::GetInstance( ).Execute( );

			if( GameStateManager::GetInstance( ).Running( ) == ZED_FALSE )
			{
				m_Running = ZED_FALSE;
			}
			
			this->Update( 16667ULL );
			this->Render( );
		}

		return ZED_OK;
	}

	void Game::Update( const ZED_UINT64 p_MicroSeconds )
	{
	}

	void Game::Render( )
	{
		m_pRenderer->BeginScene( ZED_TRUE, ZED_TRUE, ZED_TRUE );
		m_pRenderer->EndScene( );
	}
}

