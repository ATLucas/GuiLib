
#include "CubeMaker.h"

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
    string fontLocation = "fonts/Montserrat/Montserrat-Medium.ttf";

    if ( !m_monserratFont.loadFromFile( fontLocation ) )
        cerr << "Failed to load font: " << fontLocation << endl;

    shared_ptr<View> mainView = getMainView();

    shared_ptr<HorizontalView> topMenu = make_shared<HorizontalView>( "Top Menu" );
    topMenu->setWidth( Component::SizeType::Fill );
    topMenu->setHeight( Component::SizeType::Fit );
    topMenu->setColor( sf::Color( 50, 50, 60 ) );
    topMenu->setPadding( 10 );
    
    shared_ptr<TextDisplay> openButton = make_shared<TextDisplay>( "Open Button" );
    openButton->setWidth( Component::SizeType::Fit );
    openButton->setHeight( Component::SizeType::Fit );
    openButton->setText( "Open" );
    openButton->setFont( m_monserratFont );
    openButton->setTextSize( 24 );
    openButton->setTextColor( sf::Color::White );
    openButton->setPadding( 10 );
    openButton->setMargin( 10 );

    shared_ptr<TextDisplay> saveButton = make_shared<TextDisplay>( "Save Button" );
    saveButton->setWidth( Component::SizeType::Fit );
    saveButton->setHeight( Component::SizeType::Fit );
    saveButton->setText( "Save" );
    saveButton->setFont( m_monserratFont );
    saveButton->setTextSize( 24 );
    saveButton->setTextColor( sf::Color::White );
    saveButton->setPadding( 10 );
    saveButton->setMargin( 10 );

    shared_ptr<LayeredView> canvas = make_shared<LayeredView>( "Canvas" );
    canvas->setWidth( Component::SizeType::Fill );
    canvas->setHeight( Component::SizeType::Fill );

    mainView->addChild( topMenu );
    mainView->addChild( canvas );
    topMenu->addChild( openButton );
    topMenu->addChild( saveButton );
}

void CubeMaker::shutdown( void )
{

}