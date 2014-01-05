#ifndef __GUNSLINGER_GAMESTATEMANAGER_HPP__
#define __GUNSLINGER_GAMESTATEMANAGER_HPP__

#include <System/DataTypes.hpp>
#include <Utility/InputBinder.hpp>
#include <Renderer/Renderer.hpp>
#include <stack>
#include <set>

namespace Gunslinger
{
	class GameState;
	class GameStateInputListener;

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

		ZED_UINT32 SetInputBinder(
			ZED::Utility::InputBinder * const &p_pInputBinder );

		void Quit( );

		ZED_BOOL Running( ) const;

		ZED::Renderer::Renderer * const GetRenderer( );
		ZED_UINT32 SetRenderer( ZED::Renderer::Renderer * const &p_pRenderer );

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

		ZED::Utility::InputBinder	*m_pInputBinder;
		ZED::Renderer::Renderer		*m_pRenderer;

		GameStateInputListener		*m_pInputListener;
	};
}

#endif // __GUNSLINGER_GAMESTATEMANAGER_HPP__

