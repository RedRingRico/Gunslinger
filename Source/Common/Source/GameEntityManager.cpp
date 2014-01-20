#include <GameEntityManager.hpp>
#include <Player.hpp>
#include <System/Memory.hpp>

namespace Gunslinger
{
	GameEntityManager::GameEntityManager( ) :
		m_UniqueID( 0 )
	{
	}

	GameEntityManager::~GameEntityManager( )
	{
		this->PurgeEntities( );
	}

	ZED_UINT32 GameEntityManager::CreateEntity( const GameEntityType &p_Type )
	{
		GameEntity *pGameEntity = ZED_NULL;

		if( p_Type.IsUnique( ) )
		{
			GameEntityArray::const_iterator EntityInArray =
				m_Entities.begin( );

			GameEntityType EntityType;

			while( EntityInArray != m_Entities.end( ) )
			{
				( *EntityInArray )->GetGameEntityType( &EntityType );

				if( EntityType == p_Type )
				{
					zedTrace( "<ERROR> Could not insert another %s into the "
						"array of game entities, only one is allowed\n",
						EntityType.GetName( ) );
					return ZED_FAIL;
				}
				++EntityInArray;
			}
		}

		// I'm not liking the way this will be initially implemented, as it is
		// a kludge.  There must be a better way to instantiate objects without
		// needing to manually do this for each type.
		if( p_Type.GetID( ) == PlayerGameEntityType.GetID( ) )
		{
			pGameEntity = new Player( m_UniqueID );
		}
		else
		{
			zedTrace( "<ERROR> Unable to handle game entity \"%s\" [%u]\n",
				p_Type.GetName( ), p_Type.GetID( ) );
			return ZED_FAIL;
		}
		
		GameEntityType EntityType;
		pGameEntity->GetGameEntityType( &EntityType );

		zedTrace( "Created entity type %s with ID: %u [%s]\n",
			EntityType.GetName( ), m_UniqueID,
			p_Type.IsUnique( ) ? "unique" : "not unique" );

		m_Entities.push_back( pGameEntity );

		++m_UniqueID;

		return ZED_OK;
	}

	void GameEntityManager::PurgeEntities( )
	{
		GameEntityArray::iterator Entity = m_Entities.begin( );

		while( Entity != m_Entities.end( ) )
		{
			zedSafeDelete( ( *Entity ) );
			++Entity;
		}
	}
}

