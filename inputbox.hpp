#ifndef CLASS_INPUTBOX
#define CLASS_INPUTBOX

#include "guiobj.hpp"

#include <iostream>
#include <string>

#define INPUTBOX_BLINK 250

class InputBox: public GUIObj
{
protected:

    virtual void createSprite();
    virtual void createTextSprite();

    int m_Width;

    std::string m_String;
    sf::Text m_Text;
    sf::Text m_Cursor;
    sf::Clock m_BlinkTimer;

public:
    InputBox();
    ~InputBox();

    std::string getString() { return m_String;}

    void setString(std::string ninput);

    virtual void EventSelected();

    virtual bool processEvents(sf::RenderWindow *tscreen, sf::Event &events);
    virtual void update();
    virtual void draw(sf::RenderWindow *tscreen);

};
#endif // CLASS_INPUTBOX
