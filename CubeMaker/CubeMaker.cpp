
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

    shared_ptr<View> mainView = getMainView();

    shared_ptr<HorizontalView> topMenu = make_shared<HorizontalView>();
    topMenu->setWidth( View::SizeType::Fill );
    topMenu->setHeight( View::SizeType::Percent, 10 );
    topMenu->setBorderThickness( 2 );

    // TextDisplay?
    shared_ptr<LayeredView> firstSelection = make_shared<LayeredView>();
    firstSelection->setWidth( View::SizeType::Percent, 10 );
    firstSelection->setHeight( View::SizeType::Percent, 90 );
    firstSelection->setBorderThickness( 2 );

    // TextDisplay?
    shared_ptr<LayeredView> secondSelection = make_shared<LayeredView>();
    secondSelection->setWidth( View::SizeType::Percent, 10 );
    secondSelection->setHeight( View::SizeType::Percent, 90 );
    secondSelection->setBorderThickness( 2 );

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