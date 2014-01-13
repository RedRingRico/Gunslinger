#include <World.hpp>
#include <Player.hpp>
#include <GameStateManager.hpp>

namespace Gunslinger
{
	World::World( )
	{
		ZED_COLOUR GridColour;


		for( ZED_MEMSIZE i = 0; i < 6; ++i )
		{
			m_Grid[ i ] = ZED::Utility::Grid(
				GameStateManager::GetInstance( ).GetRenderer( ) );
		}

		// Floor
		GridColour.Red = 1.0f;
		GridColour.Green = 1.0f;
		GridColour.Blue = 0.0f;
		m_Grid[ 0 ].Initialise( 100, 100, ZED::Utility::PLANE_AXIS_XZ,
			GridColour, -50.0f, 1.0f );

		// Ceiling
		GridColour.Red = 1.0f;
		GridColour.Green = 0.0f;
		GridColour.Blue = 0.0f;
		m_Grid[ 1 ].Initialise( 100, 100, ZED::Utility::PLANE_AXIS_XZ,
			GridColour, 50.0f, 1.0f );

		// Left
		GridColour.Red = 0.0f;
		GridColour.Green = 1.0f;
		GridColour.Blue = 0.0f;
		m_Grid[ 2 ].Initialise( 100, 100, ZED::Utility::PLANE_AXIS_YZ,
			GridColour, -50.0f, 1.0f );
		
		// Right
		GridColour.Red = 0.0f;
		GridColour.Green = 0.0f;
		GridColour.Blue = 1.0f;
		m_Grid[ 3 ].Initialise( 100, 100, ZED::Utility::PLANE_AXIS_YZ,
			GridColour, 50.0f, 1.0f );

		// Front
		GridColour.Red = 1.0f;
		GridColour.Green = 0.0f;
		GridColour.Blue = 1.0f;
		m_Grid[ 4 ].Initialise( 100, 100, ZED::Utility::PLANE_AXIS_XY,
			GridColour, 50.0f, 1.0f );

		// Back
		GridColour.Red = 0.0f;
		GridColour.Green = 1.0f;
		GridColour.Blue = 1.0f;
		m_Grid[ 5 ].Initialise( 100, 100, ZED::Utility::PLANE_AXIS_XY,
			GridColour, -50.0f, 1.0f );
	}

	World::~World( )
	{
	}

	void World::Update( const ZED_UINT64 p_ElapsedTime )
	{
	}

	void World::Render(
		ZED::Arithmetic::Matrix4x4 * const &p_pProjectionViewMatrix )
	{
		for( ZED_MEMSIZE i = 0; i < 6; ++i )
		{
			m_Grid[ i ].Render( p_pProjectionViewMatrix );
		}
	}
}

