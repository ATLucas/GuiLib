
#include "Components.h"
#include <iostream>

using namespace sf;
using namespace std;


void TextDisplay::setFont( const sf::Font &font )
{
    m_text.setFont( font );
}

void TextDisplay::setTextSize( unsigned int size )
{
    m_text.setCharacterSize( size );
}

void TextDisplay::setTextColor( sf::Color color )
{
    m_text.setFillColor( color );
}

void TextDisplay::setText( const string &text )
{
    m_text.setString( text );
}

void TextDisplay::updateSizeAndPostion( void )
{
    Component::updateSizeAndPostion();

    m_text.setPosition( m_actualX + getModeState().leftPadding - m_text.getLocalBounds().left,
                        m_actualY + getModeState().topPadding - m_text.getLocalBounds().top );
}

void TextDisplay::draw( RenderWindow &window )
{
    Component::draw( window );

    if ( getFitWidth() <= m_actualWidth && getFitHeight() <= m_actualHeight )
        window.draw( m_text );
}

float TextDisplay::getFitWidth( void )
{
    return m_text.getLocalBounds().width +
        getModeState().leftPadding +
        getModeState().rightPadding -
        m_text.getLocalBounds().left;
}

float TextDisplay::getFitHeight( void )
{
    return m_text.getCharacterSize() +
        getModeState().topPadding +
        getModeState().botPadding -
        m_text.getLocalBounds().top;
}

void Button::onMousePressed( int x, int y )
{
    if ( containsPoint( x, y ) )
    {
        if ( getMode() == Mode::Inactive || getMode() == Mode::Hovering )
            setMode( Mode::Active );
    }
}

void Button::onMouseReleased( int x, int y )
{
    if ( getMode() == Mode::Active )
    {
        if ( containsPoint( x, y ) )
            setMode( Mode::Hovering );
        else
            setMode( Mode::Inactive );

        if ( m_listener )
            m_listener->onClicked();
    }
}