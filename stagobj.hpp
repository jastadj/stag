#ifndef CLASS_STAGOBJ
#define CLASS_STAGOBJ

#include "guiobj.hpp"

class STAGObj: public GUIObj
{
protected:
    virtual void createSprite()=0;

public:
    STAGObj();
    virtual ~STAGObj();

    //virtual void draw(sf::RenderWindow *tscreen);

    virtual void show();

};

#endif // CLASS_STAGOBJ
