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

    // init fonts
    m_Fonts.push_back( new sf::Font);
    m_Fonts.back()->loadFromFile(".\\data\\fonts\\font.ttf");

    // init master nodes list
    initNodes();

    return true;
}

bool Engine::initNodes()
{
    // create master list of nodes

    return true;

}

std::vector<sf::Font*> *Engine::getFonts()
{
    return &m_Fonts;
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

    m_Nodes.push_back(new NodeEventStart);
    m_Nodes.push_back(new NodePrintToConsole);
    m_Nodes.back()->setPosition(sf::Vector2f(400,50));
    m_Nodes.push_back(new NodeAddInt);
    m_Nodes.back()->setPosition(sf::Vector2f(200,200));
    m_Nodes.push_back(new NodeIntEquality(EQ_LESS_THAN));
    m_Nodes.back()->setPosition(sf::Vector2f(200,400));
    m_Nodes.push_back(new NodeIntToStr);
    m_Nodes.back()->setPosition(sf::Vector2f(200,0));

    sf::VertexArray m_VertexArray(sf::Lines, 2);
    bool doDrawVertexArray = false;


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

        // check mouse state (for things like dragging)
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(m_Mouse.left.isPressed())
            {
                std::vector<GUIObj*> *tgts = m_Mouse.left.getTargets();

                for(int i = 0; i < int(tgts->size()); i++)
                {
                    Node *tn = dynamic_cast<Node*>( (*tgts)[i] );
                    Pin *tp = dynamic_cast<Pin*>( (*tgts)[i]);

                    if(tn) (*tgts)[i]->setPosition(m_Mouse.getGlobalPos() + m_Mouse.left.getOffset());
                    else if(tp) { m_VertexArray[1] = m_Mouse.getGlobalPos(); doDrawVertexArray = true;}
                }

            }
        }
        else
        {
            // if left mouse button WAS pressed
            if(m_Mouse.left.isPressed())
            {
                m_Mouse.left.release();
                doDrawVertexArray = false;

                // if left mouse button has pin selected
                if(!m_Mouse.left.getTargets()->empty())
                {
                    Pin *tpin = dynamic_cast<Pin*>( (*m_Mouse.left.getTargets())[0] );
                    if(tpin)
                    {
                        // if left mouse button was released over another pin
                        GUIObj *tobj = getObjectAtGlobal(m_Mouse.getGlobalPos());
                        Pin *dpin = dynamic_cast<Pin*>(tobj);
                        if(dpin)
                        {
                            // attempt to connect pins
                            //if(tpin->connect(dpin)) std::cout << "Pins connected.\n";
                            tpin->connect(dpin);
                        }
                        // else assume user is disconnecting pin
                        else if(tpin->isConnected()) tpin->disconnect();

                    }
                }
            }
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
            if(!m_Mouse.left.getTargets()->empty())
            {
                if( (*m_Mouse.left.getTargets())[0]->processEvents(m_Screen, event)) continue;
            }

            if(event.type == sf::Event::Closed) quit = true;

            // keyboard input
            else if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape) quit = true;
                else if(event.key.code == sf::Keyboard::F1) show();
                else if(event.key.code == sf::Keyboard::F2)
                {
                    if(!m_Mouse.left.getTargets()->empty()) (*m_Mouse.left.getTargets())[0]->show();
                }
                else if(event.key.code == sf::Keyboard::F5) runScript();
            }
            // mouse input
            else if(event.type == sf::Event::MouseButtonPressed)
            {
                // left button
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    // capture click pos
                    m_Mouse.left.click();

                    // clear target
                    m_Mouse.left.clearTargets();

                    // find object at target mouse position (global)
                    GUIObj *tobj = getObjectAtGlobal(m_Mouse.getGlobalPos());

                    // if an object was found at target position
                    if(tobj)
                    {
                        // add to left mouse target
                        m_Mouse.left.addTarget(tobj);

                        // set mouse offset of position clicked with reference to object
                        m_Mouse.left.setOffset( tobj->getPosition() - m_Mouse.left.getGlobalClickedPos());

                        // if object is type pin, set line start
                        Pin *tpin = dynamic_cast<Pin*>(tobj);
                        if(tpin) m_VertexArray[0].position = tobj->getCenterPosition();
                    }

                }
                else if(event.mouseButton.button == sf::Mouse::Right)
                {
                    // capture click pos
                    m_Mouse.right.click();

                    // capture current view center in temp for panning
                    //m_Mouse.right.setOffset(m_ViewCenter);
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
        for(int i = 0; i < int(m_Nodes.size()); i++)
        {
            m_Nodes[i]->update();
        }

        // draw to screen
        drawGrid();
        //m_Screen->draw(testbox);
        for(int i = 0; i < int(m_Nodes.size()); i++)
        {
            m_Nodes[i]->draw(m_Screen);
        }

        // draw connection line
        if(doDrawVertexArray) m_Screen->draw(m_VertexArray);

        // draw to "hud"
        m_Screen->setView( m_Screen->getDefaultView());

        // display screen
        m_Screen->display();
    }
}

void Engine::runScript()
{
    NodeEvent *startnode = NULL;

    std::cout << "Starting script...\n";

    // look for start event node
    for(int i = 0; i < int(m_Nodes.size()); i++)
    {
        // cast to node event start
        NodeEventStart *cn = dynamic_cast<NodeEventStart*>(m_Nodes[i]);

        // start node found
        if(cn)
        {
            // if already found one
            if(startnode) std::cout << "Multiple start event nodes found!!\n";
            else startnode = cn;
        }
    }

    if(!startnode) std::cout << "Error, unable to find start node!\n";
    else executeNode(startnode);
}

void Engine::executeNode(NodeExecutable *tnode)
{
    if(!tnode)
    {
        std::cout << "Execution done.\n";
        return;
    }

    //std::cout << "Running executable node:" << tnode->getName() << std::endl;
    tnode->execute();

    NodeExecutable *nnode = tnode->getNextExecution();

    executeNode(nnode);
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

GUIObj *Engine::getObjectAtGlobal(sf::Vector2f tpos)
{
    GUIObj *tobj = NULL;

    // check each node window
    for(int i = 0; i < int(m_Nodes.size()); i++)
    {
        // if position is inside node window
        if( m_Nodes[i]->containsGlobal(tpos))
        {

            // find objects inside node window at target pos
            tobj = m_Nodes[i]->getObjectAtGlobal(tpos);

            // if no object was found inside node window, return node window
            if(!tobj) return m_Nodes[i];
            else return tobj;
        }
    }

    // nothing was found
    return NULL;
}

bool Engine::isSelected(GUIObj *tobj)
{
    if(!tobj) return false;

    // get mouse button targets
    std::vector<GUIObj*> *lt = m_Mouse.left.getTargets();
    std::vector<GUIObj*> *rt = m_Mouse.right.getTargets();

    // check to see if this is in the left button target list
    for(int i = 0; i < int(lt->size()); i++)
    {
        if(tobj == (*lt)[i]) return true;
    }

    // check to see if this is in the right button target list
    for(int i = 0; i < int(rt->size()); i++)
    {
        if(tobj == (*rt)[i]) return true;
    }

    // this object was not found in any mouse button lists
    return false;
}

void Engine::deselectAllMouseTargets()
{
    m_Mouse.left.clearTargets();
    m_Mouse.right.clearTargets();
}

void Engine::show()
{
    std::cout << "view center:" << m_ViewCenter.x << "," << m_ViewCenter.y << std::endl;
    std::cout << "\n";
    m_Mouse.show();
}
