#ifndef _H_NODE_DATA
#define _H_NODE_DATA

#include "node.hpp"

class NodeAddInt: public Node
{
protected:

    virtual void createSprite();
    bool m_DoSubtraction;

public:
    NodeAddInt(bool dosubtraction = false);
    ~NodeAddInt();

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
