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

    // Exposed via MainViewInterface:

    virtual void update( void ) override;

    virtual void draw( sf::RenderWindow &window ) override;

    virtual void setActualWidth( float width ) override { m_actualWidth = width; };

    virtual void setActualHeight( float height ) override { m_actualHeight = height; };


    // Only used internally by views:

    virtual void updateChildren( void ) = 0;

    std::vector<std::shared_ptr<Component>> m_children;

}; // end class View


class LayeredView: public View
{

protected:

    virtual void updateChildren( void ) override;

}; // end class LayeredView


class HorizontalView: public View
{

protected:

    virtual void updateChildren( void ) override;

}; // end class HorizontalView


class VerticalView: public View
{

protected:

    virtual void updateChildren( void ) override;

}; // end class VerticalView