
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
        m_mainView = make_shared<LayeredView>( "Main View" );
    else if ( m_config.mainViewLayout == ViewLayout::Horizontal )
        m_mainView = make_shared<HorizontalView>( "Main View" );
    else if ( m_config.mainViewLayout == ViewLayout::Vertical )
        m_mainView = make_shared<VerticalView>( "Main View" );

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
            {
                m_window.close();
            }
            else if ( event.type == sf::Event::Resized )
            {
                // Adjust the SFML view.
                m_window.setView( sf::View(
                    sf::FloatRect( 0.0f, 0.0f, (float) event.size.width, (float) event.size.height ) ) );

                // Set the size of the main view.
                m_mainViewInterface->setActualWidth( (float) event.size.width );
                m_mainViewInterface->setActualHeight( (float) event.size.height );

                // Update the view hierarchy.
                m_mainViewInterface->updateSizeAndPostion();
            }
            else if ( event.type == sf::Event::MouseButtonPressed )
            {
                if ( event.mouseButton.button == 0 )
                {
                    m_mainViewInterface->onMousePressed( event.mouseButton.x, event.mouseButton.y );

                    // Update the view hierarchy.
                    m_mainViewInterface->updateSizeAndPostion();
                }
            }
            else if ( event.type == sf::Event::MouseButtonReleased )
            {
                if ( event.mouseButton.button == 0 )
                {
                    m_mainViewInterface->onMouseReleased( event.mouseButton.x, event.mouseButton.y );

                    // Update the view hierarchy.
                    m_mainViewInterface->updateSizeAndPostion();
                }
            }
            else if ( event.type == sf::Event::MouseMoved )
            {
                m_mainViewInterface->onMouseMoved( event.mouseMove.x, event.mouseMove.y );

                // Update the view hierarchy.
                m_mainViewInterface->updateSizeAndPostion();
            }
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