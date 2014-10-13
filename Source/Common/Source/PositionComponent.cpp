#include <PositionComponent.hpp>

namespace Gunslinger
{
	PositionComponent::PositionComponent( ) :
		m_X( 0.0f ),
		m_Y( 0.0f ),
		m_Z( 0.0f )
	{
		m_pData = &m_X;
	}

	PositionComponent::~PositionComponent( )
	{
	}
}

