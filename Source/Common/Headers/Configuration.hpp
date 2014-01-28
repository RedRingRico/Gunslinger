#ifndef __GUNSLINGER_CONFIGURATION_HPP__
#define __GUNSLINGER_CONFIGURATION_HPP__

#include <System/DataTypes.hpp>
#include <System/NativeFile.hpp>
#include <map>
#include <string>
#include <vector>

namespace Gunslinger
{
	class Configuration
	{
	public:
		Configuration( );
		~Configuration( );

		ZED_UINT32 Read( const ZED_CHAR8 *p_pFilePath = ZED_NULL );
		ZED_UINT32 Write( const ZED_CHAR8 *p_pFilePath = ZED_NULL );

		ZED_UINT32 GetXPosition( ) const;
		ZED_UINT32 GetYPosition( ) const;
		ZED_UINT32 GetWidth( ) const;
		ZED_UINT32 GetHeight( ) const;

		void SetXPosition( const ZED_UINT32 p_X );
		void SetYPosition( const ZED_UINT32 p_Y );
		void SetWidth( const ZED_UINT32 p_Width );
		void SetHeight( const ZED_UINT32 p_Height );

	private:
		typedef std::multimap< std::string,
			std::map< std::string, std::string > > TypeParameterValueMap;

		ZED_UINT32 ProcessFile( ZED::System::NativeFile *p_pFile );
		void TrimWhiteSpace( std::string &p_String );

		ZED_UINT32	m_X;
		ZED_UINT32	m_Y;
		ZED_UINT32	m_Width;
		ZED_UINT32	m_Height;

		ZED_CHAR8	*m_pFilePath;

		TypeParameterValueMap	m_TypeParameterValue;

		ZED_BOOL				m_ProcessingType;
		ZED_BOOL				m_ProcessingKey;
		ZED_BOOL				m_ProcessingValue;

		std::vector< std::string >	m_Lines;
	};
}

#endif // __GUNSLINGER_CONFIGURATION_HPP__

