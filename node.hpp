#ifndef CLASS_NODE
#define CLASS_NODE

#include "stagobj.hpp"

class Node: public STAGObj
{
protected:

    void createSprite();

public:
    Node();
    ~Node();
};
#endif // CLASS_NODE
