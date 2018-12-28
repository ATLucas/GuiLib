#pragma once

#include "GuiLib.h"


class CubeMaker: public Gui
{
private:

    virtual Config getConfig( void ) override;

    virtual void init( void ) override;

    virtual void shutdown( void ) override;

    sf::Font m_monserratFont;
};