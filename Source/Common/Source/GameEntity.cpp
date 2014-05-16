#include <GameEntity.hpp>
#include <System/Hash.hpp>
#include <System/Memory.hpp>
#include <cstring>

namespace Gunslinger
{
	GameEntityType::GameEntityType( ) :
		m_ID( 0 ),
		m_pName( ZED_NULL ),
		m_Unique( ZED_FALSE )
	{
	}

	GameEntityType::GameEntityType( const ZED_CHAR8 *p_pName,
		const ZED_BOOL p_Unique ) :
		m_ID( ZED::System::HashString( p_pName ) ),
		m_Unique( p_Unique )
	{
		ZED_MEMSIZE NameLength = strlen( p_pName );
		m_pName = new ZED_CHAR8[ NameLength + 1 ];
		strncpy( m_pName, p_pName, NameLength );
		m_pName[ NameLength ] = '\0';
	}

	GameEntityType::GameEntityType( const GameEntityType &p_Type ) :
		m_ID( p_Type.m_ID ),
		m_Unique( p_Type.m_Unique )
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
		m_Unique = p_Type.m_Unique;
		m_ID = p_Type.m_ID;

		ZED_MEMSIZE NameLength = strlen( p_Type.GetName( ) );
		m_pName = new ZED_CHAR8[ NameLength + 1 ];
		strncpy( m_pName, p_Type.m_pName, NameLength );
		m_pName[ NameLength ] = '\0';
	}

	ZED_BOOL GameEntityType::operator==( const GameEntityType &p_Type )
	{
		ZED_MEMSIZE NameLength = strlen( m_pName );
		if( strncmp( p_Type.m_pName, m_pName, NameLength ) != 0 )
		{
			return ZED_FALSE;
		}
		if( m_ID != p_Type.m_ID )
		{
			return ZED_FALSE;
		}

		return ZED_TRUE;
	}

	ZED_BOOL GameEntityType::IsUnique( ) const
	{
		return m_Unique;
	}

	GameEntity::GameEntity( const GameEntityType &p_EntityType,
		const ZED_UINT32 p_ID ) :
			m_ID( p_ID ),
			m_Type( p_EntityType ),
			m_Orientation(
				ZED::Arithmetic::Quaternion( 1.0f, 0.0f, 0.0f, 0.0f ) )
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

	void GameEntity::Move( const ZED_FLOAT32 p_X, const ZED_FLOAT32 p_Y,
		const ZED_FLOAT32 p_Z )
	{
		m_Velocity.Set( p_X, p_Y, p_Z );
	}

	void GameEntity::MoveForward( const ZED_FLOAT32 p_Forward )
	{
		m_Velocity[ 2 ] = -p_Forward;
	}

	void GameEntity::MoveBackward( const ZED_FLOAT32 p_Backward )
	{
		m_Velocity[ 2 ] = p_Backward;
	}

	void GameEntity::MoveLeft( const ZED_FLOAT32 p_Left )
	{
		m_Velocity[ 0 ] = -p_Left;
	}

	void GameEntity::MoveRight( const ZED_FLOAT32 p_Right )
	{
		m_Velocity[ 0 ] = p_Right;
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

	void GameEntity::Rotate( const ZED_FLOAT32 p_Angle,
		const ZED::Arithmetic::Vector3 &p_Axis )
	{
		ZED_FLOAT32 Sine, Cosine;

		ZED::Arithmetic::SinCos( p_Angle / 2.0f, Sine, Cosine );

		m_Rotation[ 0 ] = p_Axis[ 0 ] * Sine;
		m_Rotation[ 1 ] = p_Axis[ 1 ] * Sine;
		m_Rotation[ 2 ] = p_Axis[ 2 ] * Sine;
		m_Rotation[ 3 ] = Cosine;
	}

	void GameEntity::GetGameEntityType( GameEntityType *p_pType ) const
	{
		( *p_pType ) = m_Type;
	}

	ZED_UINT32 GameEntity::GetID( ) const
	{
		return m_ID;
	}
}

