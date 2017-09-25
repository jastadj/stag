#ifndef CLASS_GUIOBJ
#define CLASS_GUIOBJ

#include <iostream>
#include <string>
#include <vector>

#include <SFML\Graphics.hpp>

class GUIObj
{
protected:

    std::string m_Name;

    // sprite
    virtual void createSprite()=0;
    sf::Sprite m_Sprite;
    sf::RenderTexture m_RenderTexture;
    sf::Vector2f m_Position;

public:
    GUIObj();
    ~GUIObj();

    void setPosition(sf::Vector2f tpos);
    void setName(std::string nname) { m_Name = nname;}

    sf::Vector2f getPosition();
    std::string getName() { return m_Name;}

    virtual bool containsGlobal(sf::Vector2f gcoord);
    virtual void draw(sf::RenderWindow *tscreen);
    virtual void update();
};
#endif // CLASS_GUIOBJ
