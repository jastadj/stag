#ifndef CLASS_NODE
#define CLASS_NODE

#include "stagobj.hpp"

class Node: public STAGObj
{
protected:

    std::string m_HeaderText;

    void createSprite();

public:
    Node();
    ~Node();
};
#endif // CLASS_NODE
