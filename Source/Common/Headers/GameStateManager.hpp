#ifndef __GUNSLINGER_GAMESTATEMANAGER_HPP__
#define __GUNSLINGER_GAMESTATEMANAGER_HPP__

#include <Renderer/Font.hpp>
#include <Renderer/Text.hpp>
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

