#ifndef __GUNSLINGER_GAMESTATEMANAGER_HPP__
#define __GUNSLINGER_GAMESTATEMANAGER_HPP__

#include <System/DataTypes.hpp>
#include <stack>
#include <vector>

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

		ZED_UINT32 ChangeState( const ZED_CHAR8 *p_pStateName );

		ZED_UINT32 PushState( const ZED_CHAR8 *p_pStateName );
		ZED_UINT32 PopState( );

		static GameStateManager &GetInstance( );

	private:
		typedef std::stack< GameState * > GameStateStack;

		GameStateStack	m_StateStack;

		std::vector< GameState * > m_GameStateRegistry;
	};
}

#endif // __GUNSLINGER_GAMESTATEMANAGER_HPP__

