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
