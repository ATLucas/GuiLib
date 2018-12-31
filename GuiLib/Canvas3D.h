#pragma once

#include <SFML/OpenGL.hpp>
#include "Component.h"


class Canvas3D: public Component
{
public:

    Canvas3D( const std::string &name = "<NameNotSet>" ) : Component( name ) {};

    virtual void initialize( sf::RenderWindow &window ) override;

    virtual void update( sf::RenderWindow &window ) override;

    virtual void draw( sf::RenderWindow &window ) override;

private:

    sf::Clock m_clock;

}; // end class Canvas3D