#ifndef CLASS_ENGINE
#define CLASS_ENGINE

#include <cstdlib>
#include <iostream>
#include <string>

#include <SFML\Graphics.hpp>

#include "mouse.hpp"

class Engine
{
private:
    // singleton
    Engine();
    ~Engine();
    static Engine *m_Instance;
    bool m_IsRunning;

    // screen
    sf::RenderWindow *m_Screen;
    sf::View m_View;
    sf::Vector2f m_ViewCenter;
    sf::Color m_ScreenBGColor;

    // init
    bool init();

    // objects
    Mouse m_Mouse;

    // mainloop
    void mainLoop();

public:

    static Engine *getInstance()
    {
        if(m_Instance == NULL)
        {
            m_Instance = new Engine;
        }

        return m_Instance;
    }

    bool start();

    //debug
    void show();
};
#endif // CLASS_ENGINE
