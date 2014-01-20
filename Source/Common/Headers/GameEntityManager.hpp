#ifndef __GUNSLINGER_GAMEENTITYMANAGER_HPP__
#define __GUNSLINGER_GAMEENTITYMANAGER_HPP__

#include <System/DataTypes.hpp>
#include <GameEntity.hpp>
#include <vector>

namespace Gunslinger
{
	class GameEntityManager
	{
	public:
		GameEntityManager( );
		~GameEntityManager( );

		ZED_UINT32 CreateEntity( const GameEntityType &p_Type );

	private:
		GameEntityManager( const GameEntityManager &p_Original );
		GameEntityManager &operator=( const GameEntityManager &p_Original );

		typedef std::vector< GameEntity * > GameEntityArray;

		GameEntityArray	m_Entities;
	};
}

#endif // __GUNSLINGER_GAMEENTITYMAANAGER_HPP__

