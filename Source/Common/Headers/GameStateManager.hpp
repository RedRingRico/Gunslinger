#ifndef __GUNSLINGER_GAMESTATEMANAGER_HPP__
#define __GUNSLINGER_GAMESTATEMANAGER_HPP__

#include <System/DataTypes.hpp>
#include <stack>
#include <set>

namespace Gunslinger
{
	class GameState;

	class GameStateManager
	{
	public:
		GameStateManager( );
		~GameStateManager( );

		ZED_UINT32 Initialise( );

		ZED_UINT32 Execute( );

		ZED_UINT32 RegisterState( GameState * const &p_pGameState );
		ZED_UINT32 GetNumberOfStates( ) const;
		ZED_CHAR8* GetStateName( const ZED_UINT32 p_Index ) const;

		ZED_UINT32 ChangeState( const ZED_CHAR8 *p_pGameStateName );

		ZED_UINT32 PushState( const ZED_CHAR8 *p_pGameStateName );
		ZED_UINT32 PopState( );

		void Quit( );

		ZED_BOOL Running( ) const;

		static GameStateManager &GetInstance( );

	private:
		typedef std::stack< GameState * > GameStateStack;
		typedef std::set< GameState * > GameStateSet;

		GameStateStack				m_GameStateStack;
		GameStateSet				m_GameStateRegistry;
		ZED_BOOL					m_Running;
		ZED_UINT64					m_StartTime;

		ZED_BOOL IsGameStateNameValid(
			const ZED_CHAR8 *p_pGameStateName ) const;
	};
}

#endif // __GUNSLINGER_GAMESTATEMANAGER_HPP__

