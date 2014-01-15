#include <GameEntity.hpp>
#include <System/Hash.hpp>
#include <System/Memory.hpp>
#include <cstring>

namespace Gunslinger
{
	GameEntity::GameEntity( const ZED_CHAR8 *p_pName, const ZED_UINT32 p_ID )
	{
		m_Type = ZED::System::HashString( p_pName );
		m_ID = p_ID;

		ZED_MEMSIZE NameLength = strlen( p_pName );
		m_pName = new ZED_CHAR8[ NameLength + 1 ];
		strncpy( m_pName, p_pName, NameLength );
		m_pName[ NameLength ] = '\0';
	}

	GameEntity::~GameEntity( )
	{
		zedSafeDeleteArray( m_pName );
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

