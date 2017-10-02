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
    if(m_InConnection || !m_OutConnections.empty()) pintxt.loadFromFile(".\\data\\art\\pinconnected.png");
    else pintxt.loadFromFile(".\\data\\art\\pin.png");

    sf::Sprite pinspr(pintxt);

    m_RenderTexture.create( pintxt.getSize().x, pintxt.getSize().y);
    m_RenderTexture.clear(sf::Color::Transparent);
    m_RenderTexture.draw(pinspr);
    m_RenderTexture.display();

    m_Sprite = sf::Sprite(m_RenderTexture.getTexture());

    m_Sprite.setColor(m_PinColor);
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

bool Pin::hasOutputConnection()
{
    if(m_OutConnections.empty()) return false;

    return true;
}

bool Pin::isConnected()
{
    if(hasOutputConnection()) return true;
    if(hasInputConnection()) return true;
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

    // if pins share the same parents
    if(m_Parent)
        if(m_Parent == tpin->m_Parent) return false;

    // if we are an input pin and target pin is an output pin
    if(m_IO == PIN_INPUT)
    {
        // if connected, disconnect
        if(m_InConnection) m_InConnection->disconnect(this);

        createSprite();
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
            if(getDataType() == PIN_EXECUTE)
            {
                m_OutConnections[i]->m_InConnection = NULL;
            }
            else if( m_OutConnections[i] == tpin)
            {
                std::cout << "OUTPUT PIN ALREADY HAS INPUT PIN IN LIST!\n";
                exit(2);
            }
        }

        if(getDataType() == PIN_EXECUTE) m_OutConnections.clear();

        // set target input pins connection to this
        tpin->m_InConnection = this;
        m_OutConnections.push_back(tpin);
        createSprite();
        tpin->createSprite();
        return true;
    }


    return false;
}

bool Pin::disconnect(Pin *tpin)
{
    if(!tpin && !isConnected()) return false;

    if(m_IO == PIN_INPUT)
    {
        if(tpin == NULL) return m_InConnection->disconnect(this);

        createSprite();
        return tpin->disconnect(this);
    }
    else if(m_IO == PIN_OUTPUT)
    {
        // make sure target pin is in output list
        for(int i = 0; i < int(m_OutConnections.size()); i++)
        {
            // if null pin, disconnect all
            if(tpin == NULL)
            {
                // disonnect input pin and update sprite
                m_OutConnections[i]->m_InConnection = NULL;
                m_OutConnections[i]->createSprite();
            }
            // connection found
            else if(m_OutConnections[i] == tpin)
            {
                // disonnect input pin and update sprite
                m_OutConnections[i]->m_InConnection = NULL;
                m_OutConnections[i]->createSprite();

                // remove pin from out pins
                m_OutConnections.erase( m_OutConnections.begin() + i);

                createSprite();
                return true;
            }

        }

        if(tpin == NULL)
        {
            m_OutConnections.clear();
            createSprite();
            return true;
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
    if(m_InConnection || !m_OutConnections.empty() ) pintxt.loadFromFile(".\\data\\art\\pinexecuteconnected.png");
    else pintxt.loadFromFile(".\\data\\art\\pinexecute.png");

    sf::Sprite pinspr(pintxt);

    m_RenderTexture.create( pintxt.getSize().x, pintxt.getSize().y);
    m_RenderTexture.clear(sf::Color::Transparent);
    m_RenderTexture.draw(pinspr);
    m_RenderTexture.display();

    m_Sprite = sf::Sprite(m_RenderTexture.getTexture());
}

PinExecute *PinExecute::getNextExecutionPin()
{
    if(!m_OutConnections.empty())
    {
        PinExecute *pe = dynamic_cast<PinExecute*>(m_OutConnections[0]);

        if(pe) return pe;
    }

    return NULL;
}

void PinExecute::show()
{
    Pin::show();
    std::cout << "PIN EXECUTABLE\n";
    std::cout << "--------------\n";
}

////////////////////////////////////////////////////////////
// PIN DATA
PinData::PinData(STAGObj *nparent, PIN_IO pio) : Pin(nparent, pio)
{

}

PinData::~PinData()
{

}

GUIObj *PinData::getObjectAtGlobal(sf::Vector2f tpos)
{
    GUIObj *tobj = NULL;

    // check input box
    if(m_InputBox.containsGlobal(tpos)) return &m_InputBox;
    // if input box does not contain pos, check pin
    else if(Pin::containsGlobal(tpos)) return this;

    return tobj;
}

void PinData::draw(sf::RenderWindow *tscreen)
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

void PinData::update()
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

void PinData::show()
{
    Pin::show();
    std::cout << "PIN DATA\n";
    std::cout << "--------\n";
    std::cout << "Input Box Contains:" << m_InputBox.getString() << std::endl;
}

////////////////////////////////////////////////////////////
// PIN INT
PinInt::PinInt(STAGObj *nparent, PIN_IO pio) : PinData(nparent, pio)
{
    m_PinColor = sf::Color::Green;
    m_Sprite.setColor(m_PinColor);

    m_Value = 0;

    m_InputBox.setString("0");

}

PinInt::~PinInt()
{

}

/*
GUIObj *PinInt::getObjectAtGlobal(sf::Vector2f tpos)
{
    GUIObj *tobj = NULL;

    // check input box
    if(m_InputBox.containsGlobal(tpos)) return &m_InputBox;
    // if input box does not contain pos, check pin
    else if(Pin::containsGlobal(tpos)) return this;

    return tobj;
}
*/

/*
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
*/

int PinInt::getValue()
{
    if(m_IO == PIN_INPUT)
    {
        // if pin is connected, get value from output in
        if(m_InConnection)
        {
            PinInt *tp = dynamic_cast<PinInt*>(m_InConnection);
            if(tp) return tp->getValue();
            else
            {
                std::cout << "ERROR getting value from PinInt connection, failed to cast\n";
                exit(3);
            }
        }
        // else get vlaue from input box
        return atoi(m_InputBox.getString().c_str());
    }
    else if(m_IO == PIN_OUTPUT)
    {
        return m_Value;
    }

    return 0;
}

void PinInt::setValue(int tval)
{
    if(m_IO == PIN_OUTPUT) m_Value = tval;
}

/*
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
*/

void PinInt::show()
{
    Pin::show();
    std::cout << "PININT\n";
    std::cout << "------\n";
    std::cout << "Value:" << getValue() << std::endl;
}

////////////////////////////////////////////////////////////
// PIN STRING

PinStr::PinStr(STAGObj *nparent, PIN_IO pio) : PinData(nparent, pio)
{
    m_PinColor = sf::Color(255,100,240);
    m_Sprite.setColor(m_PinColor);

    m_String = "test";

    m_InputBox.setString(m_String);
}

PinStr::~PinStr()
{

}

std::string PinStr::getString()
{
    if(m_IO == PIN_INPUT)
    {
        // if pin is connected, get value from output in
        if(m_InConnection)
        {
            PinStr *tp = dynamic_cast<PinStr*>(m_InConnection);
            if(tp) return tp->getString();
            else
            {
                std::cout << "ERROR getting value from PinStr connection, failed to cast\n";
                exit(3);
            }
        }
        //std::cout << "pinstr not connected, returning input box value\n";
        // else get vlaue from input box
        return m_InputBox.getString();
    }
    else if(m_IO == PIN_OUTPUT)
    {
        return m_String;
    }

    return 0;
}

void PinStr::setString(std::string tstring)
{
    if(m_IO == PIN_OUTPUT) m_String = tstring;
}

void PinStr::show()
{
    PinData::show();
    std::cout << "PIN STRING\n";
    std::cout << "----------\n";
    std::cout << "String:" << getString() << std::endl;
}

////////////////////////////////////////////////////////////
// PIN BOOL

PinBool::PinBool(STAGObj *nparent, PIN_IO pio) : PinData(nparent, pio)
{
    m_PinColor = sf::Color(255,0,0);
    m_Sprite.setColor(m_PinColor);

    m_Bool = false;
    m_Checkbox.setChecked(m_Bool);
}

PinBool::~PinBool()
{

}

bool PinBool::getBool()
{
    if(m_IO == PIN_INPUT)
    {
        // if pin is connected, get value from output in
        if(m_InConnection)
        {
            PinBool *tp = dynamic_cast<PinBool*>(m_InConnection);
            if(tp) return tp->getBool();
            else
            {
                std::cout << "ERROR getting value from PinBool connection, failed to cast\n";
                exit(3);
            }
        }
        //std::cout << "pinstr not connected, returning input box value\n";
        // else get vlaue from input box
        return m_Checkbox.isChecked();
    }
    else if(m_IO == PIN_OUTPUT)
    {
        return m_Bool;
    }

    return 0;
}

void PinBool::setBool(bool tbool)
{
    if(m_IO == PIN_OUTPUT) m_Bool = tbool;
}

void PinBool::show()
{
    PinData::show();
    std::cout << "PIN BOOL\n";
    std::cout << "----------\n";
    std::cout << "BOOL:";
    if(m_Bool) std::cout << "TRUE\n";
    else std::cout << "FALSE\n";
}
