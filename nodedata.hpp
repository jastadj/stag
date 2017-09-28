#ifndef _H_NODE_DATA
#define _H_NODE_DATA

#include "node.hpp"

class NodeAddInt: public Node
{
private:

    void createSprite();

public:
    NodeAddInt();
    ~NodeAddInt();

    virtual void update();
};

#endif // _H_NODE_DATA
