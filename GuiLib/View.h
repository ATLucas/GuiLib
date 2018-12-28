#pragma once

#include "Component.h"


// Exposes certain View functionality to be used internally by class Gui
class MainViewInterface
{
public:

    virtual void update( void ) = 0;

    virtual void draw( sf::RenderWindow &window ) = 0;

    virtual void setActualWidth( float width ) = 0;

    virtual void setActualHeight( float width ) = 0;

}; // end class MainViewInterface


class View: public Component, public MainViewInterface
{
public:

    void addChild( std::shared_ptr<Component> childView );

protected:

    View( void ) : Component() {};


    // Exposed via MainViewInterface:

    virtual void update( void ) override;

    virtual void draw( sf::RenderWindow &window ) override;

    virtual void setActualWidth( float width ) override { m_actualWidth = width; };

    virtual void setActualHeight( float height ) override { m_actualHeight = height; };


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

    LayeredView( void ) : View() {};

}; // end class LayeredView


class HorizontalView: public View
{
public:

    HorizontalView( void ) : View() {};

protected:

    virtual void updateChildWidths( void ) override;

    virtual void updateChildXValues( void ) override;

}; // end class HorizontalView


class VerticalView: public View
{
public:

    VerticalView( void ) : View() {};

protected:

    virtual void updateChildHeights( void ) override;

    virtual void updateChildYValues( void ) override;

}; // end class VerticalView