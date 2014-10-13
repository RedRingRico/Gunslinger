#ifndef __GUNSLINGER_POSITIONCOMPONENT_HPP__
#define __GUNSLINGER_POSITIONCOMPONENT_HPP__

#include <GameEntityComponent.hpp>
#include <System/DataTypes.hpp>

namespace Gunslinger
{
	class PositionComponent : public GameEntityComponent
	{
	public:
		PositionComponent( );
		virtual ~PositionComponent( );

		ZED_FLOAT32 Set( const ZED_FLOAT32 p_X, const ZED_FLOAT32 p_Y,
			const ZED_FLOAT32 p_Z );
		ZED_FLOAT32 Get( ZED_FLOAT32 &p_X, ZED_FLOAT32 &p_Y,
			ZED_FLOAT32 &p_Z );

	private:
		ZED_FLOAT32 m_X, m_Y, m_Z;
	};
}

#endif // __GUNSLINGER_POSITIONCOMPONENT_HPP__

