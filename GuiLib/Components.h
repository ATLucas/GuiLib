#pragma once

#include "Component.h"


class TextDisplay: public Component
{
public:

    TextDisplay( const std::string &name = "<NameNotSet>" ) : Component( name ) {};

    void setFont( const sf::Font &font );

    void setTextSize( unsigned int size );

    void setTextColor( sf::Color color );
    
    void setText( const std::string &text );


    // Overrides of existing Component functions:

    virtual void updateSizeAndPostion( void ) override;

    virtual void draw( sf::RenderWindow &window ) override;


    // Implementations of pure-virtual Component functions:

    virtual float getFitWidth( void ) override;

    virtual float getFitHeight( void ) override;

private:

    sf::Text m_text;
};

class Button: public TextDisplay
{
public:

    class Listener
    {
    public:

        virtual void onClicked( void ) = 0;
    };

    Button( const std::string &name = "<NameNotSet>" ) : TextDisplay( name ) {};

    void setListener( Listener *listener ) { m_listener = listener; }

protected:

    virtual void onMousePressed( int x, int y ) override;

    virtual void onMouseReleased( int x, int y ) override;

private:

    Listener *m_listener = nullptr;
};