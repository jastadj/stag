#ifndef CLASS_MOUSE
#define CLASS_MOUSE

#include <SFML\Graphics.hpp>

#include "guiobj.hpp"

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

    bool m_IsPressed;
    sf::Vector2f m_LocalClickedPos;
    sf::Vector2f m_GlobalClickedPos;
    sf::Vector2f m_ClickedOffset;

    std::vector<GUIObj*> m_Targets;

    void show();

public:

    void click();
    void release();
    bool isPressed() { return m_IsPressed;}
    void setPressed(bool tpressed) {m_IsPressed = tpressed;}
    void setOffset(sf::Vector2f toffset);
    void addTarget(GUIObj *newtarget);
    void clearTargets();

    sf::Vector2f getLocalClickedPos();
    sf::Vector2f getGlobalClickedPos();
    sf::Vector2f getOffset();
    std::vector<GUIObj*> *getTargets();

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
