#ifndef CLASS_INPUTBOX
#define CLASS_INPUTBOX

#include "guiobj.hpp"

class InputBox: public GUIObj
{
protected:

    virtual void createSprite();

    int m_Width;

public:
    InputBox();
    ~InputBox();

};
#endif // CLASS_INPUTBOX
