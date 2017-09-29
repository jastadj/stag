#ifndef _H_NODE_EVENTS
#define _H_NODE_EVENTS


#include "node.hpp"

class NodeEvent: public NodeExecutable
{
private:

public:
    NodeEvent();
    ~NodeEvent();

};

class NodeEventStart: public NodeEvent
{
private:

public:
    NodeEventStart();
    ~NodeEventStart();
};

#endif // NODE_EVENTS
