#ifndef CLASS_NODE
#define CLASS_NODE

#include "stagobj.hpp"
#include "pin.hpp"

class Node: public STAGObj
{
protected:

    std::string m_HeaderText;

    virtual void createSprite();

    std::vector<Pin*> m_PinInputs;
    std::vector<Pin*> m_PinOutputs;

public:
    Node();
    ~Node();

    Pin *addPin(Pin *tpin);

    virtual void draw(sf::RenderWindow *tscreen);
    virtual void update();
};

#endif // CLASS_NODE
