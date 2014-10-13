#ifndef __GUNSLINGER_GAMEENTITYCOMPONENT_HPP__
#define __GUNSLINGER_GAMEENTITYCOMPONENT_HPP__

#include <System/DataTypes.hpp>

namespace Gunslinger
{
	class GameEntityComponent
	{
	public:
		virtual ~GameEntityComponent( );

		template< typename T > T *GetData( ) const
			{ return reinterpret_cast< T* >( m_pData ); }

		ZED_UINT32 GetID( ) const;

	protected:
		void *m_pData;
		ZED_UINT32 m_ID;
	};
}

#endif // __GUNSLINGER_GAMEENTITYCOMPONENT_HPP__

