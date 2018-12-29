#pragma once

#include "GuiLib.h"


class CubeMaker: public Gui
{
private:

    class OpenButtonListener : public Button::Listener
    {
        void onClicked( void );
    };

    class SaveButtonListener: public Button::Listener
    {
        void onClicked( void );
    };

    virtual Config getConfig( void ) override;

    virtual void init( void ) override;

    virtual void shutdown( void ) override;

    sf::Font m_monserratFont;

    OpenButtonListener m_openButtonListener;

    SaveButtonListener m_saveButtonListener;
};