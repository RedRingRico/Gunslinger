#include <World.hpp>
#include <Player.hpp>
#include <GameStateManager.hpp>

namespace Gunslinger
{
	World::World( )
	{
		m_Grid = ZED::Utility::Grid(
			GameStateManager::GetInstance( ).GetRenderer( ) );

		ZED_COLOUR GridColour;
		// Floor
		GridColour.Red = 1.0f;
		GridColour.Green = 1.0f;
		GridColour.Blue = 0.0f;
		m_Grid.Initialise( 200, 200, ZED::Utility::PLANE_AXIS_XZ,
			GridColour, 0.0f, 50.0f );
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
		m_Grid.Render( p_pProjectionViewMatrix );
	}
}

