#ifndef _H_NODE_DATA
#define _H_NODE_DATA

#include "node.hpp"

enum EQUALITY{
                EQ_LESS_THAN                = 0x00,
                EQ_EQUAL_TO                 = 0x01,
                EQ_GREATER_THAN             = 0x02,
                EQ_LESS_THAN_OR_EQUAL_TO    = 0x04,
                EQ_GREATER_THAN_OR_EQUAL_TO = 0x06
                };


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

class NodeIntEquality: public Node
{
protected:
    virtual void createSprite();
    EQUALITY m_Mode;

public:
    NodeIntEquality(EQUALITY tmode); // 0x00 LT, 0x01 EQ, 0x10 GT, B2 is or equal to flag
    ~NodeIntEquality();

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
