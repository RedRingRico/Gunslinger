#ifndef __GUNSLINGER_GAMESTATEMANAGER_HPP__
#define __GUNSLINGER_GAMESTATEMANAGER_HPP__

#include <System/DataTypes.hpp>
#include <Utility/InputBinder.hpp>
#include <Renderer/Renderer.hpp>
#include <Renderer/OGL/GLFont.hpp>
#include <Renderer/Text.hpp>
#include <stack>
#include <set>

namespace Gunslinger
{
	class GameState;
	class GameStateInputListener;

	const ZED_FLOAT64 OneOverMillion = 1.0d / 1000000.0d;

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

		ZED_FLOAT64 GetTotalElapsedTimeAsFloat64( ) const;
		ZED_UINT64 GetTotalElapsedTimeAsUInt64( ) const;

		static GameStateManager &GetInstance( );

		void SetWindowDimensions( const ZED_UINT32 p_Width,
			const ZED_UINT32 p_Height );

	private:
		typedef std::stack< GameState * > GameStateStack;
		typedef std::set< GameState * > GameStateSet;

		GameStateStack				m_GameStateStack;
		GameStateSet				m_GameStateRegistry;
		ZED_BOOL					m_Running;
		ZED_UINT64					m_StartTime;

		ZED_BOOL IsGameStateNameValid(
			const ZED_CHAR8 *p_pGameStateName ) const;

		ZED::Renderer::Renderer		*m_pRenderer;

		GameStateInputListener		*m_pInputListener;

		ZED_UINT64					m_TotalElapsedTime;

		ZED::Renderer::Font			*m_pFont;
		ZED::Renderer::Text			m_Text;
		ZED_UINT64					m_FrameReset;
		ZED_UINT32					m_FrameCount;
		ZED_UINT32					m_FrameRate;
		ZED_BOOL					m_DrawFrameRate;

		ZED_UINT32		m_WindowWidth;
		ZED_UINT32		m_WindowHeight;
	};
}

#endif // __GUNSLINGER_GAMESTATEMANAGER_HPP__

