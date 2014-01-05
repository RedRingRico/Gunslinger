#ifndef __GUNSLINGER_GAMEPLAYGAMESTATE_HPP__
#define __GUNSLINGER_GAMEPLAYGAMESTATE_HPP__

#include <System/DataTypes.hpp>
#include <GameState.hpp>

namespace Gunslinger
{
	class GameplayInputListener;

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
		GameplayInputListener		*m_pInputListener;
	};
}

#endif // __GUNSLINGER_GAMEPLAYGAMESTATE_HPP__

