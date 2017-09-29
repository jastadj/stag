#include "nodedata.hpp"
#include <sstream>

//////////////////////////////////////////////////////////////////
//
NodeAddInt::NodeAddInt()
{
    m_Name = "AddInts";

    // create input integer pins
    Pin *ipin = new PinInt(this, PIN_INPUT);
    m_PinInputs.push_back(ipin);

    ipin = new PinInt(this, PIN_INPUT);
    m_PinInputs.push_back(ipin);

    // create output pin that adds both pin inputs
    Pin *opin = new PinInt(this, PIN_OUTPUT);
    m_PinOutputs.push_back(opin);

    createSprite();
}

NodeAddInt::~NodeAddInt()
{

}

void NodeAddInt::createSprite()
{
    int w = 200;
    int h = 75;

    int crossw = 32;
    int crossh = 8;

    // create "+" bar
    sf::RectangleShape rcross(sf::Vector2f(crossw,crossh));
    rcross.setFillColor(sf::Color(100,100,100) );
    rcross.setOrigin(sf::Vector2f(crossw/2, crossh/2));

    // create render texture
    m_RenderTexture.create(w,h);
    m_RenderTexture.clear(sf::Color(100,100,100,100));

    // set cross to center of node window
    rcross.setPosition(sf::Vector2f(w/2, h/2));
    m_RenderTexture.draw(rcross);
    rcross.rotate(90);
    m_RenderTexture.draw(rcross);

    m_RenderTexture.display();

    m_Sprite = sf::Sprite(m_RenderTexture.getTexture());
}

void NodeAddInt::update()
{
    Node::update();

    PinInt *ip0, *ip1, *op0;

    ip0 = dynamic_cast<PinInt*>(m_PinInputs[0]);
    ip1 = dynamic_cast<PinInt*>(m_PinInputs[1]);
    op0 = dynamic_cast<PinInt*>(m_PinOutputs[0]);

    if(!ip0 || !ip1 || !op0) {std::cout << "Error updating pinint, unable to cast!\n"; exit(4);}

    op0->setValue(ip0->getValue() + ip1->getValue());
}


//////////////////////////////////////////////////////////////////
//  NODE SUBTRACT INTEGER

NodeSubtractInt::NodeSubtractInt()
{
    m_Name = "SubtractInts";

    // create input integer pins
    Pin *ipin = new PinInt(this, PIN_INPUT);
    m_PinInputs.push_back(ipin);

    ipin = new PinInt(this, PIN_INPUT);
    m_PinInputs.push_back(ipin);

    // create output pin that adds both pin inputs
    Pin *opin = new PinInt(this, PIN_OUTPUT);
    m_PinOutputs.push_back(opin);

    createSprite();
}

NodeSubtractInt::~NodeSubtractInt()
{

}

void NodeSubtractInt::createSprite()
{
    int w = 200;
    int h = 75;

    int crossw = 32;
    int crossh = 8;

    // create "-" bar
    sf::RectangleShape rcross(sf::Vector2f(crossw,crossh));
    rcross.setFillColor(sf::Color(100,100,100) );
    rcross.setOrigin(sf::Vector2f(crossw/2, crossh/2));

    // create render texture
    m_RenderTexture.create(w,h);
    m_RenderTexture.clear(sf::Color(100,100,100,100));

    // set cross to center of node window
    rcross.setPosition(sf::Vector2f(w/2, h/2));
    m_RenderTexture.draw(rcross);

    m_RenderTexture.display();

    m_Sprite = sf::Sprite(m_RenderTexture.getTexture());
}

void NodeSubtractInt::update()
{
    Node::update();

    PinInt *ip0, *ip1, *op0;

    ip0 = dynamic_cast<PinInt*>(m_PinInputs[0]);
    ip1 = dynamic_cast<PinInt*>(m_PinInputs[1]);
    op0 = dynamic_cast<PinInt*>(m_PinOutputs[0]);

    if(!ip0 || !ip1 || !op0) {std::cout << "Error updating pinint, unable to cast!\n"; exit(4);}

    op0->setValue(ip0->getValue() - ip1->getValue());
}

//////////////////////////////////////////////////////////////////
//  NODE INT TO STRING
NodeIntToStr::NodeIntToStr()
{
    m_Name = "Int to String";

    // create input integer pins
    Pin *ipin = new PinInt(this, PIN_INPUT);
    m_PinInputs.push_back(ipin);

    // create output string pin
    Pin *opin = new PinStr(this, PIN_OUTPUT);
    m_PinOutputs.push_back(opin);

    createSprite();
}

NodeIntToStr::~NodeIntToStr()
{

}

void NodeIntToStr::createSprite()
{
    int w = 200;
    int h = 75;

    // create render texture
    m_RenderTexture.create(w,h);
    m_RenderTexture.clear(sf::Color(100,100,100,100));

    m_RenderTexture.display();

    m_Sprite = sf::Sprite(m_RenderTexture.getTexture());
}

void NodeIntToStr::update()
{
    Node::update();

    PinInt *ip0;
    PinStr *op0;

    ip0 = dynamic_cast<PinInt*>(m_PinInputs[0]);
    op0 = dynamic_cast<PinStr*>(m_PinOutputs[0]);

    if(!ip0 || !op0) {std::cout << "Error updating node int to string, unable to cast!\n"; exit(4);}

    std::stringstream ss;
    ss << ip0->getValue();
    op0->setString( ss.str());
}
