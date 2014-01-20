#include <GameEntity.hpp>
#include <System/Hash.hpp>
#include <System/Memory.hpp>
#include <cstring>

namespace Gunslinger
{
	GameEntityType::GameEntityType( ) :
		m_ID( 0 ),
		m_pName( ZED_NULL )
	{
	}

	GameEntityType::GameEntityType( const ZED_CHAR8 *p_pName )
	{
		m_ID = ZED::System::HashString( p_pName );

		ZED_MEMSIZE NameLength = strlen( p_pName );
		m_pName = new ZED_CHAR8[ NameLength + 1 ];
		strncpy( m_pName, p_pName, NameLength );
		m_pName[ NameLength ] = '\0';
	}

	GameEntityType::GameEntityType( const GameEntityType &p_Type ) :
		m_ID( p_Type.m_ID )
	{
		ZED_MEMSIZE NameLength = strlen( p_Type.GetName( ) );
		m_pName = new ZED_CHAR8[ NameLength + 1 ];
		strncpy( m_pName, p_Type.m_pName, NameLength );
		m_pName[ NameLength ] = '\0';
	}

	GameEntityType::~GameEntityType( )
	{
		zedSafeDeleteArray( m_pName );
	}

	ZED_UINT32 GameEntityType::GetID( ) const
	{
		return m_ID;
	}

	const ZED_CHAR8 *GameEntityType::GetName( ) const
	{
		return m_pName;
	}

	GameEntityType &GameEntityType::operator=( const GameEntityType &p_Type )
	{
		m_ID = p_Type.m_ID;

		ZED_MEMSIZE NameLength = strlen( p_Type.GetName( ) );
		m_pName = new ZED_CHAR8[ NameLength + 1 ];
		strncpy( m_pName, p_Type.m_pName, NameLength );
		m_pName[ NameLength ] = '\0';
	}

	GameEntity::GameEntity( const GameEntityType &p_EntityType,
		const ZED_UINT32 p_ID ) :
			m_ID( p_ID ),
			m_Type( p_EntityType )
	{
	}

	GameEntity::~GameEntity( )
	{
	}

	void GameEntity::GetPosition( ZED::Arithmetic::Vector3 *p_pPosition ) const
	{
		( *p_pPosition ) = m_Position;
	}

	void GameEntity::SetPosition( const ZED::Arithmetic::Vector3 &p_Position )
	{
		m_Position = p_Position;
	}

	void GameEntity::GetOrientation(
		ZED::Arithmetic::Quaternion *p_pOrientation ) const
	{
		( *p_pOrientation ) = m_Orientation;
	}
	
	void GameEntity::SetOrientation(
		const ZED::Arithmetic::Quaternion &p_Orientation )
	{
		m_Orientation = p_Orientation;
	}
}

