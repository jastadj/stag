#include "nodefunctions.hpp"

NodeFunction::NodeFunction()
{
    m_ExecuteIn = new PinExecute(this, PIN_INPUT);
    m_ExecuteOut = new PinExecute(this, PIN_OUTPUT);
}

NodeFunction::~NodeFunction()
{

}

GUIObj *NodeFunction::getObjectAtGlobal(sf::Vector2f tpos)
{
    GUIObj *tobj = Node::getObjectAtGlobal(tpos);

    if(!tobj)
    {
        // check execution pins
        if(m_ExecuteIn->containsGlobal(tpos)) return m_ExecuteIn;
        else if(m_ExecuteOut->containsGlobal(tpos)) return m_ExecuteOut;

    }

    return tobj;
}

void NodeFunction::update()
{
    Node::update();

    sf::FloatRect dim = getSpriteDimensions();
    sf::FloatRect edim = m_ExecuteIn->getSpriteDimensions();

    // update execution pins
    m_ExecuteIn->setPosition(m_Position + sf::Vector2f(4,2));
    m_ExecuteOut->setPosition(m_Position + sf::Vector2f(dim.width-edim.width-4,2));

    // update pins
    m_ExecuteIn->update();
    m_ExecuteOut->update();
}

void NodeFunction::draw(sf::RenderWindow *tscreen)
{
    Node::draw(tscreen);

    // draw execution pins
    m_ExecuteIn->draw(tscreen);
    m_ExecuteOut->draw(tscreen);
}

//////////////////////////////////////////////////////////////////
//
NodePrintToConsole::NodePrintToConsole()
{
    m_Name = "Print To Console";
    m_HeaderText = "Print To Console";

    createSprite();
}

NodePrintToConsole::~NodePrintToConsole()
{

}
