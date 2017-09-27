#include "nodeevents.hpp"

NodeEvent::NodeEvent()
{
    m_ExecuteOut = new PinExecute(this, PIN_OUTPUT);
}

NodeEvent::~NodeEvent()
{

}

GUIObj *NodeEvent::getObjectAtGlobal(sf::Vector2f tpos)
{

    // check base class
    GUIObj *tobj = Node::getObjectAtGlobal(tpos);

    // check execution pin
    if(!tobj)
    {
        if(m_ExecuteOut->containsGlobal(tpos)) return m_ExecuteOut;
    }


    // return found object at position (may be null)
    return tobj;
}

void NodeEvent::update()
{
    Node::update();

    sf::FloatRect dim = getSpriteDimensions();
    sf::FloatRect edim = m_ExecuteOut->getSpriteDimensions();

    // update execution pins
    m_ExecuteOut->setPosition(m_Position + sf::Vector2f(dim.width-edim.width-4,2));

    // update pins
    m_ExecuteOut->update();
}

void NodeEvent::draw(sf::RenderWindow *tscreen)
{
    Node::draw(tscreen);

    // draw execution pins
    m_ExecuteOut->draw(tscreen);
}

//////////////////////////////////////////////////////////////////
//

NodeEventStart::NodeEventStart()
{
    m_Name = "EventStart";
    m_HeaderText = "Start";

    createSprite();
}

NodeEventStart::~NodeEventStart()
{

}
