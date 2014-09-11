#ifndef __GUNSLINGER_GAMESTATEMANAGER_HPP__
#define __GUNSLINGER_GAMESTATEMANAGER_HPP__

#include <Renderer/Font.hpp>
#include <Renderer/Text.hpp>
/*
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

		void ShowFPS( );
		void HideFPS( );

		void ShowFrameTime( );
		void HideFrameTime( );

		void ShowBuildInfo( );
		void HideBuildInfo( );

		void ShowBeatTime( );
		void HideBeatTime( );

		void ShowElapsedTime( );
		void HideElapsedTime( );

		void ShowAllOverlays( );
		void HideAllOverlays( );

	private:
		ZED_UINT32 RenderFPS( );
		ZED_UINT32 RenderFrameTime( const ZED_UINT64 p_FrameTime );
		ZED_UINT32 RenderBuildInfo( );
		ZED_UINT32 RenderBeatTime( );
		ZED_UINT32 RenderElapsedTime( );

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

		ZED_BOOL	m_RenderFPS;
		ZED_BOOL	m_RenderFrameTime;
		ZED_BOOL	m_RenderBuildInfo;
		ZED_BOOL	m_RenderBeatTime;
		ZED_BOOL	m_RenderElapsedTime;
	};
}
*/

#include <Game/GameStateManager.hpp>

namespace ZED
{
	namespace Game
	{
		class GameState;
		class GameStateInputListener;
	}
}

namespace Gunslinger
{
	class GameStateManager : public ZED::Game::GameStateManager
	{
	public:
		GameStateManager( );
		virtual ~GameStateManager( );

		virtual ZED_UINT32 Initialise( );

		static GameStateManager &GetInstance( );

		void SetWindowDimensions( const ZED_UINT32 p_Width,
			const ZED_UINT32 p_Height );

		void ShowFPS( );
		void HideFPS( );

		void ShowFrameTime( );
		void HideFrameTime( );

		void ShowBuildInfo( );
		void HideBuildInfo( );

		void ShowBeatTime( );
		void HideBeatTime( );

		void ShowElapsedTime( );
		void HideElapsedTime( );

		void ShowAllOverlays( );
		void HideAllOverlays( );

	protected:
		virtual ZED_UINT32 Update( const ZED_UINT64 p_DeltaTime );
		virtual ZED_UINT32 Render( );
	
	private:
		ZED_UINT32 RenderFPS( );
		ZED_UINT32 RenderFrameTime( const ZED_UINT64 p_FrameTime );
		ZED_UINT32 RenderBuildInfo( );
		ZED_UINT32 RenderBeatTime( );
		ZED_UINT32 RenderElapsedTime( );

		ZED::Renderer::Font		*m_pOverlayFont;
		ZED::Renderer::Text		m_OverlayText;
		ZED_UINT64				m_FrameReset;
		ZED_UINT32				m_FrameCount;
		ZED_UINT32				m_FrameRate;
		ZED_BOOL				m_DrawFrameRate;

		ZED_UINT32		m_WindowWidth;
		ZED_UINT32		m_WindowHeight;

		ZED_BOOL	m_RenderFPS;
		ZED_BOOL	m_RenderFrameTime;
		ZED_BOOL	m_RenderBuildInfo;
		ZED_BOOL	m_RenderBeatTime;
		ZED_BOOL	m_RenderElapsedTime;
	};
}

#endif // __GUNSLINGER_GAMESTATEMANAGER_HPP__

