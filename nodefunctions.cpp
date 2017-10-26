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

////////////////////////////////////////////////////
//

NodeBranch::NodeBranch()
{
    m_Name = "Branch";
    m_HeaderText = "Branch";

    // add execution node when pin is false
    m_ExecuteWhenFalse = new PinExecute(this, PIN_OUTPUT);

    // add bool pin to determine which exec branch to take
    addPin( new PinBool(this, PIN_INPUT));

    createSprite();
}

NodeBranch::~NodeBranch()
{

}

GUIObj *NodeBranch::getObjectAtGlobal(sf::Vector2f tpos)
{
    GUIObj *tobj = NodeFunction::getObjectAtGlobal(tpos);

    if(!tobj)
    {
        if(m_ExecuteWhenFalse->containsGlobal(tpos)) return m_ExecuteWhenFalse;
    }
}

NodeExecutable *NodeBranch::getNextExecution()
{
    PinBool *tb = dynamic_cast<PinBool*>(m_PinInputs[0]);
    PinExecute *nextpin = m_ExecuteOut->getNextExecutionPin();

    if(tb)
    {
        if(tb->getBool()) nextpin = m_ExecuteOut->getNextExecutionPin();
        else nextpin = m_ExecuteWhenFalse->getNextExecutionPin();
    }

    if(nextpin)
    {
        NodeExecutable *nnode = dynamic_cast<NodeExecutable*>(nextpin->getParent());

        if(nnode) return nnode;
    }

    return NULL;
}

void NodeBranch::update()
{
    NodeFunction::update();

    m_ExecuteOut->setPosition(m_ExecuteOut->getPosition() + sf::Vector2f(0,40) );
    m_ExecuteOut->update();

    m_ExecuteWhenFalse->setPosition( m_ExecuteOut->getPosition() + sf::Vector2f(0,40));
    m_ExecuteWhenFalse->update();
}

void NodeBranch::draw(sf::RenderWindow *tscreen)
{
    NodeFunction::draw(tscreen);

    m_ExecuteWhenFalse->draw(tscreen);


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
