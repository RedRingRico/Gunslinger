#include <Player.hpp>

namespace Gunslinger
{
	Player::Player( )
	{
		m_Camera.SetViewMode( ZED_VIEWMODE_PERSPECTIVE );
		m_Camera.SetClippingPlanes( 1.0f, 100000.0f );
		m_Camera.SetPerspectiveProjection( 45.0f, 1280.0f / 720.0f, ZED_NULL );
	}

	Player::~Player( )
	{
	}

	void Player::SetPosition( const ZED::Arithmetic::Vector3 &p_Position )
	{
		m_Position = p_Position;
		m_Camera.SetPosition( m_Position );
	}

	void Player::GetCamera( ZED::Utility::Camera **p_ppCamera )
	{
		( *p_ppCamera ) = &m_Camera;
	}
}

