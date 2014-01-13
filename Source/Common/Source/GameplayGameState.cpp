#include <GameplayGameState.hpp>
#include <GameStateManager.hpp>
#include <System/Memory.hpp>
#include <Actions.hpp>
#include <GameplayEvents.hpp>
#include <Events.hpp>
#include <Utility/InputBinder.hpp>
#include <Utility/EventRouter.hpp>
#include <World.hpp>
#include <Arithmetic/Matrix4x4.hpp>
#include <Arithmetic/Vector3.hpp>

namespace Gunslinger
{
	GameplayGameState::GameplayGameState( ) :
		m_pInputListener( new GameplayInputListener( ) ),
		m_pGameWorld( new World( ) )
	{
		m_pInputBinder = new ZED::Utility::InputBinder( );
		m_pEventRouter = new ZED::Utility::EventRouter(
			"Gameplay", ZED_TRUE, 2 );

		m_DebugCamera.SetViewMode( ZED_VIEWMODE_PERSPECTIVE );
		m_DebugCamera.SetPosition( 0.0f, 0.0f, 0.0f );
		// Clip to 1cm-1Km, it's doubtful that 1Km will be needed
		m_DebugCamera.SetClippingPlanes( 1.0f, 100000.0f );
		m_DebugCamera.SetPerspectiveProjection( ZED_Pi, 1280.0f/720.0f,
			ZED_NULL );
		// Set the camera to the height of the player (the debug camera should
		// start using the position and orientation of the active camera)
		m_DebugCamera.SetPosition( 0.0f, 0.0f, 0.0f ) ;
		
		// N.B. The camera will start off looking at 0, 0, -1, which would be
		// correct if the camera were looking down from the centre, however,
		// this will need to be corrected from the current view
	}

	GameplayGameState::~GameplayGameState( )
	{
		zedSafeDelete( m_pInputBinder );
	}

	ZED_UINT32 GameplayGameState::Enter( )
	{
		m_pInputBinder->BindKey( K_ESCAPE, STATE_EXIT );
		m_pInputBinder->BindKey( K_SHIFT, DEBUG_CAMERA_MOVE_UP );
		m_pInputBinder->BindKey( K_CTRL, DEBUG_CAMERA_MOVE_DOWN );
		m_pInputBinder->BindKey( K_UPARROW, DEBUG_CAMERA_MOVE_FORWARD );
		m_pInputBinder->BindKey( K_DOWNARROW, DEBUG_CAMERA_MOVE_BACKWARD );
		m_pInputBinder->BindKey( K_LEFTARROW, DEBUG_CAMERA_MOVE_LEFT );
		m_pInputBinder->BindKey( K_RIGHTARROW, DEBUG_CAMERA_MOVE_RIGHT );
		m_pInputBinder->BindKey( K_PGUP, DEBUG_CAMERA_LOOK_UP );
		m_pInputBinder->BindKey( K_PGDN, DEBUG_CAMERA_LOOK_DOWN );
		m_pInputBinder->BindKey( K_HOME, DEBUG_CAMERA_LOOK_LEFT );
		m_pInputBinder->BindKey( K_END, DEBUG_CAMERA_LOOK_LEFT );
		GameStateManager::GetInstance( ).SetInputBinder( m_pInputBinder );

		m_pEventRouter->Add( m_pInputListener, ActionInputEventType );

		m_pInputListener->SetGameplayGameState( this );

		return ZED_OK;
	}

	void GameplayGameState::Render( )
	{
		GameStateManager::GetInstance( ).GetRenderer( )->ClearColour(
			0.14f, 0.0f, 0.14f );

		ZED::Arithmetic::Matrix4x4 ProjectionViewMatrix;
		m_DebugCamera.GetProjectionViewMatrix( &ProjectionViewMatrix );
		m_pGameWorld->Render( &ProjectionViewMatrix );
	}

	void GameplayGameState::Update( const ZED_UINT64 p_ElapsedTime )
	{
		m_DebugCamera.Update( p_ElapsedTime );
		m_DebugCamera.Rotate( 0.0f, 
			ZED::Arithmetic::Vector3( 1.0f, 1.0f, 1.0f ) );
	}

	ZED_UINT32 GameplayGameState::Exit( )
	{
		GameStateManager::GetInstance( ).PopState( );
		return ZED_OK;
	}

	ZED_CHAR8 *GameplayGameState::GetName( ) const
	{
		return "Gameplay";
	}

	ZED::Utility::FreeCamera *GameplayGameState::GetDebugCamera( )
	{
		return &m_DebugCamera;
	}
}

