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
#include <Renderer/OGL/GLFont.hpp>
#include <GitVersion.hpp>
#include <GameEntity.hpp>
#include <GameEntityManager.hpp>

namespace Gunslinger
{
	GameplayGameState::GameplayGameState( ) :
		m_pInputListener( new GameplayInputListener( ) ),
		m_pGameWorld( new World( ) ),
		m_DebugCameraActive( ZED_FALSE ),
		m_pActiveCamera( ZED_NULL ),
		m_pPreviousCamera( ZED_NULL ),
		//m_pActiveActor( ZED_NULL ),
		m_60HzTimer( 0ULL ),
		m_100HzTimer( 0ULL )
	{
		m_pInputBinder = new ZED::Utility::InputBinder( );
		m_pEventRouter = new ZED::Utility::EventRouter(
			"Gameplay", ZED_TRUE, 2 );

		m_DebugCamera.SetViewMode( ZED_VIEWMODE_PERSPECTIVE );
		// Clip to 1cm-1Km, it's doubtful that 1Km will be needed
		m_DebugCamera.SetClippingPlanes( 1.0f, 100000.0f );
		m_DebugCamera.SetPerspectiveProjection( 45.0f, 1280.0f / 720.0f,
			ZED_NULL );

		// Set the camera to the height of the player (the debug camera should
		// start using the position and orientation of the active camera)

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
		zedTrace( "Entering Gameplay\n" );
		ZED::Utility::SetGlobalEventRouter( this->m_pEventRouter );
		m_pInputBinder->BindKey( ZED_KEY_ESCAPE, STATE_EXIT );
		m_pInputBinder->BindKey( ZED_KEY_F1, DEBUG_CAMERA_TOGGLE );
		m_pInputBinder->BindKey( ZED_KEY_Q, DEBUG_CAMERA_MOVE_UP );
		m_pInputBinder->BindKey( ZED_KEY_E, DEBUG_CAMERA_MOVE_DOWN );
		m_pInputBinder->BindKey( ZED_KEY_W, DEBUG_CAMERA_MOVE_FORWARD );
		m_pInputBinder->BindKey( ZED_KEY_S, DEBUG_CAMERA_MOVE_BACKWARD );
		m_pInputBinder->BindKey( ZED_KEY_A, DEBUG_CAMERA_MOVE_LEFT );
		m_pInputBinder->BindKey( ZED_KEY_D, DEBUG_CAMERA_MOVE_RIGHT );
		m_pInputBinder->BindMouseAxis( ZED_MOUSE_AXIS_X,
			DEBUG_CAMERA_LOOK_HORIZONTAL );
		m_pInputBinder->BindMouseAxis( ZED_MOUSE_AXIS_Y,
			DEBUG_CAMERA_LOOK_VERTICAL );
		m_pInputBinder->BindKey( ZED_KEY_W, PLAYER_MOVE_FORWARD );
		m_pInputBinder->BindKey( ZED_KEY_S, PLAYER_MOVE_BACKWARD );
		m_pInputBinder->BindKey( ZED_KEY_A, PLAYER_MOVE_LEFT );
		m_pInputBinder->BindKey( ZED_KEY_D, PLAYER_MOVE_RIGHT );
		m_pInputBinder->BindMouseAxis( ZED_MOUSE_AXIS_X,
			PLAYER_LOOK_HORIZONTAL );
		m_pInputBinder->BindMouseAxis( ZED_MOUSE_AXIS_Y,
			PLAYER_LOOK_VERTICAL );
		GameStateManager::GetInstance( ).SetInputBinder( m_pInputBinder );

		m_pEventRouter->Add( m_pInputListener, ActionInputEventType );

		m_pInputListener->SetGameplayGameState( this );
/*
		m_GameEntityManager.CreateEntity( PlayerGameEntityType );
		GameEntity *pPlayer = ZED_NULL;
		m_GameEntityManager.GetEntityByID( 0, &pPlayer );*/

		/*reinterpret_cast< Player * >( pPlayer )->SetPosition(
			ZED::Arithmetic::Vector3( 0.0f, 0.0f, 0.0f ) );
		reinterpret_cast< Player * >( pPlayer )->GetCamera( &m_pActiveCamera );*/

		GameStateManager::GetInstance( ).GetRenderer( )->ClearColour(
			0.14f, 0.0f, 0.14f );

		
		m_PlayerID = GameEntityManager::GetInstance( ).CreateEntity( );

		zedTrace( "Created player entity with an ID of '%d'\n", m_PlayerID );

		GameEntityManager::GetInstance( ).SetEntityComponents( m_PlayerID,
			ENTITY_TYPE_POSITION | ENTITY_TYPE_VELOCITY );

		GameEntityManager::GetInstance( ).PrintAllEntityComponents( );

		//m_GameEntityManager.GetEntityByID( 0, &m_pActiveActor );

		return ZED_OK;
	}

	void GameplayGameState::Render( )
	{
		ZED::Arithmetic::Matrix4x4 ProjectionViewMatrix;
		//m_pActiveCamera->GetProjectionViewMatrix( &ProjectionViewMatrix );

		m_pGameWorld->Render( &ProjectionViewMatrix );
	}

	void GameplayGameState::Update( const ZED_UINT64 p_ElapsedTime )
	{
		static ZED_UINT32 UpdateCounter = 0UL;
		m_60HzTimer += p_ElapsedTime;
		m_100HzTimer += p_ElapsedTime;

		while( m_60HzTimer >= 16667ULL )
		{
		//	m_pActiveCamera->Update( p_ElapsedTime );
			m_60HzTimer -= 16667ULL;
			++UpdateCounter;
		}
		while( m_100HzTimer >= 10000ULL )
		{
		//	m_GameEntityManager.Update( p_ElapsedTime );
			m_100HzTimer -= 10000ULL;
		}
	}

	ZED_UINT32 GameplayGameState::Exit( )
	{
		// FIXME
		// I'd like to find a way to pop this off the stack and not have the
		// GSM try to pop it again, instead of calling quit (maybe
		// changestate?)
		GameStateManager::GetInstance( ).Quit( );
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

/*	ZED::Utility::FirstPersonCamera *GameplayGameState::GetPlayerCamera( )
	{
		GameEntity *pPlayer = ZED_NULL;
		m_GameEntityManager.GetEntityByID( 0, &pPlayer );*/

		/*ZED::Utility::Camera *pReturn;

		reinterpret_cast< Player * >( pPlayer )->GetCamera( &pReturn );

		return reinterpret_cast< ZED::Utility::FirstPersonCamera * >(
			pReturn );
	}*/
/*
	Player *GameplayGameState::GetPlayer( )
	{
		GameEntity *pPlayer = ZED_NULL;
		m_GameEntityManager.GetEntityByID( 0, &pPlayer );

		return reinterpret_cast< Player * >( pPlayer );
	}

	GameEntity *GameplayGameState::GetActiveActor( )
	{
		return m_pActiveActor;
	}
*/
	void GameplayGameState::ToggleDebugCamera( )
	{
		m_DebugCameraActive = !m_DebugCameraActive;

		if( m_DebugCameraActive )
		{
			// Only when there's an active camera will the debug camera use it
			// as a basis for its orientation and position
			if( m_pActiveCamera )
			{
				ZED::Arithmetic::Vector3 ActivePosition;
				ZED::Arithmetic::Quaternion ActiveOrientation;

				m_pActiveCamera->GetPosition( &ActivePosition );
				m_pActiveCamera->GetOrientation( &ActiveOrientation );

				m_DebugCamera.SetPosition( ActivePosition );
				m_DebugCamera.SetOrientation( ActiveOrientation );

				m_pPreviousCamera = m_pActiveCamera;
				m_pActiveCamera = &m_DebugCamera;
			}
		}
		else
		{
			if( m_pPreviousCamera )
			{
				m_pActiveCamera = m_pPreviousCamera;
			}
		}
	}

	ZED_BOOL GameplayGameState::DebugCameraActive( ) const
	{
		return m_DebugCameraActive;
	}
}

