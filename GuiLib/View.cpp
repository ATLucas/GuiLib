
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
        float minX = m_contentX;
        float maxX = m_contentX + m_contentWidth;
        float minY = m_contentY;
        float maxY = m_contentY + m_contentHeight;

        float childMinX = child->m_actualX - child->m_leftMargin;
        float childMaxX = child->m_actualX + child->m_actualWidth + child->m_rightMargin;
        float childMinY = child->m_actualY - child->m_topMargin;
        float childMaxY = child->m_actualY + child->m_actualHeight + child->m_botMargin;

        if ( childMinX < minX || childMinX > maxX ||
             childMaxX < minX || childMaxX > maxX ||
             childMinY < minY || childMinY > maxY ||
             childMaxY < minY || childMaxY > maxY )
        {
            child->m_validSizeAndPosition = false;
            cerr << "Warning: Found a component with invalid position or size." << endl;
        }

        child->updateSizeAndPostion();
    }
}

void View::updateChildWidths( void )
{
    for ( const auto &child : m_children )
    {
        float childHorizontalMargin = child->m_leftMargin + child->m_rightMargin;

        if ( child->m_requestedWidth.sizeType == SizeType::Absolute )
        {
            child->m_actualWidth = child->m_requestedWidth.value;
        }
        else if ( child->m_requestedWidth.sizeType == SizeType::Percent )
        {
            child->m_actualWidth = child->m_requestedWidth.value * 0.01f * m_contentWidth;
            child->m_actualWidth -= childHorizontalMargin;
        }
        else if ( child->m_requestedWidth.sizeType == SizeType::Fill )
        {
            child->m_actualWidth = m_contentWidth - childHorizontalMargin;
        }
    }
}

void View::updateChildHeights( void )
{
    for ( const auto &child : m_children )
    {
        float childVerticalMargin = child->m_topMargin + child->m_botMargin;

        if ( child->m_requestedHeight.sizeType == SizeType::Absolute )
        {
            child->m_actualHeight = child->m_requestedHeight.value;
        }
        else if ( child->m_requestedHeight.sizeType == SizeType::Percent )
        {
            child->m_actualHeight = child->m_requestedHeight.value * 0.01f * m_contentHeight;
            child->m_actualHeight -= childVerticalMargin;
        }
        else if ( child->m_requestedHeight.sizeType == SizeType::Fill )
        {
            child->m_actualHeight = m_contentHeight - childVerticalMargin;
        }
    }
}

void View::updateChildXValues( void )
{
    for ( const auto &child : m_children )
        child->m_actualX = m_contentX + child->m_leftMargin;
}

void View::updateChildYValues( void )
{
    for ( const auto &child : m_children )
        child->m_actualY = m_contentY + child->m_topMargin;
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

void HorizontalView::updateChildWidths( void )
{
    float remainingWidth = m_contentWidth;
    int numFillingChildren = 0;

    for ( const auto &child : m_children )
    {
        float childHorizontalMargin = child->m_leftMargin + child->m_rightMargin;

        child->m_actualWidth = 0;

        if ( child->m_requestedWidth.sizeType == SizeType::Absolute )
        {
            child->m_actualWidth = child->m_requestedWidth.value;
        }
        else if ( child->m_requestedWidth.sizeType == SizeType::Percent )
        {
            child->m_actualWidth = child->m_requestedWidth.value * 0.01f * m_contentWidth;
            child->m_actualWidth -= childHorizontalMargin;
        }
        else if ( child->m_requestedWidth.sizeType == SizeType::Fill )
        {
            numFillingChildren++;
        }

        remainingWidth -= child->m_actualWidth + childHorizontalMargin;
        remainingWidth = remainingWidth > 0 ? remainingWidth : 0;
    }

    if ( numFillingChildren > 0 )
    {
        float fillValue = remainingWidth / numFillingChildren;

        for ( const auto &child : m_children )
        {
            if ( child->m_requestedWidth.sizeType == SizeType::Fill )
                child->m_actualWidth = fillValue;
        }
    }
}

void HorizontalView::updateChildXValues( void )
{
    float nextX = m_contentX;

    for ( const auto &child : m_children )
    {
        nextX += child->m_leftMargin;
        child->m_actualX = nextX;
        nextX += child->m_actualWidth;
        nextX += child->m_rightMargin;
    }
}

void VerticalView::updateChildHeights( void )
{
    float remainingHeight = m_contentHeight;
    int numFillingChildren = 0;

    for ( const auto &child : m_children )
    {
        float childVerticalMargin = child->m_topMargin + child->m_botMargin;

        child->m_actualHeight = 0;

        if ( child->m_requestedHeight.sizeType == SizeType::Absolute )
        {
            child->m_actualHeight = child->m_requestedHeight.value;
        }
        else if ( child->m_requestedHeight.sizeType == SizeType::Percent )
        {
            child->m_actualHeight = child->m_requestedHeight.value * 0.01f * m_contentHeight;
            child->m_actualHeight -= childVerticalMargin;
        }
        else if ( child->m_requestedHeight.sizeType == SizeType::Fill )
        {
            numFillingChildren++;
        }

        remainingHeight -= child->m_actualHeight + childVerticalMargin;
        remainingHeight = remainingHeight > 0 ? remainingHeight : 0;
    }

    if ( numFillingChildren > 0 )
    {
        float fillValue = remainingHeight / numFillingChildren;

        for ( const auto &child : m_children )
        {
            if ( child->m_requestedHeight.sizeType == SizeType::Fill )
                child->m_actualHeight = fillValue;
        }
    }
}

void VerticalView::updateChildYValues( void )
{
    float nextY = m_actualY;

    for ( const auto &child : m_children )
    {
        nextY += child->m_topMargin;
        child->m_actualY = nextY;
        nextY += child->m_actualHeight;
        nextY += child->m_botMargin;
    }
}