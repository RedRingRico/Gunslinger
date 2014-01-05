#ifndef __GUNSLINGER_GAMEPLAYEVENTS_HPP__
#define __GUNSLINGER_GAMEPLAYEVENTS_HPP__

#include <System/DataTypes.hpp>
#include <Utility/Event.hpp>

namespace Gunslinger
{
	class GameplayGameState;

	class GameplayInputListener : public ZED::Utility::EventListener
	{
	public:
		GameplayInputListener( );
		virtual ~GameplayInputListener( );

		virtual ZED_BOOL HandleEvent( const ZED::Utility::Event &p_Event );

		virtual ZED_CHAR8 *Name( ) const;

		ZED_UINT32 SetGameplayGameState(
			GameplayGameState * const &p_pGameplayGameState );

	private:
		GameplayGameState	*m_pGameplayGameState;
	};
}

#endif // __GUNSLINGER_GAMEPLAYEVENTS_HPP__

