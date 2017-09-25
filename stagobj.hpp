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



};

#endif // CLASS_STAGOBJ
