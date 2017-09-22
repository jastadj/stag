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

    // temporary view center, used for panning
    sf::Vector2f tviewcenter = m_ViewCenter;

    sf::RectangleShape testbox( sf::Vector2f(512,512));

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

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {

        }
        else
        {

        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            // get delta of right clicked position and current mouse position (locally)
            sf::Vector2f mdelta = m_Mouse.getLocalPos() - m_Mouse.right.getLocalClickedPos();

            // apply delta to view center
            m_View.setCenter( m_ViewCenter - mdelta);

            // set view
            m_Screen->setView(m_View);
        }
        else
        {
            // if mouse button was clicked but is no longer
            if(m_Mouse.right.isPressed())
            {
                // get delta of right clicked position and current mouse position (locally)
                sf::Vector2f mdelta = m_Mouse.getLocalPos() - m_Mouse.right.getLocalClickedPos();

                // apply delta to view center
                m_ViewCenter -= mdelta;
                m_View.setCenter( m_ViewCenter);
                m_Screen->setView(m_View);

                m_Mouse.right.release();
            }

        }

        // process events in que
        while(m_Screen->pollEvent(event))
        {
            if(event.type == sf::Event::Closed) quit = true;

            // keyboard input
            else if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape) quit = true;
                else if(event.key.code == sf::Keyboard::F1) show();
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

                    // capture current view center in temp for panning
                    tviewcenter = m_ViewCenter;
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

void Engine::show()
{
    std::cout << "view center:" << m_ViewCenter.x << "," << m_ViewCenter.y << std::endl;
    std::cout << "\n";
    m_Mouse.show();
}
