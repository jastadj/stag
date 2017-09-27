#include "stagobj.hpp"

STAGObj::STAGObj()
{

}

STAGObj::~STAGObj()
{

}

void STAGObj::show()
{
    GUIObj::show();
    std::cout << "STAGOBJ\n";
    std::cout << "-------\n";
}

/*
void STAGObj::draw(sf::RenderWindow *tscreen)
{
    GUIObj::draw(tscreen);
}
*/
