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

    class TextInputListener: public TextInput::Listener
    {
        void onTextSubmitted( const std::string &text );
    };

    virtual Config getConfig( void ) override;

    virtual void initialize( void ) override;

    virtual void shutdown( void ) override;

    sf::Font m_monserratFont;

    OpenButtonListener m_openButtonListener;

    SaveButtonListener m_saveButtonListener;

    TextInputListener m_textInputListener;
};