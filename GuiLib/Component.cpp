
#include "Component.h"

using namespace sf;
using namespace std;

Component::Component( const string &name ): m_name( name )
{
    for ( Mode mode : m_modes )
    {
        // Allocate mode-specific state
        m_modeState[ mode ] = make_shared<ModeState>();

        // Set border shape fill color to transparent
        getModeState( mode ).borderShape.setFillColor( sf::Color( 0, 0, 0, 0 ) );

        // Component fill color defaults to black
        setColor( sf::Color::Black, mode );

        // Make the border a random color
        setBorderColor( sf::Color( rand() % 256, rand() % 256, rand() % 256 ), mode );

        // Disable the border by default
        setBorderThickness( 0, mode );
    }
}

void Component::initialize( sf::RenderWindow &window )
{

}

void Component::updateSizeAndPostion( sf::RenderWindow &window )
{
    ModeState &modeState = getModeState();

    float leftPadding = modeState.leftPadding;
    float topPadding = modeState.topPadding;
    float rightPadding = modeState.rightPadding;
    float botPadding = modeState.botPadding;

    m_contentX = m_actualX + leftPadding;
    m_contentY = m_actualY + topPadding;
    m_contentWidth = m_actualWidth - leftPadding - rightPadding;
    m_contentHeight = m_actualHeight - topPadding - botPadding;

    modeState.shape.setSize( Vector2f( m_actualWidth, m_actualHeight ) );
    modeState.shape.setPosition( Vector2f( m_actualX, m_actualY ) );

    float borderThickness = modeState.borderShape.getOutlineThickness();

    modeState.borderShape.setPosition( m_actualX + borderThickness,
                                       m_actualY + borderThickness );

    modeState.borderShape.setSize( sf::Vector2f( m_actualWidth - 2 * borderThickness,
                                                 m_actualHeight - 2 * borderThickness ) );
}

void Component::draw( sf::RenderWindow &window )
{
    window.draw( getModeState().shape );
    window.draw( getModeState().borderShape );
}

void Component::setWidth( SizeType sizeType, float width, Mode mode )
{
    if ( width < 0 )
        return;

    if ( mode == Mode::All )
    {
        for ( Mode modeToUpdate : m_modes )
            setWidth( sizeType, width, modeToUpdate );
    }
    else
    {
        SizeRequest &requestedWidth = getModeState( mode ).requestedWidth;
        requestedWidth.sizeType = sizeType;
        requestedWidth.value = width;
    }
}

void Component::setHeight( SizeType sizeType, float height, Mode mode )
{
    if ( height < 0 )
        return;

    if ( mode == Mode::All )
    {
        for ( Mode modeToUpdate : m_modes )
            setHeight( sizeType, height, modeToUpdate );
    }
    else
    {
        SizeRequest &requestedHeight = getModeState( mode ).requestedHeight;
        requestedHeight.sizeType = sizeType;
        requestedHeight.value = height;
    }
}

void Component::setColor( const sf::Color &color, Mode mode )
{
    if ( mode == Mode::All )
    {
        for ( Mode modeToUpdate : m_modes )
            setColor( color, modeToUpdate );
    }
    else
    {
        getModeState( mode ).shape.setFillColor( color );
    }
}

void Component::setBorderThickness( float thickness, Mode mode )
{
    if ( thickness < 0 )
        return;

    if ( mode == Mode::All )
    {
        for ( Mode modeToUpdate : m_modes )
            setBorderThickness( thickness, modeToUpdate );
    }
    else
    {
        getModeState( mode ).borderShape.setOutlineThickness( thickness );
    }
}

void Component::setBorderColor( const sf::Color &color, Mode mode )
{
    if ( mode == Mode::All )
    {
        for ( Mode modeToUpdate : m_modes )
            setBorderColor( color, modeToUpdate );
    }
    else
    {
        getModeState( mode ).borderShape.setOutlineColor( color );
    }
}

void Component::setPadding( float padding, Side side, Mode mode )
{
    if ( padding < 0 )
        return;

    if ( mode == Mode::All )
    {
        for ( Mode modeToUpdate : m_modes )
            setPadding( padding, side, modeToUpdate );
    }
    else
    {
        ModeState &modeState = getModeState( mode );

        if ( side == Side::All || side == Side::Left || side == Side::LeftAndRight )
            modeState.leftPadding = padding;

        if ( side == Side::All || side == Side::Right || side == Side::LeftAndRight )
            modeState.rightPadding = padding;

        if ( side == Side::All || side == Side::Top || side == Side::TopAndBottom )
            modeState.topPadding = padding;

        if ( side == Side::All || side == Side::Bottom || side == Side::TopAndBottom )
            modeState.botPadding = padding;
    }
}

void Component::setMargin( float margin, Side side, Mode mode )
{
    if ( margin < 0 )
        return;

    if ( mode == Mode::All )
    {
        for ( Mode modeToUpdate : m_modes )
            setMargin( margin, side, modeToUpdate );
    }
    else
    {
        ModeState &modeState = getModeState( mode );

        if ( side == Side::All || side == Side::Left || side == Side::LeftAndRight )
            modeState.leftMargin = margin;

        if ( side == Side::All || side == Side::Right || side == Side::LeftAndRight )
            modeState.rightMargin = margin;

        if ( side == Side::All || side == Side::Top || side == Side::TopAndBottom )
            modeState.topMargin = margin;

        if ( side == Side::All || side == Side::Bottom || side == Side::TopAndBottom )
            modeState.botMargin = margin;
    }
}

void Component::onMousePressed( int x, int y )
{

}

void Component::onMouseReleased( int x, int y )
{

}

void Component::onMouseMoved( int x, int y )
{
    if ( containsPoint( x, y ) )
    {
        if ( getMode() == Mode::Inactive )
            setMode( Mode::Hovering );
    }
    else
    {
        if ( getMode() == Mode::Hovering )
            setMode( Mode::Inactive );
    }
}

void Component::onTextEntered( char c )
{

}

bool Component::containsPoint( int x, int y )
{
    float minX = m_actualX;
    float maxX = m_actualX + m_actualWidth;
    float minY = m_actualY;
    float maxY = m_actualY + m_actualHeight;

    return x >= minX && x < maxX && y >= minY && y < maxY;
}

void Component::setMode( Mode mode )
{
    m_mode = mode;
}

Component::Mode Component::getMode( void )
{
    return m_mode;
}

Component::ModeState &Component::getModeState( void )
{
    return *m_modeState[ m_mode ];
};

Component::ModeState &Component::getModeState( Mode mode )
{
    return *m_modeState[ mode ];
};