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
    // target pin is valid
    if(!tpin) return false;

    // if data types do not match
    if(getDataType() != tpin->getDataType()) return false;

    // if IO is not mated
    if(m_IO == tpin->m_IO) return false;

    // if we are an input pin and target pin is an output pin
    if(m_IO == PIN_INPUT)
    {
        // if connected, disconnect
        if(m_InConnection) m_InConnection->disconnect(this);

        return tpin->connect(this);

    }
    // if we are an output pin connecting to an input pin
    else if(m_IO == PIN_OUTPUT)
    {
        // if tpin is already connected...
        if(tpin->m_InConnection == this) return true;

        // error check to see if target input pin is already in out output list
        for(int i = 0; i < int(m_OutConnections.size()); i++)
        {
            if( m_OutConnections[i] == tpin)
            {
                std::cout << "OUTPUT PIN ALREADY HAS INPUT PIN IN LIST!\n";
                exit(2);
            }
        }

        // set target input pins connection to this
        tpin->m_InConnection = this;
        m_OutConnections.push_back(tpin);
        return true;
    }


    return false;
}

bool Pin::disconnect(Pin *tpin)
{
    if(!tpin) return false;

    if(m_IO == PIN_INPUT)
    {
        return tpin->disconnect(this);
    }
    else if(m_IO == PIN_OUTPUT)
    {
        // make sure target pin is in output list
        for(int i = 0; i < int(m_OutConnections.size()); i++)
        {
            // connection found
            if(m_OutConnections[i] == tpin)
            {
                // disonnect input pin
                m_OutConnections[i]->m_InConnection = NULL;

                // remove pin from out pins
                m_OutConnections.erase( m_OutConnections.begin() + i);

                return true;
            }
        }
    }

    return false;
}

void Pin::draw(sf::RenderWindow *tscreen)
{
    GUIObj::draw(tscreen);

    if(m_IO == PIN_OUTPUT)
    {
        for(int i = 0; i < int(m_OutConnections.size()); i++)
        {
            sf::VertexArray line(sf::Lines,2);
            line[0].position = getCenterPosition();
            line[1].position = m_OutConnections[i]->getCenterPosition();
            tscreen->draw(line);
        }
    }
}

void Pin::show()
{
    GUIObj::show();
    std::cout << "PIN OBJECT\n";
    std::cout << "----------\n";
    std::cout << "PIN IO:";
    if(m_IO == PIN_INPUT) std::cout << "INPUT\n";
    else if(m_IO == PIN_OUTPUT) std::cout << "OUTPUT\n";
    else std::cout << "ERROR\n";
    std::cout << "Parent:";
    if(!m_Parent) std::cout << "NULL\n";
    else std::cout << m_Parent->getName() << std::endl;
    std::cout << "COLOR:" << m_PinColor.r << "," << m_PinColor.g << "," << m_PinColor.b << "," << m_PinColor.a << std::endl;
    std::cout << "Input Connection:";
    if(!m_InConnection) std::cout << "NULL\n";
    else std::cout << m_InConnection->getName() << std::endl;
    std::cout << "Output Connections:" << m_OutConnections.size() << std::endl;
    for(int i = 0; i < int(m_OutConnections.size()); i++) std::cout << "  " << m_OutConnections[i]->getName() << std::endl;



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
    Pin::draw(tscreen);

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
