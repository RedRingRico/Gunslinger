#ifndef __GUNSLINGER_GAMEPLAYEVENTS_HPP__
#define __GUNSLINGER_GAMEPLAYEVENTS_HPP__

#include <System/DataTypes.hpp>
#include <Utility/Event.hpp>

namespace Gunslinger
{
	const ZED_UINT32 PLAYER_MOVE_FORWARD	= 9000;
	const ZED_UINT32 PLAYER_MOVE_BACKWARD	= 9001;
	const ZED_UINT32 PLAYER_MOVE_LEFT		= 9002;
	const ZED_UINT32 PLAYER_MOVE_RIGHT		= 9003;

	const ZED_UINT32 DEBUG_CAMERA_MOVE_FORWARD	= 10000;
	const ZED_UINT32 DEBUG_CAMERA_MOVE_BACKWARD	= 10001;
	const ZED_UINT32 DEBUG_CAMERA_MOVE_LEFT		= 10002;
	const ZED_UINT32 DEBUG_CAMERA_MOVE_RIGHT	= 10003;
	const ZED_UINT32 DEBUG_CAMERA_MOVE_UP		= 10004;
	const ZED_UINT32 DEBUG_CAMERA_MOVE_DOWN		= 10005;
	const ZED_UINT32 DEBUG_CAMERA_LOOK_UP		= 10006;
	const ZED_UINT32 DEBUG_CAMERA_LOOK_DOWN		= 10007;
	const ZED_UINT32 DEBUG_CAMERA_LOOK_LEFT		= 10008;
	const ZED_UINT32 DEBUG_CAMERA_LOOK_RIGHT	= 10009;
	const ZED_UINT32 DEBUG_CAMERA_TOGGLE		= 10010;

	class GameplayGameState;

	class GameplayInputListener : public ZED::Utility::EventListener
	{
	public:
		GameplayInputListener( );
		virtual ~GameplayInputListener( );

		virtual ZED_BOOL HandleEvent( const ZED::Utility::Event &p_Event );

		virtual ZED_CHAR8 *Name( ) const;

		ZED_UINT32 SetGameplayGameState(
			GameplayGameState * const &p_pGameplayGameState );

	private:
		GameplayGameState	*m_pGameplayGameState;
	};
}

#endif // __GUNSLINGER_GAMEPLAYEVENTS_HPP__

