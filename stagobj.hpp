#ifndef CLASS_STAGOBJ
#define CLASS_STAGOBJ

#include "guiobj.hpp"

class STAGObj: public GUIObj
{
protected:
    virtual void createSprite()=0;

public:
    STAGObj();
    ~STAGObj();

    //virtual void draw(sf::RenderWindow *tscreen);

};

#endif // CLASS_STAGOBJ
