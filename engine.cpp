#include "engine.hpp"

Engine *Engine::m_Instance = NULL;

Engine::Engine()
{
    m_IsRunning = false;

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
    m_ScreenBGColor = sf::Color(25,25,25);

    // init screen view
    m_ViewZoom = 1.0f;
    m_ViewCenter = sf::Vector2f( float(dwidth/2), float(dheight/2));
    m_View = sf::View( m_ViewCenter, sf::Vector2f( float(dwidth), float(dheight)) );
    m_View.zoom(m_ViewZoom);

    // init grid
    m_GridSubColor = sf::Color(70,70,70,128);
    m_GridSpacing = 32;

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
        m_View.setSize( sf::Vector2f(800 * m_ViewZoom,600 * m_ViewZoom));
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
            //sf::Vector2f mdelta = (m_Mouse.getLocalPos() - m_Mouse.right.getLocalClickedPos());
            sf::Vector2f mdelta = (m_Mouse.getLocalPos() - m_Mouse.right.getLocalClickedPos())*m_ViewZoom;

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
                sf::Vector2f mdelta = (m_Mouse.getLocalPos() - m_Mouse.right.getLocalClickedPos())*m_ViewZoom;

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
            // mouse wheel event
            else if(event.type == sf::Event::MouseWheelMoved)
            {
                // mouse wheel scrolled up
                if(event.mouseWheel.delta > 0)
                {
                    // zoom in
                    m_ViewZoom += 0.2;
                }
                // mouse wheel down
                else if(event.mouseWheel.delta < 0)
                {
                    m_ViewZoom -= 0.2;
                }
            }
        }

        // update

        // draw to screen
        drawGrid();
        m_Screen->draw(testbox);

        // draw to "hud"
        m_Screen->setView( m_Screen->getDefaultView());

        // display screen
        m_Screen->display();
    }
}

void Engine::drawGrid()
{
    //testing, not efficient, should clean up so not have to create every frame?
    sf::VertexArray gline(sf::Lines, 2);
    gline[0].color = m_GridSubColor;
    gline[1].color = m_GridSubColor;

    // get rect that is a global of screen
    sf::FloatRect viewrect = getGlobalView();

    //std::cout << "viewrect: TL(" << viewrect.left << "," << viewrect.top << ")  BR(" << viewrect.left + viewrect.width << "," << viewrect.top + viewrect.height << ")\n";

    // switch screen view to local (hud)
    m_Screen->setView( m_Screen->getDefaultView());

    sf::Vector2f goffset( int(int(viewrect.left / float(m_GridSpacing)) * m_GridSpacing) - viewrect.left,
                          int(int(viewrect.top / float(m_GridSpacing))  * m_GridSpacing) - viewrect.top);

    // draw vertical grid lines
    for(int i = 0; i <= int(viewrect.width / float(m_GridSpacing)*m_ViewZoom ) + 1; i++)
    {
        //gline[0].position = sf::Vector2f(i*m_GridSpacing, viewrect.top);
        //gline[1].position = sf::Vector2f( gline[0].position.x, viewrect.top + viewrect.height);

        gline[0].position = sf::Vector2f(i*m_GridSpacing*m_ViewZoom + goffset.x, 0);
        gline[1].position = sf::Vector2f( gline[0].position.x, viewrect.height);

        m_Screen->draw(gline);
    }

    // draw horizontal grid lines
    for(int i = 0; i <= int(viewrect.height / float(m_GridSpacing))+1; i++ )
    {
        //gline[0].position = sf::Vector2f(viewrect.left, i*m_GridSpacing);
        //gline[1].position = sf::Vector2f( viewrect.left + viewrect.width, gline[0].position.y);

        gline[0].position = sf::Vector2f(0, i*m_GridSpacing + goffset.y);
        gline[1].position = sf::Vector2f(viewrect.width, gline[0].position.y);

        m_Screen->draw(gline);
    }

    // draw axis lines


    // switch screen back to global view
    m_Screen->setView(m_View);

}

sf::FloatRect Engine::getGlobalView()
{
    // get rect that is a global of screen
    sf::Vector2f viewsize = m_View.getSize();
    sf::FloatRect viewrect;
    viewrect.left = m_Screen->mapPixelToCoords(sf::Vector2i(0,0)).x;
    viewrect.top = m_Screen->mapPixelToCoords(sf::Vector2i(0,0)).y;
    viewrect.width = viewsize.x;
    viewrect.height = viewsize.y;

    return viewrect;
}

void Engine::show()
{
    std::cout << "view center:" << m_ViewCenter.x << "," << m_ViewCenter.y << std::endl;
    std::cout << "\n";
    m_Mouse.show();
}
