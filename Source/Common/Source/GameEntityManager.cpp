#include <GameEntityManager.hpp>
#include <Player.hpp>
#include <System/Memory.hpp>
#include <GameEntityComponent.hpp>
#include <GameEntitySystem.hpp>
#include <System/Debugger.hpp>
#include <cstring>

namespace Gunslinger
{
	GameEntityManager::GameEntityManager( )
	{
		memset( &m_GameEntityWorld, 0, sizeof( m_GameEntityWorld ) );
	}

	GameEntityManager::~GameEntityManager( )
	{
	}

	ZED_UINT32 GameEntityManager::CreateEntity( )
	{
		for( ZED_MEMSIZE i = 0; i < MAX_ENTITY_COUNT; ++i )
		{
			if( m_GameEntityWorld.Mask[ i ] == ENTITY_TYPE_NONE )
			{
				return i;
			}
		}

		zedTrace( "[Gunslinger::GameEntityManager::CreateEntity] <WARN> "
			"This is the last entity available\n" );

		return MAX_ENTITY_COUNT;
	}

	void GameEntityManager::DestroyEntity( const ZED_MEMSIZE p_Index )
	{
		if( ( p_Index > MAX_ENTITY_COUNT ) || ( p_Index < 0 ) )
		{
			return;
		}

		m_GameEntityWorld.Mask[ p_Index ] = ENTITY_TYPE_NONE;
	}

	ZED_UINT32 GameEntityManager::SetEntityComponents(
		const ZED_MEMSIZE p_Index, const ZED_UINT32 p_ComponentMask )
	{
		if( ( p_Index < 0 ) || ( p_Index > MAX_ENTITY_COUNT ) )
		{
			zedTrace( "[Gunslinger::GameEntityManager::SetEntityComponents] "
				"<ERROR> Unable to modify component at location: %d \n"
				"\tIndex out of bounds\n", p_Index );

			return ZED_FAIL;
		}

		m_GameEntityWorld.Mask[ p_Index ] = p_ComponentMask;

		return ZED_OK;
	}

	ZED_UINT32 GameEntityManager::AddEntityComponent(
		const ZED_MEMSIZE p_Index, const ZED_UINT32 p_ComponentMask )
	{
		if( ( p_Index < 0 ) || ( p_Index > MAX_ENTITY_COUNT ) )
		{
			zedTrace( "[Gunslinger::GameEntityManager::AddEntityComponent] "
				"<ERROR> Unable to modify component at location: %d\n"
				"\tIndex out of bounds\n", p_Index );

			return ZED_FAIL;
		}

		m_GameEntityWorld.Mask[ p_Index ] |= p_ComponentMask;

		return ZED_OK;
	}

	ZED_UINT32 GameEntityManager::RemoveEntityComponent(
		const ZED_MEMSIZE p_Index, const ZED_UINT32 p_ComponentMask )
	{
		if( ( p_Index < 0 ) || ( p_Index > MAX_ENTITY_COUNT ) ) 
		{
			zedTrace( "[Gunslinger::GameEntityManager::RemoveEntityComponent] "
				"<ERROR> Unable to modify component at location: %d\n"
				"\tIndex out of bounds\n", p_Index );

			return ZED_FAIL;
		}

		m_GameEntityWorld.Mask[ p_Index ] = ~p_ComponentMask &
			m_GameEntityWorld.Mask[ p_Index ];

		return ZED_OK;
	}

	ZED_UINT32 GameEntityManager::PrintEntityComponents(
		const ZED_MEMSIZE p_Index ) const
	{
		if( ( p_Index < 0 ) || ( p_Index > MAX_ENTITY_COUNT ) )
		{
			zedTrace( "{Gunslinger::GameEntityManager::PrintEntityComponents] "
				"<ERROR> Unable to modify component at location: %d\n"
				"\tIndex out of bounds\n", p_Index );

			return ZED_FAIL;
		}

		zedTrace( "Game entity ID: %d | ", p_Index );
		zedTrace( "Mask: 0x%08X [ ", m_GameEntityWorld.Mask[ p_Index ] );

		if( m_GameEntityWorld.Mask[ p_Index ] == ENTITY_TYPE_NONE )
		{
			zedTrace( "NONE" );
		}

		ZED_BOOL AddPipe = ZED_FALSE;

		if( m_GameEntityWorld.Mask[ p_Index ] & ENTITY_TYPE_POSITION )
		{
			if( AddPipe )
			{
				zedTrace( " | " );
			}

			zedTrace( "POSITION" );

			AddPipe = ZED_TRUE;
		}

		if( m_GameEntityWorld.Mask[ p_Index ] & ENTITY_TYPE_VELOCITY )
		{
			if( AddPipe )
			{
				zedTrace( " | " );
			}

			zedTrace( "VELOCITY" );

			AddPipe = ZED_TRUE;
		}

		if( m_GameEntityWorld.Mask[ p_Index ] & ENTITY_TYPE_RENDER )
		{
			if( AddPipe )
			{
				zedTrace( " | " );
			}

			zedTrace( "RENDER" );

			AddPipe = ZED_TRUE;
		}

		if( m_GameEntityWorld.Mask[ p_Index ] & ENTITY_TYPE_COLLIDE )
		{
			if( AddPipe )
			{
				zedTrace( " | " );
			}

			zedTrace( "COLLIDE" );

			AddPipe = ZED_TRUE;
		}

		zedTrace( " ]\n" );

		return ZED_OK;
	}

	ZED_UINT32 GameEntityManager::PrintAllEntityComponents( ) const
	{
		for( ZED_MEMSIZE i = 0; i < MAX_ENTITY_COUNT; ++i )
		{
			ZED_UINT32 Error = this->PrintEntityComponents( i );

			if( Error != ZED_OK )
			{
				return Error;
			}
		}

		return ZED_OK;
	}

	ZED_UINT32 GameEntityManager::AddSystem( GameEntitySystem *p_pSystem )
	{
		for( ZED_MEMSIZE i = 0; i < m_Systems.size( ); ++i )
		{
			if( m_Systems[ i ] == p_pSystem )
			{
				return ZED_OK;
			}
		}

		m_Systems.push_back( p_pSystem );

		return ZED_OK;
	}

	ZED_UINT32 GameEntityManager::Process( )
	{
		GameSystemArray::const_iterator SystemItr =
			m_Systems.begin( );

		while( SystemItr != m_Systems.end( ) )
		{
			for( ZED_MEMSIZE i = 0; i < MAX_ENTITY_COUNT; ++i )
			{
				( *SystemItr )->ProcessEntity( &m_GameEntityWorld, i );
			}

			++SystemItr;
		}

		return ZED_OK;
	}

	GameEntityManager &GameEntityManager::GetInstance( )
	{
		static GameEntityManager Instance;

		return Instance;
	}
}

