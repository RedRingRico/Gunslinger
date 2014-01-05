#ifndef __GUNSLINGER_GAMEPLAYGAMESTATE_HPP__
#define __GUNSLINGER_GAMEPLAYGAMESTATE_HPP__

#include <System/DataTypes.hpp>
#include <GameState.hpp>
#include <Utility/InputBinder.hpp>
#include <Utility/EventRouter.hpp>

namespace Gunslinger
{
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

	private:
		ZED::Utility::InputBinder	*m_pInputBinder;
		ZED::Utility::EventRouter	*m_pEventRouter;
	};
}

#endif // __GUNSLINGER_GAMEPLAYGAMESTATE_HPP__

