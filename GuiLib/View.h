#pragma once

#include "Component.h"


// Exposes certain View functionality to be used internally by class Gui
class MainViewInterface
{
public:

    virtual void initialize( sf::RenderWindow &window ) = 0;

    virtual void update( sf::RenderWindow &window ) = 0;

    virtual void draw( sf::RenderWindow &window ) = 0;

    virtual void onMouseButtonPressed( int x,
                                       int y,
                                       sf::Mouse::Button button,
                                       bool inFocus ) = 0;

    virtual void onMouseButtonReleased( int x,
                                        int y,
                                        sf::Mouse::Button button,
                                        bool inFocus ) = 0;

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

    virtual void update( sf::RenderWindow &window ) override;

    virtual void draw( sf::RenderWindow &window ) override;

    virtual void setActualWidth( float width ) override { m_actualWidth = width; };

    virtual void setActualHeight( float height ) override { m_actualHeight = height; };

    virtual void onMouseButtonPressed( int x,
                                       int y,
                                       sf::Mouse::Button button,
                                       bool inFocus ) override;

    virtual void onMouseButtonReleased( int x,
                                        int y,
                                        sf::Mouse::Button button,
                                        bool inFocus ) override;

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

protected:

    virtual void onMouseButtonPressed( int x,
                                       int y,
                                       sf::Mouse::Button button,
                                       bool inFocus ) override;

    virtual void onMouseButtonReleased( int x,
                                        int y,
                                        sf::Mouse::Button button,
                                        bool inFocus ) override;

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