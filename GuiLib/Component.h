#pragma once

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include <unordered_map>


class Component
{
    // Declare views to be friends so that they can
    // access the protected members of their children.
    friend class View;
    friend class LayeredView;
    friend class HorizontalView;
    friend class VerticalView;

public:

    enum class Mode
    {
        All,
        Active,
        Inactive,
        Hovering
    };

    std::vector<Mode> m_modes = { Mode::Active, Mode::Inactive, Mode::Hovering };

    enum class SizeType
    {
        Absolute,
        Percent,
        Fill,
        Fit
    };

    void setWidth( SizeType sizeType, float width = 0, Mode mode = Mode::All );

    void setHeight( SizeType sizeType, float height = 0, Mode mode = Mode::All );

    void setColor( const sf::Color &color, Mode mode = Mode::All );

    void setBorderThickness( float thickness, Mode mode = Mode::All );

    void setBorderColor( const sf::Color &color, Mode mode = Mode::All );

    enum class Side
    {
        All,
        Left,
        Right,
        Top,
        Bottom,
        LeftAndRight,
        TopAndBottom
    };

    void setPadding( float padding, Side side = Side::All, Mode mode = Mode::All );

    void setMargin( float margin, Side side = Side::All, Mode mode = Mode::All );

protected:

    Component( const std::string &name );

    virtual void updateSizeAndPostion( void );

    virtual void draw( sf::RenderWindow &window );

    virtual void onMousePressed( int x, int y );

    virtual void onMouseReleased( int x, int y );

    virtual void onMouseMoved( int x, int y );

    virtual void onTextEntered( char c );

    virtual float getFitWidth( void ) = 0;

    virtual float getFitHeight( void ) = 0;

    bool containsPoint( int x, int y );

    std::string m_name;

    float m_actualX = 0;
    float m_actualY = 0;
    float m_actualWidth = 0;
    float m_actualHeight = 0;

    float m_contentX = 0;
    float m_contentY = 0;
    float m_contentWidth = 0;
    float m_contentHeight = 0;

    bool m_validSizeAndPosition = true;

    void setMode( Mode mode );

    Mode getMode( void );

    struct SizeRequest
    {
        SizeType sizeType = SizeType::Absolute;
        float value = 0.0f;
    };

    struct ModeState
    {
        SizeRequest requestedWidth;
        SizeRequest requestedHeight;

        float leftPadding = 0;
        float rightPadding = 0;
        float topPadding = 0;
        float botPadding = 0;

        float leftMargin = 0;
        float rightMargin = 0;
        float topMargin = 0;
        float botMargin = 0;

        sf::RectangleShape shape;
        sf::RectangleShape borderShape;
    };

    ModeState &getModeState( void );

    ModeState &getModeState( Mode mode );

private:

    std::unordered_map<Mode, std::shared_ptr<ModeState>> m_modeState;

    Mode m_mode = Mode::Inactive;
};