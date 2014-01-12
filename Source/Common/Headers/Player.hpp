#ifndef __GUNSLINGER_PLAYER_HPP__
#define __GUNSLINGER_PLAYER_HPP__

#include <System/DataTypes.hpp>
#include <Utility/Camera.hpp>
#include <Arithmetic/Vector3.hpp>

namespace Gunslinger
{
	class Player
	{
	public:
		Player( );
		~Player( );

		void SetPosition( const ZED::Arithmetic::Vector3 &p_Position );

		void GetCamera( ZED::Utility::Camera *p_pCamera );

	private:
		ZED::Utility::Camera		*m_Camera;
		ZED::Arithmetic::Vector3	m_Position;
	};
}

#endif // __GUNSLINGER_PLAYER_HPP__

