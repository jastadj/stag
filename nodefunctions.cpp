#include "nodefunctions.hpp"

NodeFunction::NodeFunction()
{
    m_ExecuteIn = new PinExecute(this, PIN_INPUT);
}

NodeFunction::~NodeFunction()
{

}

GUIObj *NodeFunction::getObjectAtGlobal(sf::Vector2f tpos)
{
    GUIObj *tobj = NodeExecutable::getObjectAtGlobal(tpos);

    if(!tobj)
    {
        // check execution pins
        if(m_ExecuteIn->containsGlobal(tpos)) return m_ExecuteIn;
    }

    return tobj;
}

void NodeFunction::update()
{
    NodeExecutable::update();

    //sf::FloatRect dim = getSpriteDimensions();
    //sf::FloatRect edim = m_ExecuteIn->getSpriteDimensions();

    // update execution pins
    m_ExecuteIn->setPosition(m_Position + sf::Vector2f(4,2));
    //m_ExecuteOut->setPosition(m_Position + sf::Vector2f(dim.width-edim.width-4,2));

    // update pins
    m_ExecuteIn->update();
    //m_ExecuteOut->update();
}

void NodeFunction::draw(sf::RenderWindow *tscreen)
{
    NodeExecutable::draw(tscreen);

    // draw execution pins
    m_ExecuteIn->draw(tscreen);
    //m_ExecuteOut->draw(tscreen);
}

//////////////////////////////////////////////////////////////////
//
NodePrintToConsole::NodePrintToConsole()
{
    m_Name = "Print To Console";
    m_HeaderText = "Print To Console";

    // create input string pin
    Pin *spin = new PinStr(this, PIN_INPUT);
    m_PinInputs.push_back(spin);

    createSprite();
}

NodePrintToConsole::~NodePrintToConsole()
{

}

void NodePrintToConsole::execute()
{
    if(m_PinInputs.empty()) return;

    PinStr *ps = dynamic_cast<PinStr*>(m_PinInputs[0]);

    if(ps)
    {
        std::cout << ps->getString() << std::endl;
    }
}
