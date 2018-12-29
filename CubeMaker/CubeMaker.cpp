
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
    
    shared_ptr<Button> openButton = make_shared<Button>( "Open Button" );
    openButton->setWidth( Component::SizeType::Fit );
    openButton->setHeight( Component::SizeType::Fit );
    openButton->setText( "Open" );
    openButton->setFont( m_monserratFont );
    openButton->setTextSize( 24 );
    openButton->setTextColor( sf::Color::White );
    openButton->setPadding( 10 );
    openButton->setMargin( 10 );
    openButton->setColor( sf::Color::Green, Component::Mode::Active );
    openButton->setBorderThickness( 1, Component::Mode::Hovering );
    openButton->setBorderColor( sf::Color::Green, Component::Mode::Hovering );
    openButton->setListener( &m_openButtonListener );

    shared_ptr<Button> saveButton = make_shared<Button>( "Save Button" );
    saveButton->setWidth( Component::SizeType::Fit );
    saveButton->setHeight( Component::SizeType::Fit );
    saveButton->setText( "Save" );
    saveButton->setFont( m_monserratFont );
    saveButton->setTextSize( 24 );
    saveButton->setTextColor( sf::Color::White );
    saveButton->setPadding( 10 );
    saveButton->setMargin( 10 );
    saveButton->setColor( sf::Color::Green, Component::Mode::Active );
    saveButton->setBorderThickness( 1, Component::Mode::Hovering );
    saveButton->setBorderColor( sf::Color::Green, Component::Mode::Hovering );
    saveButton->setListener( &m_saveButtonListener );

    shared_ptr<TextInput> textInput = make_shared<TextInput>( "Text Input" );
    textInput->setWidth( Component::SizeType::Fill );
    textInput->setHeight( Component::SizeType::Fill );
    textInput->setFont( m_monserratFont );
    textInput->setTextSize( 24 );
    textInput->setTextColor( sf::Color::White );
    textInput->setPadding( 10 );
    textInput->setMargin( 10 );
    textInput->setBorderThickness( 1, Component::Mode::Active );
    textInput->setBorderColor( sf::Color::Green, Component::Mode::Active );
    textInput->setListener( &m_textInputListener );

    shared_ptr<Canvas3D> canvas = make_shared<Canvas3D>( "Canvas" );
    canvas->setWidth( Component::SizeType::Fill );
    canvas->setHeight( Component::SizeType::Fill );

    mainView->addChild( topMenu );
    mainView->addChild( canvas );
    topMenu->addChild( openButton );
    topMenu->addChild( saveButton );
    topMenu->addChild( textInput );
}

void CubeMaker::shutdown( void )
{

}

void CubeMaker::OpenButtonListener::onClicked( void )
{
    cout << "Clicked the open button" << endl;
}

void CubeMaker::SaveButtonListener::onClicked( void )
{
    cout << "Clicked the save button" << endl;
}

void CubeMaker::TextInputListener::onTextSubmitted( const std::string &text )
{
    cout << "Received submitted text: " << text << endl;
}