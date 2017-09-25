#include "pin.hpp"

Pin::Pin(STAGObj *nparent, PIN_IO pio)
{
    m_Parent = nparent;
    m_IO = pio;

    createSprite();
}

Pin::~Pin()
{

}

void Pin::createSprite()
{
    sf::Texture pintxt;
    pintxt.loadFromFile(".\\data\\art\\pin.png");

    sf::Sprite pinspr(pintxt);

    m_RenderTexture.create( pintxt.getSize().x, pintxt.getSize().y);
    m_RenderTexture.clear(sf::Color::Transparent);
    m_RenderTexture.draw(pinspr);
    m_RenderTexture.display();

    m_Sprite = sf::Sprite(m_RenderTexture.getTexture());
}

STAGObj *Pin::getParent()
{
    return m_Parent;
}

////////////////////////////////////////////////////////////
// PIN INT
PinInt::PinInt(STAGObj *nparent, PIN_IO pio) : Pin(nparent, pio)
{
    m_PinColor = sf::Color::Green;

    m_Sprite.setColor(m_PinColor);

}

PinInt::~PinInt()
{

}

PIN_DATA_TYPE PinInt::getDataType()
{
    return PIN_INT;
}
