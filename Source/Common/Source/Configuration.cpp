#include <Configuration.hpp>
#include <System/Memory.hpp>
#include <System/Debugger.hpp>
#include <cstring>
#include <string>

namespace Gunslinger
{
	Configuration::Configuration( ) :
		m_pFilePath( ZED_NULL )
	{
	}

	Configuration::~Configuration( )
	{
		zedSafeDeleteArray( m_pFilePath );
	}

	ZED_UINT32 Configuration::Read( const ZED_CHAR8 *p_pFilePath )
	{
		if( p_pFilePath )
		{
			// TODO
			// Absolute and relative file paths, relative ones should be
			// relative to the executable's directory
			ZED_MEMSIZE FilePathLength = strlen( p_pFilePath );
			m_pFilePath = new ZED_CHAR8[ FilePathLength + 1 ];
			strncpy( m_pFilePath, p_pFilePath, FilePathLength );
			m_pFilePath[ FilePathLength ] = '\0';
		}
		else
		{
			ZED_CHAR8 *pExecutableDirectory = new ZED_CHAR8[ ZED_MAX_PATH ];
			ZED_CHAR8 *pCompletePath = new ZED_CHAR8[ ZED_MAX_PATH ];

			memset( pExecutableDirectory, '\0',
				sizeof( ZED_CHAR8 ) * ZED_MAX_PATH );
			memset( pCompletePath, '\0', sizeof( ZED_CHAR8 ) * ZED_MAX_PATH );

			ZED::System::GetExecutablePath( &pExecutableDirectory,
				ZED_MAX_PATH );
			ZED_CHAR8 *pDefaultConfiguration = "gunslinger.config";

			strcat( pCompletePath, pExecutableDirectory );
			strcat( pCompletePath, pDefaultConfiguration );

			ZED_MEMSIZE FilePathLength = strlen( pCompletePath );
			m_pFilePath = new ZED_CHAR8[ FilePathLength + 1];
			strncpy( m_pFilePath, pCompletePath, FilePathLength );
			m_pFilePath[ FilePathLength ] = '\0';

			zedSafeDeleteArray( pCompletePath );
			zedSafeDeleteArray( pExecutableDirectory );
		}

		if( ZED::System::FileExists( m_pFilePath, ZED_FALSE ) )
		{
			ZED::System::NativeFile File;
			if( File.Open( m_pFilePath, ZED::System::FILE_ACCESS_READ ) !=
				ZED_OK )
			{
				return ZED_FAIL;
			}

			if( this->ProcessFile( &File ) != ZED_OK )
			{
				File.Close( );

				return ZED_FAIL;
			}

			File.Close( );
		}
		else
		{
			return ZED_FAIL;
		}

		std::vector< std::string >::const_iterator LineIterator =
			m_Lines.begin( );

		std::string CurrentType( "Global" );
		zedTrace( "\n\n" );

		while( LineIterator != m_Lines.end( ) )
		{
			if( ( *LineIterator ).find_first_of( "[" ) == 0 )
			{
				ZED_MEMSIZE CloseBracket =
					( *LineIterator ).find_first_of( "]" );
				if( CloseBracket != std::string::npos )
				{
					CurrentType = ( *LineIterator ).substr( 1,
						CloseBracket - 1 );

					this->TrimWhiteSpace( CurrentType );

					++LineIterator;

					zedTrace( "\nCurrent Type: %s\n", CurrentType.c_str( ) );

					continue;
				}
			}
			ZED_MEMSIZE TokenPosition = ( *LineIterator ).find_first_of( "=" );
			if( TokenPosition != std::string::npos )
			{
				std::string Key = ( *LineIterator ).substr( 0, TokenPosition );
				std::string Value =
					( *LineIterator ).substr( TokenPosition + 1 );

				this->TrimWhiteSpace( Key );
				this->TrimWhiteSpace( Value );
				
				zedTrace( "Key: %s | Value: %s\n",
					Key.c_str( ), Value.c_str( ) );
			}
			++LineIterator;
		}

		return ZED_OK;
	}

	ZED_UINT32 Configuration::Write( const ZED_CHAR8 *p_pFilePath )
	{
		return ZED_OK;
	}

	ZED_UINT32 Configuration::GetXPosition( ) const
	{
		return m_X;
	}

	ZED_UINT32 Configuration::GetYPosition( ) const
	{
		return m_Y;
	}

	ZED_UINT32 Configuration::GetWidth( ) const
	{
		return m_Width;
	}

	ZED_UINT32 Configuration::GetHeight( ) const
	{
		return m_Height;
	}

	void Configuration::SetXPosition( const ZED_UINT32 p_X )
	{
		m_X = p_X;
	}

	void Configuration::SetYPosition( const ZED_UINT32 p_Y )
	{
		m_Y = p_Y;
	}

	void Configuration::SetWidth( const ZED_UINT32 p_Width )
	{
		m_Width = p_Width;
	}

	void Configuration::SetHeight( const ZED_UINT32 p_Height )
	{
		m_Height = p_Height;
	}

	ZED_UINT32 Configuration::ProcessFile( ZED::System::NativeFile *p_pFile )
	{
		ZED_MEMSIZE FileSize = p_pFile->GetSize( );
		const ZED_MEMSIZE BufferLength = 1024;
		ZED_CHAR8 *pFileBuffer = new ZED_CHAR8[ BufferLength ];
		ZED_MEMSIZE ReadLength = 0;
		std::string TempString;
		std::string CurrentLine;
		std::string CarryOver = "";

		while( FileSize > 0 )
		{
			memset( pFileBuffer, '\0', BufferLength * sizeof( ZED_CHAR8 ) );

			if( FileSize > BufferLength )
			{
				p_pFile->ReadByte(
					reinterpret_cast< ZED_BYTE * >( pFileBuffer ),
					BufferLength, &ReadLength );
				FileSize -= BufferLength;
			}
			else
			{
				p_pFile->ReadByte(
					reinterpret_cast< ZED_BYTE * >( pFileBuffer ),
					FileSize, &ReadLength );
				FileSize -= FileSize;
			}

			if( !CarryOver.empty( ) )
			{
				CurrentLine += CarryOver;
				CarryOver.clear( );
			}

			TempString = pFileBuffer;
			TempString.resize( BufferLength );

			ZED_MEMSIZE FirstLineFeed = TempString.find_first_of( "\n" );
			ZED_MEMSIZE LastLineFeed = TempString.find_last_of( "\n" );

			if( ( FirstLineFeed == std::string::npos ) ||
				( LastLineFeed == std::string::npos ) )
			{
				CurrentLine += TempString;
				continue;
			}

			ZED_MEMSIZE CursorPosition = 0;
			ZED_MEMSIZE NextLineFeed = 0;

			while( NextLineFeed != LastLineFeed )
			{
				if( CursorPosition == BufferLength )
				{
					break;
				}

				NextLineFeed = TempString.find_first_of( "\n",
					CursorPosition+1 );
				ZED_MEMSIZE LineLength = NextLineFeed - CursorPosition;
				CurrentLine += TempString.substr(
					CursorPosition, LineLength );
				CursorPosition = NextLineFeed;
				this->TrimWhiteSpace( CurrentLine );
				if( !CurrentLine.empty( ) )
				{
					m_Lines.push_back( CurrentLine );
					CurrentLine.clear( );
				}
			}

			if( LastLineFeed != BufferLength )
			{
				if( LastLineFeed == 0 )
				{
					this->TrimWhiteSpace( CurrentLine );
					m_Lines.push_back( CurrentLine );
					CurrentLine.clear( );
				}

				CarryOver = TempString.substr( LastLineFeed+1,
					BufferLength - LastLineFeed + 1 );
				
				// End of file
				if( FileSize == 0 )
				{
					CurrentLine += CarryOver;
					this->TrimWhiteSpace( CurrentLine );

					if( !CurrentLine.empty( ) )
					{
						m_Lines.push_back( CurrentLine );
					}
				}
			}
		}

		zedSafeDeleteArray( pFileBuffer );

		zedTrace( "-----------------------------\n" );
		zedTrace( "Gunslinger Configuration File\n" );
		zedTrace( "-----------------------------\n" );

		ZED_MEMSIZE LineCounter = 0;
		std::vector< std::string >::const_iterator LineIterator =
			m_Lines.begin( );

		while( LineIterator != m_Lines.end( ) )
		{
			zedTrace( "[%d] %s\n", LineCounter, ( *LineIterator ).c_str( ) );
			++LineCounter;
			++LineIterator;
		}

		return ZED_OK;
	}

	void Configuration::TrimWhiteSpace( std::string &p_String )
	{
		ZED_MEMSIZE LeadPosition = 0;
		ZED_MEMSIZE TrailPosition = 0;
		ZED_MEMSIZE FirstCharPosition = 0;
		ZED_MEMSIZE LastCharPosition = 0;

		LeadPosition = p_String.find_first_of( " \n\t\r" );
		FirstCharPosition = p_String.find_first_not_of( " \n\t\r" );
	
		// Blank line
		if( FirstCharPosition == std::string::npos )
		{
			p_String = "";
			return;
		}

		if( p_String[ 0 ] == 0x00 )
		{
			p_String = "";
			return;
		}

		if( LeadPosition != std::string::npos )
		{
			if( LeadPosition < FirstCharPosition )
			{
				p_String = p_String.substr( FirstCharPosition,
					p_String.size( ) - LeadPosition );
			}
		}

		TrailPosition = p_String.find_last_of( " \n\t\r" );
		LastCharPosition = p_String.find_last_not_of( " \n\t\r" );

		if( TrailPosition != std::string::npos )
		{
			if( TrailPosition > LastCharPosition )
			{
				p_String = p_String.substr( 0, TrailPosition );
			}
		}
	}
}

