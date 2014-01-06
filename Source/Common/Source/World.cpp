#include <World.hpp>
#include <Player.hpp>
#include <GameStateManager.hpp>

namespace Gunslinger
{
	World::World( )
	{
		ZED_COLOUR GridColour;
		GridColour.Red = 1.0f;
		GridColour.Green = 1.0f;
		GridColour.Blue = 0.0f;

		m_Grid = ZED::Utility::Grid( GameStateManager::GetInstance( ).GetRenderer( ) );

		m_Grid.Initialise( 100, 100, ZED::Utility::PLANE_AXIS_XZ, GridColour,
			0.0f, 1.0f );
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

