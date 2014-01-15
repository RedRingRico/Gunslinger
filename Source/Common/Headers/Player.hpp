#ifndef __GUNSLINGER_PLAYER_HPP__
#define __GUNSLINGER_PLAYER_HPP__

#include <System/DataTypes.hpp>
#include <Utility/FirstPersonCamera.hpp>
#include <Arithmetic/Vector3.hpp>
#include <Arithmetic/AABB.hpp>

namespace Gunslinger
{
	class Player
	{
	public:
		Player( );
		~Player( );

		void SetPosition( const ZED::Arithmetic::Vector3 &p_Position );

		void GetCamera( ZED::Utility::Camera **p_ppCamera );

	private:
		ZED::Utility::FirstPersonCamera	m_Camera;
		ZED::Arithmetic::Vector3		m_Position;
		ZED::Arithmetic::AABB			m_BoundingBox;
	};
}

#endif // __GUNSLINGER_PLAYER_HPP__

