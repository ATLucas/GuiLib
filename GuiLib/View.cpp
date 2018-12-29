
#include "View.h"
#include <iostream>


using namespace std;


void View::addChild( std::shared_ptr<Component> childView )
{
    m_children.push_back( childView );
}

void View::updateSizeAndPostion( void )
{
    Component::updateSizeAndPostion();

    updateChildWidths();
    updateChildHeights();
    updateChildXValues();
    updateChildYValues();

    for ( const auto &child : m_children )
    {
        // Validate the child's size and position.
        ModeState &childModeState = child->getModeState();

        float minX = m_contentX;
        float maxX = m_contentX + m_contentWidth;
        float minY = m_contentY;
        float maxY = m_contentY + m_contentHeight;

        float childMinX = child->m_actualX - childModeState.leftMargin;
        float childMaxX = child->m_actualX + child->m_actualWidth + childModeState.rightMargin;
        float childMinY = child->m_actualY - childModeState.topMargin;
        float childMaxY = child->m_actualY + child->m_actualHeight + childModeState.botMargin;

        if ( childMinX < minX || childMinX > maxX ||
             childMaxX < minX || childMaxX > maxX ||
             childMinY < minY || childMinY > maxY ||
             childMaxY < minY || childMaxY > maxY )
        {
            child->m_validSizeAndPosition = false;
            cerr << "Warning: " << child->m_name << " has invalid size or position." << endl;
        }

        child->updateSizeAndPostion();
    }
}

void View::updateChildWidths( void )
{
    for ( const auto &child : m_children )
    {
        ModeState &childModeState = child->getModeState();

        float childHorizontalMargin = childModeState.leftMargin + childModeState.rightMargin;

        if ( childModeState.requestedWidth.sizeType == SizeType::Absolute )
        {
            child->m_actualWidth = childModeState.requestedWidth.value;
        }
        else if ( childModeState.requestedWidth.sizeType == SizeType::Percent )
        {
            child->m_actualWidth = childModeState.requestedWidth.value * 0.01f * m_contentWidth;
            child->m_actualWidth -= childHorizontalMargin;
        }
        else if ( childModeState.requestedWidth.sizeType == SizeType::Fill )
        {
            child->m_actualWidth = m_contentWidth - childHorizontalMargin;
        }
        else if ( childModeState.requestedWidth.sizeType == SizeType::Fit )
        {
            child->m_actualWidth = child->getFitWidth();
        }
    }
}

void View::updateChildHeights( void )
{
    for ( const auto &child : m_children )
    {
        ModeState &childModeState = child->getModeState();

        float childVerticalMargin = childModeState.topMargin + childModeState.botMargin;

        if ( childModeState.requestedHeight.sizeType == SizeType::Absolute )
        {
            child->m_actualHeight = childModeState.requestedHeight.value;
        }
        else if ( childModeState.requestedHeight.sizeType == SizeType::Percent )
        {
            child->m_actualHeight = childModeState.requestedHeight.value * 0.01f * m_contentHeight;
            child->m_actualHeight -= childVerticalMargin;
        }
        else if ( childModeState.requestedHeight.sizeType == SizeType::Fill )
        {
            child->m_actualHeight = m_contentHeight - childVerticalMargin;
        }
        else if ( childModeState.requestedHeight.sizeType == SizeType::Fit )
        {
            child->m_actualHeight = child->getFitHeight();
        }
    }
}

void View::updateChildXValues( void )
{
    for ( const auto &child : m_children )
        child->m_actualX = m_contentX + child->getModeState().leftMargin;
}

void View::updateChildYValues( void )
{
    for ( const auto &child : m_children )
        child->m_actualY = m_contentY + child->getModeState().topMargin;
}

void View::draw( sf::RenderWindow &window )
{
    Component::draw( window );

    for ( const auto &child : m_children )
    {
        // Only draw the component if it fits in the view.
        if ( child->m_validSizeAndPosition )
            child->draw( window );
    }
}

void View::onMousePressed( int x, int y )
{
    for ( const auto &child : m_children )
        child->onMousePressed( x, y );
}

void View::onMouseReleased( int x, int y )
{
    for ( const auto &child : m_children )
        child->onMouseReleased( x, y );
}

void View::onMouseMoved( int x, int y )
{
    for ( const auto &child : m_children )
        child->onMouseMoved( x, y );
}

void View::onTextEntered( char c )
{
    for ( const auto &child : m_children )
        child->onTextEntered( c );
}

float View::getFitWidth( void )
{
    float fitWidth = 0;

    for ( const auto &child : m_children )
    {
        ModeState &childModeState = child->getModeState();

        float childMargin = childModeState.leftMargin + childModeState.rightMargin;
        float childFitWidth = 0;

        if ( childModeState.requestedWidth.sizeType == SizeType::Absolute )
        {
            childFitWidth = childMargin + childModeState.requestedWidth.value;
        }
        else if ( childModeState.requestedWidth.sizeType == SizeType::Fit )
        {
            childFitWidth = childMargin + child->getFitWidth();
        }

        fitWidth = childFitWidth > fitWidth ? childFitWidth : fitWidth;
    }

    fitWidth += getModeState().leftPadding + getModeState().rightPadding;
    
    return fitWidth;
}

float View::getFitHeight( void )
{
    float fitHeight = 0;

    for ( const auto &child : m_children )
    {
        ModeState &childModeState = child->getModeState();

        float childMargin = childModeState.topMargin + childModeState.botMargin;
        float childFitHeight = 0;

        if ( childModeState.requestedHeight.sizeType == SizeType::Absolute )
        {
            childFitHeight = childMargin + childModeState.requestedHeight.value;
        }
        else if ( childModeState.requestedHeight.sizeType == SizeType::Fit )
        {
            childFitHeight = childMargin + child->getFitHeight();
        }

        fitHeight = childFitHeight > fitHeight ? childFitHeight : fitHeight;
    }

    fitHeight += getModeState().topPadding + getModeState().botPadding;

    return fitHeight;
}

float HorizontalView::getFitWidth( void )
{
    float fitWidth = getModeState().leftPadding + getModeState().rightPadding;

    for ( const auto &child : m_children )
    {
        ModeState &childModeState = child->getModeState();

        float childMargin = childModeState.leftMargin + childModeState.rightMargin;

        if ( childModeState.requestedWidth.sizeType == SizeType::Absolute )
        {
            fitWidth += childMargin + childModeState.requestedWidth.value;
        }
        else if ( childModeState.requestedWidth.sizeType == SizeType::Fit )
        {
            fitWidth += childMargin + child->getFitWidth();
        }
    }

    return fitWidth;
}

void HorizontalView::updateChildWidths( void )
{
    float remainingWidth = m_contentWidth;
    int numFillingChildren = 0;

    for ( const auto &child : m_children )
    {
        ModeState &childModeState = child->getModeState();

        float childHorizontalMargin = childModeState.leftMargin + childModeState.rightMargin;

        child->m_actualWidth = 0;

        if ( childModeState.requestedWidth.sizeType == SizeType::Absolute )
        {
            child->m_actualWidth = childModeState.requestedWidth.value;
        }
        else if ( childModeState.requestedWidth.sizeType == SizeType::Percent )
        {
            child->m_actualWidth = childModeState.requestedWidth.value * 0.01f * m_contentWidth;
            child->m_actualWidth -= childHorizontalMargin;
        }
        else if ( childModeState.requestedWidth.sizeType == SizeType::Fill )
        {
            numFillingChildren++;
        }
        else if ( childModeState.requestedWidth.sizeType == SizeType::Fit )
        {
            child->m_actualWidth = child->getFitWidth();
        }

        remainingWidth -= child->m_actualWidth + childHorizontalMargin;
        remainingWidth = remainingWidth > 0 ? remainingWidth : 0;
    }

    if ( numFillingChildren > 0 )
    {
        float fillValue = remainingWidth / numFillingChildren;

        for ( const auto &child : m_children )
        {
            if ( child->getModeState().requestedWidth.sizeType == SizeType::Fill )
                child->m_actualWidth = fillValue;
        }
    }
}

void HorizontalView::updateChildXValues( void )
{
    float nextX = m_contentX;

    for ( const auto &child : m_children )
    {
        ModeState &childModeState = child->getModeState();

        nextX += childModeState.leftMargin;
        child->m_actualX = nextX;
        nextX += child->m_actualWidth;
        nextX += childModeState.rightMargin;
    }
}

float VerticalView::getFitHeight( void )
{
    ModeState &modeState = getModeState();
    float fitHeight = modeState.topPadding + modeState.botPadding;

    for ( const auto &child : m_children )
    {
        ModeState &childModeState = child->getModeState();

        float childMargin = childModeState.topMargin + childModeState.botMargin;

        if ( childModeState.requestedHeight.sizeType == SizeType::Absolute )
        {
            fitHeight += childMargin + childModeState.requestedHeight.value;
        }
        else if ( childModeState.requestedHeight.sizeType == SizeType::Fit )
        {
            fitHeight += childMargin + child->getFitHeight();
        }
    }

    return fitHeight;
}

void VerticalView::updateChildHeights( void )
{
    float remainingHeight = m_contentHeight;
    int numFillingChildren = 0;

    for ( const auto &child : m_children )
    {
        ModeState &childModeState = child->getModeState();

        float childVerticalMargin = childModeState.topMargin + childModeState.botMargin;

        child->m_actualHeight = 0;

        if ( childModeState.requestedHeight.sizeType == SizeType::Absolute )
        {
            child->m_actualHeight = childModeState.requestedHeight.value;
        }
        else if ( childModeState.requestedHeight.sizeType == SizeType::Percent )
        {
            child->m_actualHeight = childModeState.requestedHeight.value * 0.01f * m_contentHeight;
            child->m_actualHeight -= childVerticalMargin;
        }
        else if ( childModeState.requestedHeight.sizeType == SizeType::Fill )
        {
            numFillingChildren++;
        }
        else if ( childModeState.requestedHeight.sizeType == SizeType::Fit )
        {
            child->m_actualHeight = child->getFitHeight();
        }

        remainingHeight -= child->m_actualHeight + childVerticalMargin;
        remainingHeight = remainingHeight > 0 ? remainingHeight : 0;
    }

    if ( numFillingChildren > 0 )
    {
        float fillValue = remainingHeight / numFillingChildren;

        for ( const auto &child : m_children )
        {
            if ( child->getModeState().requestedHeight.sizeType == SizeType::Fill )
                child->m_actualHeight = fillValue;
        }
    }
}

void VerticalView::updateChildYValues( void )
{
    float nextY = m_actualY;

    for ( const auto &child : m_children )
    {
        ModeState &childModeState = child->getModeState();

        nextY += childModeState.topMargin;
        child->m_actualY = nextY;
        nextY += child->m_actualHeight;
        nextY += childModeState.botMargin;
    }
}