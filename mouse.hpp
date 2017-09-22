#ifndef CLASS_MOUSE
#define CLASS_MOUSE

#include <SFML\Graphics.hpp>

enum MOUSE_BUTTONS{MOUSE_LEFT, MOUSE_RIGHT};

// forward dec
class Mouse;

class MouseButton
{
private:
    MouseButton();
    ~MouseButton();

    Mouse *m_Parent;

    MOUSE_BUTTONS m_Type;

    sf::Vector2f m_LocalClickedPos;
    sf::Vector2f m_GlobalClickedPos;

    void show();

public:

    void click();
    bool isPressed();

    sf::Vector2f getLocalClickedPos();
    sf::Vector2f getGlobalClickedPos();

    friend Mouse;
};

class Mouse
{
private:

    // position info
    sf::Vector2f m_LocalPos;
    sf::Vector2f m_GlobalPos;

public:
    Mouse();
    ~Mouse();

    // mouse button objects
    MouseButton left;
    MouseButton right;

    sf::Vector2f getLocalPos();
    sf::Vector2f getGlobalPos();

    void update(sf::RenderWindow *tscreen);
    void show();
};
#endif // CLASS_MOUSE
