#include "guiobj.hpp"

GUIObj::GUIObj()
{
    m_Name = "unnamed";
    m_Visible = true;
}

GUIObj::~GUIObj()
{

}

void GUIObj::setPosition(sf::Vector2f tpos)
{
    m_Position = tpos;
}

sf::Vector2f GUIObj::getPosition()
{
    return m_Position;
}



bool GUIObj::containsGlobal(sf::Vector2f gcoord)
{
    return m_Sprite.getGlobalBounds().contains(gcoord);
}

void GUIObj::draw(sf::RenderWindow *tscreen)
{
    if(m_Visible)
    {
        tscreen->draw(m_Sprite);
    }

}

void GUIObj::update()
{
    m_Sprite.setPosition(m_Position);
}
