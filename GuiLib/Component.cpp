
#include "Component.h"

using namespace sf;


Component::Component( void )
{
    // Component fill color defaults to black
    setColor( sf::Color::Black );

    // Set border shape fill color to transparent
    m_borderShape.setFillColor( sf::Color( 0, 0, 0, 0 ) );

    // Make the border a random color
    setBorderColor( sf::Color( rand() % 256, rand() % 256, rand() % 256 ) );

    // Disable the border by default
    setBorderThickness( 0 );
}

void Component::setWidth( SizeType sizeType, float width )
{
    m_requestedWidth.sizeType = sizeType;
    m_requestedWidth.value = width;
}

void Component::setHeight( SizeType sizeType, float height )
{
    m_requestedHeight.sizeType = sizeType;
    m_requestedHeight.value = height;
}

void Component::setColor( sf::Color color )
{
    m_shape.setFillColor( color );
}

void Component::setBorderThickness( float thickness )
{
    m_borderShape.setOutlineThickness( thickness );
    updateBorder();
}

void Component::setBorderColor( sf::Color color )
{
    m_borderShape.setOutlineColor( color );
}

void Component::update( void )
{
    m_shape.setSize( Vector2f( m_actualWidth, m_actualHeight ) );
    m_shape.setPosition( Vector2f( m_actualX, m_actualY ) );

    updateBorder();
}

void Component::draw( sf::RenderWindow &window )
{
    window.draw( m_shape );
    window.draw( m_borderShape );
}

void Component::updateBorder( void )
{
    m_borderShape.setPosition( m_actualX + m_borderShape.getOutlineThickness(),
                               m_actualY + m_borderShape.getOutlineThickness() );

    m_borderShape.setSize( sf::Vector2f( m_actualWidth - 2 * m_borderShape.getOutlineThickness(),
                                         m_actualHeight - 2 * m_borderShape.getOutlineThickness() ) );
}