#ifndef __GUNSLINGER_GAMEPLAYGAMESTATE_HPP__
#define __GUNSLINGER_GAMEPLAYGAMESTATE_HPP__

#include <System/DataTypes.hpp>
#include <GameState.hpp>
#include <Utility/Camera.hpp>
#include <Utility/FreeCamera.hpp>
#include <Utility/FirstPersonCamera.hpp>
#include <Player.hpp>
#include <GameEntityManager.hpp>

namespace Gunslinger
{
	class GameplayInputListener;
	class World;

	class GameplayGameState : public GameState
	{
	public:
		GameplayGameState( );
		virtual ~GameplayGameState( );

		virtual ZED_UINT32 Enter( );
		virtual void Render( );
		virtual void Update( const ZED_UINT64 p_ElapsedTime );
		virtual ZED_UINT32 Exit( );

		virtual ZED_CHAR8 *GetName( ) const;

		ZED::Utility::FreeCamera		*GetDebugCamera( );
		ZED::Utility::FirstPersonCamera	*GetPlayerCamera( );

		void ToggleDebugCamera( );
		ZED_BOOL DebugCameraActive( ) const;

	private:
		GameplayInputListener		*m_pInputListener;
		World						*m_pGameWorld;
		ZED::Utility::FreeCamera	m_DebugCamera;
		ZED_BOOL					m_DebugCameraActive;
		ZED::Utility::Camera		*m_pActiveCamera;
		ZED::Utility::Camera		*m_pPreviousCamera;
		GameEntityManager			m_GameEntityManager;
	};
}

#endif // __GUNSLINGER_GAMEPLAYGAMESTATE_HPP__

