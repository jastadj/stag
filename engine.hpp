#ifndef CLASS_ENGINE
#define CLASS_ENGINE

#include <cstdlib>
#include <iostream>
#include <string>

#include <SFML\Graphics.hpp>

#include "mouse.hpp"
#include "node.hpp"
#include "nodeevents.hpp"
#include "nodefunctions.hpp"
#include "nodedata.hpp"

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
    float m_ViewZoom;
    sf::Vector2f m_ViewCenter;
    sf::Color m_ScreenBGColor;

    // grid
    sf::Color m_GridSubColor;
    int m_GridSpacing;

    // init
    bool init();
    bool initNodes();

    // master node list
    std::vector<Node*> m_MasterNodeList;

    // objects
    Mouse m_Mouse;
    std::vector<sf::Font*> m_Fonts;
    std::vector<Node*> m_Nodes;

    // mainloop
    void mainLoop();
    void drawGrid();
    void runScript();

    // util
    sf::FloatRect getGlobalView();
    GUIObj *getObjectAtGlobal(sf::Vector2f tpos);

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

    std::vector<sf::Font*> *getFonts();

    bool isSelected(GUIObj *tobj);
    void deselectAllMouseTargets();

    void executeNode(NodeExecutable *tnode);

    //debug
    void show();
};
#endif // CLASS_ENGINE
