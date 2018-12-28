
#include "CubeMaker.h"
#include <iostream>

using namespace std;


int main( void )
{
    CubeMaker CubeMaker;
    CubeMaker.run();

    return 0;
}

Gui::Config CubeMaker::getConfig( void )
{
    Gui::Config config;

    config.title = "CubeMaker";
    config.width = 1600;
    config.height = 900;
    config.isFullscreen = false;
    config.mainViewLayout = ViewLayout::Vertical;

    return config;
}

void CubeMaker::init( void )
{
    cout << "Beginning CubeMaker::init()" << endl;

    string fontLocation = "fonts/Montserrat/Montserrat-Medium.ttf";

    if ( !m_monserratFont.loadFromFile( fontLocation ) )
        cerr << "Failed to load font: " << fontLocation << endl;

    shared_ptr<View> mainView = getMainView();

    shared_ptr<HorizontalView> topMenu = make_shared<HorizontalView>();
    topMenu->setWidth( View::SizeType::Fill );
    topMenu->setHeight( View::SizeType::Percent, 10 );
    topMenu->setColor( sf::Color( 50, 50, 60 ) );
    topMenu->setBorderThickness( 2 );
    
    shared_ptr<TextDisplay> firstSelection = make_shared<TextDisplay>();
    firstSelection->setWidth( View::SizeType::Percent, 10 );
    firstSelection->setHeight( View::SizeType::Percent, 90 );
    firstSelection->setBorderThickness( 2 );
    firstSelection->setText( "Open" );
    firstSelection->setFont( m_monserratFont );
    firstSelection->setTextSize( 24 );
    firstSelection->setTextColor( sf::Color::White );

    shared_ptr<TextDisplay> secondSelection = make_shared<TextDisplay>();
    secondSelection->setWidth( View::SizeType::Percent, 10 );
    secondSelection->setHeight( View::SizeType::Percent, 90 );
    secondSelection->setBorderThickness( 2 );
    secondSelection->setText( "Save" );
    secondSelection->setFont( m_monserratFont );
    secondSelection->setTextSize( 24 );
    secondSelection->setTextColor( sf::Color::White );

    // Canvas?
    shared_ptr<LayeredView> canvas = make_shared<LayeredView>();
    canvas->setWidth( View::SizeType::Fill );
    canvas->setHeight( View::SizeType::Fill );
    canvas->setBorderThickness( 2 );

    mainView->addChild( topMenu );
    mainView->addChild( canvas );
    topMenu->addChild( firstSelection );
    topMenu->addChild( secondSelection );

    cout << "Done with CubeMaker::init()" << endl;
}

void CubeMaker::shutdown( void )
{
    cout << "Beginning CubeMaker::shutdown()" << endl;

    cout << "Done with CubeMaker::shutdown()" << endl;
}