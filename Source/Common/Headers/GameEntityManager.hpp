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
		typedef std::vector< GameEntity * > GameEntityArray;

		GameEntityArray	m_Entities;
	};
}

#endif // __GUNSLINGER_GAMEENTITYMAANAGER_HPP__

