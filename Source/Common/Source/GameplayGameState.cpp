#include <GameplayGameState.hpp>
#include <GameStateManager.hpp>
#include <System/Memory.hpp>
#include <Actions.hpp>

namespace Gunslinger
{
	GameplayGameState::GameplayGameState( ) :
		m_pInputBinder( new ZED::Utility::InputBinder( ) ),
		m_pEventRouter( new ZED::Utility::EventRouter(
			"Gameplay", ZED_TRUE, 2 ) )
	{
	}

	GameplayGameState::~GameplayGameState( )
	{
		zedSafeDelete( m_pInputBinder );
	}

	ZED_UINT32 GameplayGameState::Enter( )
	{
		m_pInputBinder->BindKey( K_ESCAPE, STATE_EXIT );
		GameStateManager::GetInstance( ).SetInputBinder( m_pInputBinder );
		return ZED_OK;
	}

	void GameplayGameState::Render( )
	{
		GameStateManager::GetInstance( ).GetRenderer( )->ClearColour(
			0.0f, 1.0f, 0.0f );
	}

	void GameplayGameState::Update( const ZED_UINT64 p_ElapsedTime )
	{
	}

	ZED_UINT32 GameplayGameState::Exit( )
	{
		return ZED_OK;
	}

	ZED_CHAR8 *GameplayGameState::GetName( ) const
	{
		return "Gameplay";
	}
}

