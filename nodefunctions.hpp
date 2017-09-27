#ifndef _H_NODE_FUNCTIONS
#define _H_NODE_FUNCTIONS

#include "node.hpp"

class NodeFunction: public Node
{
private:

    PinExecute *m_ExecuteIn;
    PinExecute *m_ExecuteOut;


public:
    NodeFunction();
    virtual ~NodeFunction();

    virtual GUIObj *getObjectAtGlobal(sf::Vector2f tpos);
    virtual void draw(sf::RenderWindow *tscreen);
    virtual void update();
};

class NodePrintToConsole: public NodeFunction
{
private:

public:
    NodePrintToConsole();
    ~NodePrintToConsole();
};

#endif // _H_NODE_FUNCTIONS
