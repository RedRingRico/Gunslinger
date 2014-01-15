#ifndef __GUNSLINGER_PLAYER_HPP__
#define __GUNSLINGER_PLAYER_HPP__

#include <System/DataTypes.hpp>
#include <Utility/FirstPersonCamera.hpp>
#include <Arithmetic/Vector3.hpp>
#include <Arithmetic/AABB.hpp>
#include <GameEntity.hpp>

namespace Gunslinger
{
	class Player : public GameEntity
	{
	public:
		ZED_EXPLICIT Player( const ZED_UINT32 p_ID );
		virtual ~Player( );

		virtual ZED_UINT32 Initialise( );

		virtual void Update( const ZED_UINT64 p_ElapsedTime );

		virtual void Render( );

		virtual void SetPosition( const ZED::Arithmetic::Vector3 &p_Position );

		virtual void SetOrientation(
			const ZED::Arithmetic::Quaternion &p_Orientation );

		void GetCamera( ZED::Utility::Camera **p_ppCamera );

	private:
		Player( const Player &p_Player );
		Player &operator=( const Player &p_Player );

		ZED::Utility::FirstPersonCamera	m_Camera;
		ZED::Arithmetic::AABB			m_BoundingBox;
	};
}

#endif // __GUNSLINGER_PLAYER_HPP__

