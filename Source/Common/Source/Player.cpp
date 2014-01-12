#include <Player.hpp>

namespace Gunslinger
{
	Player::Player( )
	{
	}

	Player::~Player( )
	{
	}

	void Player::SetPosition( const ZED::Arithmetic::Vector3 &p_Position )
	{
		m_Position = p_Position;
	}

	void Player::GetCamera( ZED::Utility::Camera *p_pCamera )
	{
		//( *p_pCamera ) = m_Camera;
	}
}

