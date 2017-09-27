#ifndef _H_NODE_EVENTS
#define _H_NODE_EVENTS


#include "node.hpp"

class NodeEvent: public Node
{
private:

    PinExecute *m_ExecuteOut;

public:
    NodeEvent();
    ~NodeEvent();

    virtual GUIObj *getObjectAtGlobal(sf::Vector2f tpos);
    virtual void draw(sf::RenderWindow *tscreen);
    virtual void update();
};

class NodeEventStart: public NodeEvent
{
private:

public:
    NodeEventStart();
    ~NodeEventStart();
};

#endif // NODE_EVENTS
