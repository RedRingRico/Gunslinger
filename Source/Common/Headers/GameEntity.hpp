#ifndef __GUNSLINGER_GAMEENTITY_HPP__
#define __GUNSLINGER_GAMEENTITY_HPP__

#include <System/DataTypes.hpp>
#include <Arithmetic/Quaternion.hpp>
#include <Arithmetic/Vector3.hpp>

namespace Gunslinger
{
	class GameEntityType
	{
	public:
		GameEntityType( );
		ZED_EXPLICIT GameEntityType( const ZED_CHAR8 *p_pName,
			const ZED_BOOL p_Unique );
		GameEntityType( const GameEntityType &p_Type );
		~GameEntityType( );

		ZED_UINT32 GetID( ) const;
		const ZED_CHAR8 *GetName( ) const;

		GameEntityType &operator=( const GameEntityType &p_Type );

		ZED_BOOL operator==( const GameEntityType &p_Type );

		ZED_BOOL IsUnique( ) const;

	private:
		ZED_UINT32	m_ID;
		ZED_CHAR8	*m_pName;
		ZED_BOOL	m_Unique;
	};

	class GameEntity
	{
	public:
		ZED_EXPLICIT GameEntity( const GameEntityType &p_EntityType,
			const ZED_UINT32 p_ID );
		virtual ~GameEntity( );

		virtual ZED_UINT32 Initialise( ) = 0;

		virtual void Update( const ZED_UINT64 p_ElapsedTime );

		virtual void Render( ) = 0;

		void GetPosition( ZED::Arithmetic::Vector3 *p_pPoistion ) const;
		virtual void SetPosition( const ZED::Arithmetic::Vector3 &p_Position );

		void Move( const ZED_FLOAT32 p_X, const ZED_FLOAT32 p_Y,
			const ZED_FLOAT32 p_Z );

		void GetOrientation(
			ZED::Arithmetic::Quaternion *p_pOrientation ) const;
		virtual void SetOrientation(
			const ZED::Arithmetic::Quaternion &p_Orientation );

		void Rotate( const ZED_FLOAT32 p_Angle,
			const ZED::Arithmetic::Vector3 &p_Axis );

		void GetGameEntityType( GameEntityType *p_pType ) const;

		ZED_UINT32 GetID( ) const;

	protected:
		GameEntityType	m_Type;
		ZED_UINT32		m_ID;

		ZED::Arithmetic::Vector3	m_Position;
		ZED::Arithmetic::Vector3	m_Velocity;
		ZED::Arithmetic::Quaternion	m_Orientation;
		ZED::Arithmetic::Quaternion	m_Rotation;
	};
}

#endif // __GUNSLINGER_GAMEENTITY_HPP__

