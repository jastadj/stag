#include "node.hpp"
#include "engine.hpp"

Node::Node()
{
    m_HeaderText = "anode";

    createSprite();
}

Node::~Node()
{

}

void Node::createSprite()
{
    int w = 200;
    int h = 200;
    int headerh = 16;

    Engine *eptr = Engine::getInstance();
    std::vector<sf::Font*> *fonts = eptr->getFonts();

    // create header bar
    sf::RectangleShape headerspr(sf::Vector2f(w, headerh));
    headerspr.setFillColor(sf::Color(255,0,0,100));

    // create header text
    sf::Text htext(m_HeaderText, *(*fonts)[0], 12);

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

void Node::draw(sf::RenderWindow *tscreen)
{
    // draw main sprite
    GUIObj::draw(tscreen);

    // draw input pins
    for(int i = 0; i < int(m_PinInputs.size()); i++)
    {
        m_PinInputs[i]->draw(tscreen);
    }
}

void Node::update()
{
    // main update
    GUIObj::update();

    // update pins
    // note : pin positions are local offsets relative to main node window
    for(int i = 0; i < int(m_PinInputs.size()); i++)
    {
        m_PinInputs[i]->setPosition( m_Position + sf::Vector2f(4, 18 + i*4));
        m_PinInputs[i]->update();
    }
}
