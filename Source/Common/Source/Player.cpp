#include <Player.hpp>

namespace Gunslinger
{
	Player::Player( const ZED_UINT32 p_ID ) :
		GameEntity( PlayerGameEntityType, p_ID )
	{
		m_Camera.SetViewMode( ZED_VIEWMODE_PERSPECTIVE );
		m_Camera.SetClippingPlanes( 1.0f, 100000.0f );
		m_Camera.SetPerspectiveProjection( 45.0f, 1280.0f / 720.0f, ZED_NULL );
	}

	Player::~Player( )
	{
	}

	ZED_UINT32 Player::Initialise( )
	{
		return ZED_OK;
	}

	void Player::Update( const ZED_UINT64 p_ElapsedTime )
	{
	}

	void Player::Render( )
	{
	}

	void Player::SetPosition( const ZED::Arithmetic::Vector3 &p_Position )
	{
		GameEntity::SetPosition( p_Position );
		m_Camera.SetPosition( m_Position );
	}

	void Player::SetOrientation(
		const ZED::Arithmetic::Quaternion &p_Orientation )
	{
		GameEntity::SetOrientation( p_Orientation );
	}

	void Player::GetCamera( ZED::Utility::Camera **p_ppCamera )
	{
		( *p_ppCamera ) = &m_Camera;
	}
}

