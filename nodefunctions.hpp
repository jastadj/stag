#ifndef _H_NODE_FUNCTIONS
#define _H_NODE_FUNCTIONS

#include "node.hpp"

class NodeFunction: public NodeExecutable
{
private:

    PinExecute *m_ExecuteIn;

public:
    NodeFunction();
    virtual ~NodeFunction();

    virtual GUIObj *getObjectAtGlobal(sf::Vector2f tpos);
    virtual void draw(sf::RenderWindow *tscreen);
    virtual void update();
};

class NodeBranch: public NodeFunction
{
protected:

    PinExecute *m_ExecuteWhenFalse;

public:
    NodeBranch();
    ~NodeBranch();

    virtual NodeExecutable *getNextExecution();


    virtual GUIObj *getObjectAtGlobal(sf::Vector2f tpos);
    virtual void update();
    virtual void draw(sf::RenderWindow *tscreen);

};

class NodePrintToConsole: public NodeFunction
{
private:

public:
    NodePrintToConsole();
    ~NodePrintToConsole();

    virtual void execute();
};

#endif // _H_NODE_FUNCTIONS
