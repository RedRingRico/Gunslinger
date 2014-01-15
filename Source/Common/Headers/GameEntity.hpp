#ifndef __GUNSLINGER_GAMEENTITY_HPP__
#define __GUNSLINGER_GAMEENTITY_HPP__

#include <System/DataTypes.hpp>
#include <Arithmetic/Quaternion.hpp>
#include <Arithmetic/Vector3.hpp>

namespace Gunslinger
{
	class GameEntity
	{
	public:
		ZED_EXPLICIT GameEntity( const ZED_CHAR8 *p_pName,
			const ZED_UINT32 p_ID );
		virtual ~GameEntity( );

		virtual ZED_UINT32 Initialise( ) = 0;

		virtual void Update( const ZED_UINT64 p_ElapsedTime ) = 0;

		virtual void Render( ) = 0;

		void GetPosition( ZED::Arithmetic::Vector3 *p_pPoistion ) const;
		virtual void SetPosition( const ZED::Arithmetic::Vector3 &p_Position );

		void GetOrientation(
			ZED::Arithmetic::Quaternion *p_pOrientation ) const;
		virtual void SetOrientation(
			const ZED::Arithmetic::Quaternion &p_Orientation );

	protected:
		ZED_UINT32	m_ID;
		ZED_UINT32	m_Type;
		ZED_CHAR8	*m_pName;

		ZED::Arithmetic::Vector3	m_Position;
		ZED::Arithmetic::Quaternion	m_Orientation;
	};
}

#endif // __GUNSLINGER_GAMEENTITY_HPP__

