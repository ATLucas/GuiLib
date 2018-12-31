
#include "Text.h"

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

void TextDisplay::update( sf::RenderWindow &window )
{
    Component::update( window );

    m_text.setPosition( m_actualX + getModeState().leftPadding,
                        m_actualY + getModeState().topPadding );
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
        getModeState().rightPadding;
}

float TextDisplay::getFitHeight( void )
{
    return m_text.getCharacterSize() +
        getModeState().topPadding +
        getModeState().botPadding;
}

void Button::onMouseButtonPressed( int x,
                                   int y,
                                   sf::Mouse::Button button,
                                   bool inFocus )
{
    if ( inFocus )
    {
        if ( getMode() == Mode::Inactive || getMode() == Mode::Hovering )
            setMode( Mode::Active );
    }
}

void Button::onMouseButtonReleased( int x,
                                    int y,
                                    sf::Mouse::Button button,
                                    bool inFocus )
{
    if ( getMode() == Mode::Active )
    {
        if ( inFocus )
            setMode( Mode::Hovering );
        else
            setMode( Mode::Inactive );

        if ( m_listener )
            m_listener->onClicked();
    }
}

void TextInput::onMouseButtonPressed( int x,
                                      int y,
                                      sf::Mouse::Button button,
                                      bool inFocus )
{
    if ( inFocus )
    {
        if ( getMode() != Mode::Active )
            setMode( Mode::Active );
    }
    else
    {
        if ( getMode() == Mode::Active )
            setMode( Mode::Inactive );
    }
}

void TextInput::onTextEntered( char c )
{
    if ( getMode() == Mode::Active )
    {
        string text = m_text.getString();

        if ( c == '\r' )
        {
            if ( m_listener )
                m_listener->onTextSubmitted( text );

            text = "";
        }
        else if ( c == '\b' )
        {
            if ( text.size() > 0 )
                text = text.substr(0, text.size() - 1);
        }
        else
        {
            text += c;
        }

        m_text.setString( text );
    }
}