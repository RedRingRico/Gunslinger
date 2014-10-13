#ifndef __GUNSLINGER_GAMEENTITYMANAGER_HPP__
#define __GUNSLINGER_GAMEENTITYMANAGER_HPP__

#include <System/DataTypes.hpp>
#include <PositionComponent.hpp>
#include <vector>
#include <map>

namespace Gunslinger
{
	class GameEntity;
	class GameEntityComponent;
	class GameEntitySystem;

	const ZED_MEMSIZE MAX_ENTITY_COUNT = 300;

	// The list of entities in the world are stored as a structre of arrays in
	// order to improve cache coherency.  Unfortunately, this means each entity
	// has to retain the data for all components.
	typedef struct _tagENTITY_WORLD
	{
		ZED_UINT32	Mask[ MAX_ENTITY_COUNT ];

		PositionComponent Position[ MAX_ENTITY_COUNT ];
	}ENTITY_WORLD;

	class GameEntityManager
	{
	public:
		GameEntityManager( );
		~GameEntityManager( );

		ZED_UINT32 CreateEntity( );
		void DestroyEntity( ZED_MEMSIZE p_Index );

		ZED_UINT32 SetEntityComponents( const ZED_MEMSIZE p_Index,
			const ZED_UINT32 p_ComponentMask );

		ZED_UINT32 AddEntityComponent( const ZED_MEMSIZE p_Index,
			const ZED_UINT32 p_ComponentMask );
		ZED_UINT32 RemoveEntityComponent( const ZED_MEMSIZE p_Index,
			const ZED_UINT32 p_ComponentMask );

		ZED_UINT32 GetEntityComponents( const ZED_MEMSIZE p_Index,
			ZED_UINT32 *p_pComponentMask ) const;
		ZED_UINT32 PrintEntityComponents( const ZED_MEMSIZE p_Index ) const;

		ZED_UINT32 PrintAllEntityComponents( ) const;

		ZED_UINT32 AddSystem( GameEntitySystem *p_pSystem );

		ZED_UINT32 Process( );

		static GameEntityManager &GetInstance( );

	private:
		typedef std::vector< GameEntitySystem * >GameSystemArray;

		GameSystemArray		m_Systems;

		ENTITY_WORLD m_GameEntityWorld;
	};
}

#endif // __GUNSLINGER_GAMEENTITYMAANAGER_HPP__

