#include "node.hpp"
#include "engine.hpp"

Node::Node()
{
    m_HeaderText = "anode";

    createSprite();
}

Node::~Node()
{
    // need to disconnect pins and delete them

}

void Node::createSprite()
{
    int w = 200;
    int h = 100;
    int headerh = 16;

    Engine *eptr = Engine::getInstance();
    std::vector<sf::Font*> *fonts = eptr->getFonts();

    // create header bar
    sf::RectangleShape headerspr(sf::Vector2f(w, headerh));
    headerspr.setFillColor(sf::Color(255,0,0,100));

    // create header text
    sf::Text htext(m_HeaderText, *(*fonts)[0], 12);
    htext.setPosition(sf::Vector2f(32,0));

    // create render texture
    m_RenderTexture.create(w,h+headerh);
    m_RenderTexture.clear(sf::Color(100,100,100,100));
    m_RenderTexture.draw(headerspr);
    m_RenderTexture.draw(htext);
    m_RenderTexture.display();

    m_Sprite = sf::Sprite(m_RenderTexture.getTexture());
}

Pin *Node::addPin(Pin *tpin)
{
    if(!tpin)
    {
        std::cout << "Error adding pin, pin is NULL\n";
        return NULL;
    }

    if(tpin->getParent() != this)
    {
        std::cout << "Error adding pin, parent does not match\n";
        return NULL;
    }

    if(tpin->getIO() == PIN_INPUT) m_PinInputs.push_back(tpin);
    else if(tpin->getIO() == PIN_OUTPUT) m_PinOutputs.push_back(tpin);
    else
    {
        std::cout << "Error adding pin, IO is not recognized\n";
        return NULL;
    }

    return tpin;
}

GUIObj *Node::getObjectAtGlobal(sf::Vector2f tpos)
{
    GUIObj *tobj = NULL;

    // check input pins
    for(int i = 0; i < int(m_PinInputs.size()); i++)
    {
        tobj = m_PinInputs[i]->getObjectAtGlobal(tpos);

        if(tobj) break;
    }

    // check output pins if object not already found
    if(!tobj)
    {
        for(int n = 0; n < int(m_PinOutputs.size()); n++)
        {
            tobj = m_PinOutputs[n]->getObjectAtGlobal(tpos);

            if(tobj) break;
        }
    }

    // return found object at position (may be null)
    return tobj;
}

void Node::draw(sf::RenderWindow *tscreen)
{
    // draw main sprite
    GUIObj::draw(tscreen);

    // draw input pins
    for(int i = 0; i < int(m_PinInputs.size()); i++)
    {
        m_PinInputs[i]->draw(tscreen);
    }

    // draw output pins
    for(int i = 0; i < int(m_PinOutputs.size()); i++)
    {
        m_PinOutputs[i]->draw(tscreen);
    }
}

void Node::update()
{
    // main update
    GUIObj::update();

    sf::FloatRect dim = m_Sprite.getLocalBounds();

    // update pins
    // note : pin positions are local offsets relative to main node window
    for(int i = 0; i < int(m_PinInputs.size()); i++)
    {
        m_PinInputs[i]->setPosition( m_Position + sf::Vector2f(4, 22 + i*20));
        m_PinInputs[i]->update();
    }
    for(int i = 0; i < int(m_PinOutputs.size()); i++)
    {
        sf::FloatRect pindim = m_PinOutputs[i]->getSpriteDimensions();

        m_PinOutputs[i]->setPosition( m_Position + sf::Vector2f(dim.width-4-pindim.width, 22 + i*20));
        m_PinOutputs[i]->update();
    }
}

void Node::show()
{
    STAGObj::show();
    std::cout << "NODE OBJECT\n";
    std::cout << "-----------\n";
}

