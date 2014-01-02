#ifndef __GUNSLINGER_GAMESTATEEVENTS_HPP__
#define __GUNSLINGER_GAMESTATEEVENTS_HPP__

#include <System/DataTypes.hpp>
#include <Utility/Event.hpp>
#include <Utility/InputBinder.hpp>

namespace Gunslinger
{
	class GameStateInputListener : public ZED::Utility::EventListener
	{
	public:
		GameStateInputListener( );
		virtual ~GameStateInputListener( );

		virtual ZED_BOOL HandleEvent( const ZED::Utility::Event &p_Event );

		virtual ZED_CHAR8 *Name( ) const;

		ZED_UINT32 SetInputBinder(
			ZED::Utility::InputBinder * const &p_pInputBinder );
		
	private:
		ZED::Utility::InputBinder	*m_pInputBinder;
	};
}

#endif // __GUNSLINGER_GAMESTATEEVENTS_HPP__

