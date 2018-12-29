#pragma once

#include "View.h"
#include "Text.h"
#include "Canvas3D.h"


class Gui
{
public:

    enum class ViewLayout
    {
        Layered,
        Horizontal,
        Vertical
    };

    struct Config
    {
        std::string title;
        int width;
        int height;
        bool isFullscreen;
        ViewLayout mainViewLayout;
    };

    virtual Config getConfig( void ) = 0;

    virtual void initialize( void ) = 0;

    virtual void shutdown( void ) = 0;

    void run( void );

    std::shared_ptr<View> getMainView( void );

private:

    Config m_config;

    sf::RenderWindow m_window;

    std::shared_ptr<View> m_mainView;

    std::shared_ptr<MainViewInterface> m_mainViewInterface;

}; // end class Gui