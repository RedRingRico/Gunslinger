#ifndef __GUNSLINGER_GAMEENTITYMANAGER_HPP__
#define __GUNSLINGER_GAMEENTITYMANAGER_HPP__

#include <System/DataTypes.hpp>
#include <vector>

namespace Gunslinger
{
	class GameEntity;

	class GameEntityManager
	{
	public:
		GameEntityManager( );
		~GameEntityManager( );

	private:
		GameEntityManager( const GameEntityManager &p_Original );
		GameEntityManager &operator=( const GameEntityManager &p_Original );

		typedef std::vector< GameEntity * > GameEntityArray;

		GameEntityArray	m_Entities;
	};
}

#endif // __GUNSLINGER_GAMEENTITYMAANAGER_HPP__

