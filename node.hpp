#ifndef CLASS_NODE
#define CLASS_NODE

#include "stagobj.hpp"
#include "pin.hpp"

class Node: public STAGObj
{
protected:

    std::string m_HeaderText;

    virtual void createSprite();


    Pin *addPin(Pin *tpin);
    std::vector<Pin*> m_PinInputs;
    std::vector<Pin*> m_PinOutputs;

public:
    Node();
    virtual ~Node();

    virtual GUIObj *getObjectAtGlobal(sf::Vector2f tpos);

    virtual void draw(sf::RenderWindow *tscreen);
    virtual void update();

    virtual void show();
};



class NodeAddInt: public Node
{
private:

    void createSprite();

public:
    NodeAddInt();
    ~NodeAddInt();
};



#endif // CLASS_NODE
