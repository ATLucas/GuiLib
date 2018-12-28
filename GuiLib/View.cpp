
#include "View.h"
#include <iostream>


using namespace std;


void View::addChild( std::shared_ptr<Component> childView )
{
    m_children.push_back( childView );
}

void View::update( void )
{
    Component::update();

    updateChildren();
}

void View::draw( sf::RenderWindow &window )
{
    Component::draw( window );

    for ( const auto &child : m_children )
        child->draw( window );
}

void LayeredView::updateChildren( void )
{
    // Update widths
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

    // Update heights
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

    // Update x values
    for ( const auto &child : m_children )
        child->m_actualX = m_contentX;

    // Update y values
    for ( const auto &child : m_children )
        child->m_actualY = m_contentY;

    // Recurse
    for ( const auto &child : m_children )
        child->update();
}

void HorizontalView::updateChildren( void )
{
    // Update widths
    float remainingWidth = m_contentWidth;
    int numChildrenOfTypeFill = 0;

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
            numChildrenOfTypeFill++;
        }

        remainingWidth -= child->m_actualWidth + childHorizontalMargin;
        remainingWidth = remainingWidth > 0 ? remainingWidth : 0;
    }

    if ( numChildrenOfTypeFill > 0 )
    {
        float fillValue = remainingWidth / numChildrenOfTypeFill;

        for ( const auto &child : m_children )
        {
            if ( child->m_requestedWidth.sizeType == SizeType::Fill )
                child->m_actualWidth = fillValue;
        }
    }

    // Update heights
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

    // Update x values
    float nextX = m_contentX;

    for ( const auto &child : m_children )
    {
        nextX += child->m_leftMargin;
        child->m_actualX = nextX;
        nextX += child->m_actualWidth;
        nextX += child->m_rightMargin;
    }

    // Update y values
    for ( const auto &child : m_children )
        child->m_actualY = m_contentY + child->m_topMargin;

    // Recurse
    for ( const auto &child : m_children )
        child->update();
}

void VerticalView::updateChildren( void )
{
    // Update widths
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

    // Update heights
    float remainingHeight = m_contentHeight;
    int numChildrenOfTypeFill = 0;

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
            numChildrenOfTypeFill++;
        }

        remainingHeight -= child->m_actualHeight + childVerticalMargin;
        remainingHeight = remainingHeight > 0 ? remainingHeight : 0;
    }

    if ( numChildrenOfTypeFill > 0 )
    {
        float fillValue = remainingHeight / numChildrenOfTypeFill;

        for ( const auto &child : m_children )
        {
            if ( child->m_requestedHeight.sizeType == SizeType::Fill )
                child->m_actualHeight = fillValue;
        }
    }

    // Update x values
    for ( const auto &child : m_children )
        child->m_actualX = m_contentX + child->m_leftMargin;

    // Update y values
    float nextY = m_actualY;

    for ( const auto &child : m_children )
    {
        nextY += child->m_topMargin;
        child->m_actualY = nextY;
        nextY += child->m_actualHeight;
        nextY += child->m_botMargin;
    }

    // Recurse
    for ( const auto &child : m_children )
        child->update();
}