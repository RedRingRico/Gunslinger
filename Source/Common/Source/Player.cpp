#include <Player.hpp>
#include <Arithmetic/Vector4.hpp>

namespace Gunslinger
{
	Player::Player( const ZED_UINT32 p_ID ) :
		GameEntity( PlayerGameEntityType, p_ID ),
		m_HeadOffset( 0.0f )
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
		m_HeadOffset = 170.0f;
		return ZED_OK;
	}

	void Player::Update( const ZED_UINT64 p_ElapsedTime )
	{
		this->SetPosition( m_Position );
	}

	void Player::Render( )
	{
	}

	void Player::SetPosition( const ZED::Arithmetic::Vector3 &p_Position )
	{
		ZED::Arithmetic::Matrix4x4 HeadCameraInverseView;
		m_Camera.GetViewMatrix( &HeadCameraInverseView );

		HeadCameraInverseView.AffineInverse( );

		ZED::Arithmetic::Vector4 HeadRight;
		HeadCameraInverseView.GetColumn( 0, HeadRight );
		m_Position[ 0 ] += HeadRight[ 0 ] * m_Velocity[ 0 ];
		m_Position[ 2 ] += HeadRight[ 2 ] * m_Velocity[ 0 ];

		ZED::Arithmetic::Vector4 HeadForward;
		HeadCameraInverseView.GetColumn( 2, HeadForward );
		m_Position[ 0 ] += HeadForward[ 0 ] * m_Velocity[ 2 ];
		m_Position[ 2 ] += HeadForward[ 2 ] * m_Velocity[ 2 ];
		
		GameEntity::SetPosition( m_Position );
		// This should really be based on the player's stance, such as whether
		// the player is standing or crouching
		m_Camera.SetPosition( m_Position[ 0 ], m_Position[ 1 ] + m_HeadOffset,
			m_Position[ 2 ] );
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

	void Player::RotateHead( const ZED_FLOAT32 p_Angle,
		const ZED::Arithmetic::Vector3 &p_Axis )
	{
		m_Camera.Rotate( p_Angle, p_Axis );

		// TODO
		// When the head is rotated about the Y axis more than n radians, the
		// whole body should move
	}
}

