#pragma once

#include <SFML/Graphics.hpp>
#include <stdlib.h>


class Component
{
    // Declare views to be friends so that they can
    // access the protected members of their children.
    friend class View;
    friend class LayeredView;
    friend class HorizontalView;
    friend class VerticalView;

public:

    enum class SizeType
    {
        Absolute,
        Percent,
        Fill
    };

    void setWidth( SizeType sizeType, float width = 0 );

    void setHeight( SizeType sizeType, float height = 0 );

    void setColor( sf::Color color );

    void setBorderThickness( float thickness );

    void setBorderColor( sf::Color color );

protected:

    Component( void );

    virtual void update( void );

    virtual void draw( sf::RenderWindow &window );

    struct SizeRequest
    {
        SizeType sizeType = SizeType::Absolute;
        float value = 0.0f;
    };

    SizeRequest m_requestedWidth;
    SizeRequest m_requestedHeight;

    float m_actualX = 0;
    float m_actualY = 0;
    float m_actualWidth = 0;
    float m_actualHeight = 0;

private:

    void updateBorder( void );

    sf::RectangleShape m_shape;
    sf::RectangleShape m_borderShape;
};