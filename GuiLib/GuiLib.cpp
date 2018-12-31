
#include "GuiLib.h"

using namespace std;


void Gui::run( void )
{
    m_config = getConfig();

    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;

    m_window.create( sf::VideoMode( m_config.width, m_config.height ),
                     m_config.title,
                     m_config.isFullscreen ? sf::Style::Fullscreen : sf::Style::Default,
                     contextSettings );

    m_window.setVerticalSyncEnabled( true );

    if ( m_config.mainViewLayout == ViewLayout::Layered )
        m_mainView = make_shared<LayeredView>( "Main View" );
    else if ( m_config.mainViewLayout == ViewLayout::Horizontal )
        m_mainView = make_shared<HorizontalView>( "Main View" );
    else if ( m_config.mainViewLayout == ViewLayout::Vertical )
        m_mainView = make_shared<VerticalView>( "Main View" );

    m_mainViewInterface = dynamic_pointer_cast<MainViewInterface>( m_mainView );

    // Set the main view to fill the window.
    m_mainViewInterface->setActualWidth( static_cast<float>( m_window.getSize().x ) );
    m_mainViewInterface->setActualHeight( static_cast<float>( m_window.getSize().y ) );

    initialize();

    m_mainViewInterface->initialize( m_window );

    while ( m_window.isOpen() )
    {
        sf::Event event;

        while ( m_window.pollEvent( event ) )
        {
            if ( event.type == sf::Event::Closed )
            {
                m_window.close();
                break;
            }
            
            if ( event.type == sf::Event::Resized )
            {
                // Adjust the SFML view.
                m_window.setView( sf::View( sf::FloatRect(
                    0.0f,
                    0.0f,
                    static_cast<float>( event.size.width ),
                    static_cast<float>( event.size.height ) ) ) );

                // Set the size of the main view.
                m_mainViewInterface->setActualWidth( static_cast<float>( event.size.width ) );
                m_mainViewInterface->setActualHeight( static_cast<float>( event.size.height ) );
            }
            else if ( event.type == sf::Event::MouseButtonPressed )
            {
                m_mainViewInterface->onMouseButtonPressed( event.mouseButton.x,
                                                           event.mouseButton.y,
                                                           event.mouseButton.button,
                                                           true );
            }
            else if ( event.type == sf::Event::MouseButtonReleased )
            {
                m_mainViewInterface->onMouseButtonReleased( event.mouseButton.x,
                                                            event.mouseButton.y,
                                                            event.mouseButton.button,
                                                            true );
            }
            else if ( event.type == sf::Event::TextEntered )
            {
                if ( event.text.unicode < 128 )
                    m_mainViewInterface->onTextEntered( static_cast<char>( event.text.unicode ) );
            }
            else if ( event.type == sf::Event::KeyPressed )
            {
                if ( event.key.code == sf::Keyboard::Escape )
                {
                    m_window.close();
                    break;
                }
            }
        }

        // Update the view hierarchy.
        m_mainViewInterface->update( m_window );

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