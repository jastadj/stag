#include "inputbox.hpp"

InputBox::InputBox()
{
    m_Name = "Input Box";

    m_Width = 32;

    createSprite();
}

InputBox::~InputBox()
{

}

void InputBox::createSprite()
{
    static const int m_Height = 16;

    sf::RectangleShape ibox(sf::Vector2f(m_Width-2, m_Height-2));
    ibox.setOutlineThickness(1.0);
    ibox.setFillColor(sf::Color(100,100,100,100));
    ibox.setOutlineColor(sf::Color::White);
    ibox.setPosition(sf::Vector2f(1,1));

    m_RenderTexture.create(m_Width, m_Height);
    m_RenderTexture.clear(sf::Color::Transparent);
    m_RenderTexture.draw(ibox);
    m_RenderTexture.display();

    m_Sprite = sf::Sprite(m_RenderTexture.getTexture());

}
