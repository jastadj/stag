#include "node.hpp"

Node::Node()
{
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

    sf::RectangleShape headerspr(sf::Vector2f(w, headerh));
    headerspr.setFillColor(sf::Color(255,0,0,100));

    // create render texture
    m_RenderTexture.create(w,h+headerh);
    m_RenderTexture.clear(sf::Color(100,100,100,100));
    m_RenderTexture.draw(headerspr);
    m_RenderTexture.display();

    m_Sprite = sf::Sprite(m_RenderTexture.getTexture());
}
