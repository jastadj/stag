#include "checkbox.hpp"
#include "engine.hpp"

CheckBox::CheckBox()
{
    m_Name = "Checkbox";
    m_Checked = false;

    createSprite();
}

CheckBox::~CheckBox()
{

}

void CheckBox::createSprite()
{
    sf::Texture ttxt;
    if(!m_Checked) ttxt.loadFromFile(".\\data\\art\\checkbox.png");
    else ttxt.loadFromFile(".\\data\\art\\checkboxchecked.png");
    sf::Sprite tspr(ttxt);

    m_RenderTexture.create(ttxt.getSize().x, ttxt.getSize().y);
    m_RenderTexture.clear(sf::Color::Transparent);
    m_RenderTexture.draw(tspr);
    m_RenderTexture.display();

    m_Sprite = sf::Sprite(m_RenderTexture.getTexture());

}

void CheckBox::setChecked(bool nchecked)
{
    m_Checked = nchecked;
    createSprite();
}

void CheckBox::toggleChecked()
{
    m_Checked = !m_Checked;
    createSprite();
}

bool CheckBox::processEvents(sf::RenderWindow *tscreen, sf::Event &event)
{
    Engine *eptr = Engine::getInstance();

    if(event.type == sf::Event::MouseButtonPressed)
    {

    }

    return false;
}

void CheckBox::EventSelected()
{
    toggleChecked();
}
