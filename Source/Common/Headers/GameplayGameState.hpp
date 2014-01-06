#ifndef __GUNSLINGER_GAMEPLAYGAMESTATE_HPP__
#define __GUNSLINGER_GAMEPLAYGAMESTATE_HPP__

#include <System/DataTypes.hpp>
#include <GameState.hpp>
#include <Utility/FreeCamera.hpp>

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

		ZED::Utility::FreeCamera *GetDebugCamera( );

	private:
		GameplayInputListener		*m_pInputListener;
		World						*m_pGameWorld;
		ZED::Utility::FreeCamera	m_DebugCamera;
	};
}

#endif // __GUNSLINGER_GAMEPLAYGAMESTATE_HPP__

