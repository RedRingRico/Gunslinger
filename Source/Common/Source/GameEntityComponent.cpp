#include <GameEntityComponent.hpp>

namespace Gunslinger
{
	GameEntityComponent::~GameEntityComponent( )
	{
	}

	ZED_UINT32 GameEntityComponent::GetID( ) const
	{
		return m_ID;
	}
}

