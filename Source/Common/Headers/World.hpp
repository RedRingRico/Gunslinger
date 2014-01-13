#ifndef __GUNSLINGER_WORLD_HPP__
#define __GUNSLINGER_WORLD_HPP__

#include <Utility/Grid.hpp>
#include <Utility/Camera.hpp>
#include <Arithmetic/Matrix4x4.hpp>

namespace Gunslinger
{
	class Player;

	class World
	{
	public:
		World( );
		~World( );

		void Update( const ZED_UINT64 p_ElapsedTime );
		void Render(
			ZED::Arithmetic::Matrix4x4 * const &p_pProjectionViewMatrix );

	private:
		ZED::Utility::Grid		m_Grid[ 6 ];
		ZED::Utility::Camera	*m_pViewCamera;

		Player	*m_pPlayer;
	};
}

#endif // __GUNSLINGER_WORLD_HPP__

