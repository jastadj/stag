#include "nodeevents.hpp"

NodeEvent::NodeEvent()
{

}

NodeEvent::~NodeEvent()
{

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
