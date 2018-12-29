
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

    m_text.setPosition( m_actualX + m_leftPadding - m_text.getLocalBounds().left,
                        m_actualY + m_topPadding - m_text.getLocalBounds().top );
}

void TextDisplay::draw( RenderWindow &window )
{
    Component::draw( window );

    window.draw( m_text );
}

float TextDisplay::getFitWidth( void )
{
    float returnValue = m_text.getLocalBounds().width + m_leftPadding + m_rightPadding - m_text.getLocalBounds().left;
    cout << "getFitWidth [" << m_name << "]: " << returnValue << endl;
    return returnValue;
}

float TextDisplay::getFitHeight( void )
{
    float returnValue = m_text.getCharacterSize() + m_topPadding + m_botPadding - m_text.getLocalBounds().top;
    cout << "getFitHeight [" << m_name << "]: " << returnValue << endl;
    return returnValue;
}