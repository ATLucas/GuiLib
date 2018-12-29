#pragma once

#include "Component.h"


class Canvas3D: public Component
{
public:

    Canvas3D( const std::string &name = "<NameNotSet>" ) : Component( name ) {};
};