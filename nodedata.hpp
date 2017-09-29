#ifndef _H_NODE_DATA
#define _H_NODE_DATA

#include "node.hpp"

class NodeAddInt: public Node
{
protected:

    virtual void createSprite();

public:
    NodeAddInt();
    ~NodeAddInt();

    virtual void update();
};

class NodeSubtractInt: public Node
{
protected:

    virtual void createSprite();

public:
    NodeSubtractInt();
    ~NodeSubtractInt();

    virtual void update();
};

class NodeIntToStr: public Node
{
protected:

    virtual void createSprite();

public:
    NodeIntToStr();
    ~NodeIntToStr();

    virtual void update();

};

#endif // _H_NODE_DATA
