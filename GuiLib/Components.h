#pragma once

#include "Component.h"


class TextDisplay: public Component
{
public:

    void setFont( const sf::Font &font );

    void setTextSize( unsigned int size );

    void setTextColor( sf::Color color );
    
    void setText( const std::string &text );

    virtual void updateSizeAndPostion( void ) override;

    virtual void draw( sf::RenderWindow &window ) override;

private:

    sf::Text m_text;
};