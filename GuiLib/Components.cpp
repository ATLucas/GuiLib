
#include "Components.h"

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

    m_text.setPosition( m_actualX + m_leftPadding,
                        m_actualY + m_topPadding );
}

void TextDisplay::draw( RenderWindow &window )
{
    Component::draw( window );

    window.draw( m_text );
}