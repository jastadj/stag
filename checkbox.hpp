#ifndef CLASS_CHECKBOX
#define CLASS_CHECKBOX

#include "guiobj.hpp"

class CheckBox : public GUIObj
{
protected:

    virtual void createSprite();

    bool m_Checked;

public:
    CheckBox();
    ~CheckBox();

    bool isChecked() { return m_Checked;}
    void setChecked(bool nchecked);
    void toggleChecked();

    //virtual void EventSelected();
    virtual bool processEvents(sf::RenderWindow *tscreen, sf::Event &event);
    //virtual void update();
    //virtual void draw(sf::RenderWindow *tscreen);

};
#endif // CLASS_CHECKBOX
