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

		Configuration Test;
		Test.Read( );

		while( m_Running )
		{
			m_pWindow->Update( );
			m_pInputManager->Update( );
			m_pWindow->FlushEvents( );

			ZED_KEYBOARDSTATE NewKeyboardState;
			m_Keyboard.State( &NewKeyboardState );

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

			if( m_Keyboard.IsKeyDown( ZED_KEY_ESCAPE ) &&
				m_Keyboard.IsKeyDown( ZED_KEY_CTRL ) )
			{
				m_Running = ZED_FALSE;
			}

			GameStateManager::GetInstance( ).Execute( );

			if( GameStateManager::GetInstance( ).Running( ) == ZED_FALSE )
			{
				m_Running = ZED_FALSE;
			}
		}

		zedSafeDelete( pGameplay );

		return ZED_OK;
	}
}

