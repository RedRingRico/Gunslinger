#ifndef __GUNSLINGER_GAMEENTITYSYSTEM_HPP__
#define __GUNSLINGER_GAMEENTITYSYSTEM_HPP__

#include <System/DataTypes.hpp>
#include <GameEntityManager.hpp>

namespace Gunslinger
{
	class GameEntity;

	class GameEntitySystem
	{
	public:
		virtual ~GameEntitySystem( );

		virtual ZED_UINT32 ProcessEntity( ENTITY_WORLD *p_pWorld,
			ZED_MEMSIZE p_Index ) = 0;
	protected:
	};
}

#endif // __GUNSLINGER_GAMEENTITYSYSTEM_HPP__

