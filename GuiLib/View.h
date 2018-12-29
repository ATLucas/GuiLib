#pragma once

#include "Component.h"


// Exposes certain View functionality to be used internally by class Gui
class MainViewInterface
{
public:

    virtual void initialize( sf::RenderWindow &window ) = 0;

    virtual void updateSizeAndPostion( sf::RenderWindow &window ) = 0;

    virtual void draw( sf::RenderWindow &window ) = 0;

    virtual void onMousePressed( int x, int y ) = 0;

    virtual void onMouseReleased( int x, int y ) = 0;

    virtual void onMouseMoved( int x, int y ) = 0;

    virtual void onTextEntered( char c ) = 0;

    virtual void setActualWidth( float width ) = 0;

    virtual void setActualHeight( float width ) = 0;

}; // end class MainViewInterface


class View: public Component, public MainViewInterface
{
public:

    void addChild( std::shared_ptr<Component> childView );

protected:

    View( const std::string &name ) : Component( name ) {};


    // Exposed via MainViewInterface:

    virtual void initialize( sf::RenderWindow &window ) override;

    virtual void updateSizeAndPostion( sf::RenderWindow &window ) override;

    virtual void draw( sf::RenderWindow &window ) override;

    virtual void setActualWidth( float width ) override { m_actualWidth = width; };

    virtual void setActualHeight( float height ) override { m_actualHeight = height; };


    // Implementations of pure-virtual Component functions:

    virtual void onMousePressed( int x, int y ) override;

    virtual void onMouseReleased( int x, int y ) override;

    virtual void onMouseMoved( int x, int y ) override;

    virtual void onTextEntered( char c ) override;

    virtual float getFitWidth( void ) override;

    virtual float getFitHeight( void ) override;


    // Only used internally by views:

    virtual void updateChildWidths( void );

    virtual void updateChildHeights( void );

    virtual void updateChildXValues( void );

    virtual void updateChildYValues( void );

    std::vector<std::shared_ptr<Component>> m_children;

}; // end class View


class LayeredView: public View
{
public:

    LayeredView( const std::string &name = "<NameNotSet>" ) : View( name ) {};

}; // end class LayeredView


class HorizontalView: public View
{
public:

    HorizontalView( const std::string &name = "<NameNotSet>" ) : View( name ) {};

protected:

    virtual float getFitWidth( void ) override;

    virtual void updateChildWidths( void ) override;

    virtual void updateChildXValues( void ) override;

}; // end class HorizontalView


class VerticalView: public View
{
public:

    VerticalView( const std::string &name = "<NameNotSet>" ) : View( name ) {};

protected:

    virtual float getFitHeight( void ) override;

    virtual void updateChildHeights( void ) override;

    virtual void updateChildYValues( void ) override;

}; // end class VerticalView