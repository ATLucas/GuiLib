#pragma once

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>


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
        Fill,
        Fit
    };

    void setWidth( SizeType sizeType, float width = 0 );

    void setHeight( SizeType sizeType, float height = 0 );

    void setColor( const sf::Color &color );

    void setBorderThickness( float thickness );

    void setBorderColor( const sf::Color &color );

    enum class Side
    {
        Left,
        Right,
        Top,
        Bottom,
        LeftAndRight,
        TopAndBottom,
        All
    };

    void setPadding( float padding, Side side = Side::All );

    void setMargin( float margin, Side side = Side::All );

protected:

    Component( const std::string &name );

    virtual void updateSizeAndPostion( void );

    virtual void draw( sf::RenderWindow &window );

    virtual float getFitWidth( void ) = 0;

    virtual float getFitHeight( void ) = 0;

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

    float m_contentX = 0;
    float m_contentY = 0;
    float m_contentWidth = 0;
    float m_contentHeight = 0;

    float m_leftPadding = 0;
    float m_rightPadding = 0;
    float m_topPadding = 0;
    float m_botPadding = 0;

    float m_leftMargin = 0;
    float m_rightMargin = 0;
    float m_topMargin = 0;
    float m_botMargin = 0;

    bool m_validSizeAndPosition = true;

    std::string m_name;

private:

    void updateBorder( void );

    sf::RectangleShape m_shape;
    sf::RectangleShape m_borderShape;
};