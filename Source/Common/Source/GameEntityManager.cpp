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

		// FIXME
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
		if( pGameEntity->Initialise( ) != ZED_OK )
		{
			zedSafeDelete( pGameEntity );
			zedTrace( "Failed to initialise entity: %s [%u]\n",
				EntityType.GetName( ), EntityType.GetID( ) );
			return ZED_FAIL;
		}

		zedTrace( "Created entity type %s with ID: %u [%s]\n",
			EntityType.GetName( ), m_UniqueID,
			p_Type.IsUnique( ) ? "unique" : "not unique" );

		m_Entities.push_back( pGameEntity );

		++m_UniqueID;

		return ZED_OK;
	}

	void GameEntityManager::Update( const ZED_UINT64 p_ElapsedDeltaTime )
	{
		GameEntityArray::const_iterator EntityItr = m_Entities.begin( );

		while( EntityItr != m_Entities.end( ) )
		{
			( *EntityItr )->Update( p_ElapsedDeltaTime );
			++EntityItr;
		}
	}

	ZED_UINT32 GameEntityManager::GetEntityByID( const ZED_UINT32 p_ID,
		GameEntity **p_ppEntity )
	{
		GameEntityArray::iterator Entity = m_Entities.begin( );

		while( Entity != m_Entities.end( ) )
		{
			if( ( *Entity )->GetID( ) == p_ID )
			{
				( *p_ppEntity ) = ( *Entity );
				return ZED_OK;
			}
			++Entity;
		}

		return ZED_FAIL;
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

