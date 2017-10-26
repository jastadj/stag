#include "mouse.hpp"
#include <cmath>

// for debug
#include <iostream>
#include <string>

Mouse::Mouse()
{
    left.m_Parent = this;
    left.m_Type = MOUSE_LEFT;

    right.m_Parent = this;
    right.m_Type = MOUSE_RIGHT;
}

Mouse::~Mouse()
{

}

sf::Vector2f Mouse::getGlobalPos()
{
    return m_GlobalPos;
}

sf::Vector2f Mouse::getLocalPos()
{
    return m_LocalPos;
}

void Mouse::update(sf::RenderWindow *tscreen)
{
    if(!tscreen) return;

    sf::Vector2i rawpos = sf::Mouse::getPosition(*tscreen);

    m_LocalPos = sf::Vector2f( float(rawpos.x), float(rawpos.y));
    m_GlobalPos = tscreen->mapPixelToCoords( rawpos);
}

void Mouse::show()
{
    std::cout << "Mouse\n";
    std::cout << "-----\n";
    std::cout << "local pos  = " << m_LocalPos.x << "," << m_LocalPos.y << std::endl;
    std::cout << "global pos = " << m_GlobalPos.x << "," << m_GlobalPos.y << std::endl;
    left.show();
    right.show();

}

////////////////////////////////////////////////
MouseButton::MouseButton()
{
    // this needs to be set by the parent mouse class
    m_Parent = NULL;

    m_IsPressed = false;
}

MouseButton::~MouseButton()
{

}

void MouseButton::click()
{
    m_LocalClickedPos = m_Parent->getLocalPos();
    m_GlobalClickedPos = m_Parent->getGlobalPos();

    m_IsPressed = true;

    m_ClickedTimer.restart();
}

void MouseButton::release()
{
    m_IsPressed = false;
}

void MouseButton::setOffset(sf::Vector2f toffset)
{
    m_ClickedOffset = toffset;
}

void MouseButton::addTarget(GUIObj *newtarget)
{
    m_Targets.push_back(newtarget);
    newtarget->EventSelected();

}

void MouseButton::clearTargets()
{
    for(int i = 0; i < int(m_Targets.size()); i++) m_Targets[i]->EventDeselected();
    m_Targets.clear();
}

/*
bool MouseButton::isPressed()
{
    if(m_Type == MOUSE_LEFT) return sf::Mouse::isButtonPressed(sf::Mouse::Left);
    else if(m_Type == MOUSE_RIGHT) return sf::Mouse::isButtonPressed( sf::Mouse::Right);
    else return false;
}
*/

sf::Vector2f MouseButton::getLocalClickedPos()
{
    return m_LocalClickedPos;
}

sf::Vector2f MouseButton::getGlobalClickedPos()
{
    return m_GlobalClickedPos;
}

sf::Vector2f MouseButton::getOffset()
{
    return m_ClickedOffset;
}

std::vector<GUIObj*> *MouseButton::getTargets()
{
    return &m_Targets;
}

sf::Time MouseButton::getTimeSinceClicked()
{
    return m_ClickedTimer.getElapsedTime();
}

void MouseButton::show()
{
    std::cout << "Button: ";
    if(m_Type == MOUSE_LEFT) std::cout << "Left\n";
    else if(m_Type == MOUSE_RIGHT) std::cout << "Right\n";
    std::cout << "Pressed:" << isPressed() << std::endl;
    std::cout << "Time (ms) since last clicked : " << getTimeSinceClicked().asMilliseconds() << std::endl;
    std::cout << "local pos  = " << m_LocalClickedPos.x << "," << m_LocalClickedPos.y << std::endl;
    std::cout << "global pos = " << m_GlobalClickedPos.x << "," << m_GlobalClickedPos.y << std::endl;
    std::cout << "Targets : " << m_Targets.size() << " targets\n";
    for(int i = 0; i < int(m_Targets.size()); i++)
    {
        std::cout << "  " << m_Targets[i]->getName() << std::endl;
    }
    std::cout << "Offset : " << m_ClickedOffset.x << "," << m_ClickedOffset.y << std::endl;
}
