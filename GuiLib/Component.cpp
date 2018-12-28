
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
    if ( width < 0 )
        return;

    m_requestedWidth.sizeType = sizeType;
    m_requestedWidth.value = width;
}

void Component::setHeight( SizeType sizeType, float height )
{
    if ( height < 0 )
        return;

    m_requestedHeight.sizeType = sizeType;
    m_requestedHeight.value = height;
}

void Component::setColor( const sf::Color &color )
{
    m_shape.setFillColor( color );
}

void Component::setBorderThickness( float thickness )
{
    if ( thickness < 0 )
        return;

    m_borderShape.setOutlineThickness( thickness );
    updateBorder();
}

void Component::setBorderColor( const sf::Color &color )
{
    m_borderShape.setOutlineColor( color );
}

void Component::setPadding( float padding, Side side )
{
    if ( padding < 0 )
        return;

    if ( side == Side::All || side == Side::Left || side == Side::LeftAndRight )
        m_leftPadding = padding;

    if ( side == Side::All || side == Side::Right || side == Side::LeftAndRight )
        m_rightPadding = padding;

    if ( side == Side::All || side == Side::Top || side == Side::TopAndBottom )
        m_topPadding = padding;

    if ( side == Side::All || side == Side::Bottom || side == Side::TopAndBottom )
        m_botPadding = padding;
}

void Component::setMargin( float margin, Side side )
{
    if ( margin < 0 )
        return;

    if ( side == Side::All || side == Side::Left || side == Side::LeftAndRight )
        m_leftMargin = margin;

    if ( side == Side::All || side == Side::Right || side == Side::LeftAndRight )
        m_rightMargin = margin;

    if ( side == Side::All || side == Side::Top || side == Side::TopAndBottom )
        m_topMargin = margin;

    if ( side == Side::All || side == Side::Bottom || side == Side::TopAndBottom )
        m_botMargin = margin;
}

void Component::updateSizeAndPostion( void )
{
    m_contentX = m_actualX + m_leftPadding;
    m_contentY = m_actualY + m_topPadding;
    m_contentWidth = m_actualWidth - m_leftPadding - m_rightPadding;
    m_contentHeight = m_actualHeight - m_topPadding - m_botPadding;

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