#ifndef __GUNSLINGER_GAMESTATE_HPP__
#define __GUNSLINGER_GAMESTATE_HPP__

#include <System/DataTypes.hpp>

namespace Gunslinger
{
	class GameState
	{
	public:
		virtual ~GameState( );

		virtual ZED_UINT32 Enter( ) = 0;
		virtual void Render( ) = 0;
		virtual void Update( const ZED_UINT64 p_ElapsedTime ) = 0;
		virtual ZED_UINT32 Exit( ) = 0;

		virtual ZED_CHAR8 *GetName( ) const = 0;

	protected:
	};
}

#endif // __GUNSLINGER_GAMESTATE_HPP__

