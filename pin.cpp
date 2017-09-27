#include "pin.hpp"

Pin::Pin(STAGObj *nparent, PIN_IO pio)
{
    m_Name = "Pin";
    m_Parent = nparent;
    m_InConnection = NULL;
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

bool Pin::hasInputConnection()
{
    if(m_IO == PIN_INPUT)
    {
        if(m_InConnection) return true;
    }

    return false;
}

bool Pin::connect(Pin *tpin)
{
    // if target pin is not valid
    if(!tpin) return false;

    // if pins do not match type
    if(getDataType() != tpin->getDataType()) return false;

    // if this pin is an input pin
    if(m_IO == PIN_INPUT)
    {
        // if already has an input connection, disconnect output to this
        if(m_InConnection)
        {
            m_InConnection->disconnect(this);
            m_InConnection = NULL;
        }


        // connect outpit pin to this
        tpin->connect(this);
        // connect input pin
        m_InConnection = tpin;

        return true;
    }
    else if(m_IO == PIN_OUTPUT)
    {
        //if target pin already has connection, reject
        if(tpin->hasInputConnection()) return false;

        //check output pin connections to check if this target pin is already in the list...
        for(int i = 0; i < int(m_OutConnections.size()); i++)
        {

            // double check, exit if found
            if(m_OutConnections[i] == tpin)
            {
                std::cout << "ERROR: Pin output connections already has target pin connected.  This should never happen.\n";
                exit(2);
            }
        }

        m_OutConnections.push_back(tpin);
    }

    return false;
}

bool Pin::disconnect(Pin *tpin)
{
    if(m_IO == PIN_INPUT)
    {
        m_InConnection->disconnect(this);
        m_InConnection = NULL;
        return true;
    }
    else if(m_IO == PIN_OUTPUT)
    {
        // if target pin is provided, disconnect specific pin
        if(tpin)
        {
            //find target pin in output connection list
            for(int i = 0; i < int(m_OutConnections.size()); i++)
            {

                if(m_OutConnections[i] == tpin)
                {
                    tpin->disconnect();
                    m_OutConnections.erase(m_OutConnections.begin() + i);
                    return true;
                }

            }
        }
        // else if no specific pin is specified, disconnect all pins connected to output
        else
        {
            //find target pin in output connection list
            for(int i = 0; i < int(m_OutConnections.size()); i++)
            {
                m_OutConnections[i]->disconnect();

            }
            m_OutConnections.clear();

            return true;
        }


    }

    return false;
}

void Pin::show()
{
    GUIObj::show();
    std::cout << "PIN OBJECT\n";
    std::cout << "----------\n";

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
        if(!m_InConnection)
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
