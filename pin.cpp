#include "pin.hpp"

Pin::Pin(STAGObj *nparent, PIN_IO pio)
{
    m_Name = "Pin";
    m_Parent = nparent;
    m_Connection = NULL;
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

GUIObj *Pin::getObjectAtGlobal(sf::Vector2f tpos)
{
    GUIObj *tobj = NULL;

    if(containsGlobal(tpos)) return this;

    return tobj;
}

////////////////////////////////////////////////////////////
// PIN EXECUTION

PinExecute::PinExecute(STAGObj *nparent, PIN_IO pio) : Pin(nparent, pio)
{
    m_Name = "Execution Pin";

    createSprite();
}

PinExecute::~PinExecute()
{

}

void PinExecute::createSprite()
{
    sf::Texture pintxt;
    pintxt.loadFromFile(".\\data\\art\\pinexecute.png");

    sf::Sprite pinspr(pintxt);

    m_RenderTexture.create( pintxt.getSize().x, pintxt.getSize().y);
    m_RenderTexture.clear(sf::Color::Transparent);
    m_RenderTexture.draw(pinspr);
    m_RenderTexture.display();

    m_Sprite = sf::Sprite(m_RenderTexture.getTexture());
}

////////////////////////////////////////////////////////////
// PIN INT
PinInt::PinInt(STAGObj *nparent, PIN_IO pio) : Pin(nparent, pio)
{
    m_PinColor = sf::Color::Green;

    m_Sprite.setColor(m_PinColor);

    m_Value = 0;

    m_InputBox.setString("0");

}

PinInt::~PinInt()
{

}

PIN_DATA_TYPE PinInt::getDataType()
{
    return PIN_INT;
}

GUIObj *PinInt::getObjectAtGlobal(sf::Vector2f tpos)
{
    GUIObj *tobj = NULL;

    // check input box
    if(m_InputBox.containsGlobal(tpos)) return &m_InputBox;
    // if input box does not contain pos, check pin
    else if(Pin::containsGlobal(tpos)) return this;

    return tobj;
}

void PinInt::draw(sf::RenderWindow *tscreen)
{
    GUIObj::draw(tscreen);

    if(m_IO == PIN_INPUT)
    {
        if(!m_Connection)
        {
            m_InputBox.draw(tscreen);
        }
    }
}

void PinInt::update()
{
    GUIObj::update();

    switch(m_IO)
    {
    case PIN_INPUT:
        m_InputBox.setPosition( m_Position + sf::Vector2f(20,0));
        m_InputBox.update();
        break;
    default:
        break;
    }
}
