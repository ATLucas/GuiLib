
#include "GuiLib.h"

using namespace std;


void Gui::run( void )
{
    m_config = getConfig();

    m_window.create( sf::VideoMode( m_config.width, m_config.height ),
                     m_config.title,
                     m_config.isFullscreen ? sf::Style::Fullscreen : sf::Style::Default );

    m_window.setVerticalSyncEnabled( true );

    if ( m_config.mainViewLayout == ViewLayout::Layered )
        m_mainView = make_shared<LayeredView>();
    else if ( m_config.mainViewLayout == ViewLayout::Horizontal )
        m_mainView = make_shared<HorizontalView>();
    else if ( m_config.mainViewLayout == ViewLayout::Vertical )
        m_mainView = make_shared<VerticalView>();

    m_mainViewInterface = dynamic_pointer_cast<MainViewInterface>( m_mainView );

    // Set the main view to fill the window.
    m_mainViewInterface->setActualWidth( (float) m_window.getSize().x );
    m_mainViewInterface->setActualHeight( (float) m_window.getSize().y );

    init();

    m_mainViewInterface->updateSizeAndPostion();

    while ( m_window.isOpen() )
    {
        sf::Event event;

        while ( m_window.pollEvent( event ) )
        {
            if ( event.type == sf::Event::Closed )
                m_window.close();
        }

        m_window.clear();

        m_mainViewInterface->draw( m_window );

        m_window.display();
    }

    shutdown();
}

std::shared_ptr<View> Gui::getMainView( void )
{
    return m_mainView;
}