#ifndef CLASS_PIN
#define CLASS_PIN

#include "stagobj.hpp"

enum PIN_DATA_TYPE{PIN_INT};
enum PIN_IO{PIN_INPUT, PIN_OUTPUT};

// forward declaration


class Pin: public STAGObj
{
protected:

    STAGObj *m_Parent;
    sf::Color m_PinColor;

    PIN_DATA_TYPE m_DataType;
    PIN_IO m_IO;

    virtual void createSprite();

public:
    Pin(STAGObj *nparent, PIN_IO pio);
    ~Pin();

    STAGObj *getParent();

    virtual PIN_IO getIO() { return m_IO;}
    virtual PIN_DATA_TYPE getDataType()=0;

    //virtual void draw(sf::RenderWindow *tscreen);
    //virtual void update();
};

class PinInt: public Pin
{
protected:

public:
    PinInt(STAGObj *nparent, PIN_IO pio);
    ~PinInt();

    virtual PIN_DATA_TYPE getDataType();
};
#endif // CLASS_PIN
