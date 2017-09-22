#include "engine.hpp"

Engine *Engine::m_Instance = NULL;

Engine::Engine()
{
    m_IsRunning = false;
    m_ScreenBGColor = sf::Color(25,25,25);
}

Engine::~Engine()
{

}

bool Engine::init()
{
    const int dwidth = 800;
    const int dheight = 600;

    // init screen
    m_Screen = new sf::RenderWindow( sf::VideoMode(dwidth,dheight,32), "STAG");

    // init screen view
    m_ViewCenter = sf::Vector2f( float(dwidth/2), float(dheight/2));
    m_View = sf::View( m_ViewCenter, sf::Vector2f( float(dwidth), float(dheight)) );

    return true;
}

bool Engine::start()
{
    if(m_Instance == NULL) return false;
    else if(m_IsRunning) return false;

    // initialize
    init();

    // start main loop
    mainLoop();

    return true;
}

void Engine::mainLoop()
{
    bool quit = false;

    sf::RectangleShape testbox( sf::Vector2f(32,32));

    // main loop
    while(!quit)
    {
        // event que
        sf::Event event;

        // clear screen and fill with color
        m_Screen->clear(m_ScreenBGColor);

        // set view
        m_View.setCenter(m_ViewCenter);
        m_Screen->setView(m_View);


        // update mouse
        m_Mouse.update(m_Screen);

        if(m_Mouse.right.isPressed())
        {

        }

        // process events in que
        while(m_Screen->pollEvent(event))
        {
            if(event.type == sf::Event::Closed) quit = true;

            // keyboard input
            else if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape) quit = true;
            }
            // mouse input
            else if(event.type == sf::Event::MouseButtonPressed)
            {
                // left button
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    // capture click pos
                    m_Mouse.left.click();
                }
                else if(event.mouseButton.button == sf::Mouse::Right)
                {
                    // capture click pos
                    m_Mouse.right.click();
                }
            }
        }

        // update

        // draw to screen
        m_Screen->draw(testbox);

        // draw to "hud"
        m_Screen->setView( m_Screen->getDefaultView());

        // display screen
        m_Screen->display();
    }
}
