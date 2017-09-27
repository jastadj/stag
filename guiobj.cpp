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

sf::Vector2f GUIObj::getCenterPosition()
{
    return m_Position + sf::Vector2f(m_Sprite.getLocalBounds().width/2, m_Sprite.getLocalBounds().height/2);
}

sf::FloatRect GUIObj::getSpriteDimensions()
{
    return m_Sprite.getLocalBounds();
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

void GUIObj::show()
{
    std::cout << "GUI OBJ\n";
    std::cout << "-------\n";
    std::cout << "Name:" << getName() << std::endl;
    std::cout << "Visible:" << isVisible() << std::endl;
    std::cout << "Position:" << getPosition().x << "," << getPosition().y << std::endl;
    std::cout << "Center Pos:" << getCenterPosition().x << "," << getCenterPosition().y << std::endl;
}
