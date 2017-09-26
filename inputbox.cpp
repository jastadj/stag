#include "inputbox.hpp"
#include "engine.hpp"

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

void InputBox::createTextSprite()
{
    Engine *eptr = Engine::getInstance();

    m_Text = sf::Text(m_String, *(*eptr->getFonts())[0], 12);

    m_Cursor = sf::Text("|", *(*eptr->getFonts())[0], 12);

}

void InputBox::setString(std::string ninput)
{
    m_String = ninput;

    createTextSprite();
}

void InputBox::EventSelected()
{
    m_BlinkTimer.restart();
}

bool InputBox::processEvents(sf::RenderWindow *tscreen, sf::Event &events)
{
    )

    return false;
}

void InputBox::update()
{

    GUIObj::update();

    m_Text.setPosition(m_Position + sf::Vector2f(2,0));
}

void InputBox::draw(sf::RenderWindow *tscreen)
{
    Engine *eptr = Engine::getInstance();

    GUIObj::draw(tscreen);

    tscreen->draw(m_Text);

    // if this input box is selected, blink cursor
    if(eptr->isSelected(this))
    {
        if(m_BlinkTimer.getElapsedTime().asMilliseconds() > INPUTBOX_BLINK*2) m_BlinkTimer.restart();
        else if(m_BlinkTimer.getElapsedTime().asMilliseconds() > INPUTBOX_BLINK)
        {
            m_Cursor.setPosition(m_Text.getPosition() + sf::Vector2f(m_Text.getLocalBounds().width, 0));
            tscreen->draw(m_Cursor);
        }
    }
}
