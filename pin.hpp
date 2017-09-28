#ifndef CLASS_PIN
#define CLASS_PIN

#include "stagobj.hpp"
#include "inputbox.hpp"

enum PIN_DATA_TYPE{PIN_INT, PIN_EXECUTE};
enum PIN_IO{PIN_INPUT, PIN_OUTPUT};

// forward declaration


class Pin: public STAGObj
{
protected:

    STAGObj *m_Parent;
    PIN_IO m_IO;

    Pin *m_InConnection;
    std::vector<Pin*> m_OutConnections;

    sf::Color m_PinColor;



    virtual void createSprite();

public:
    Pin(STAGObj *nparent, PIN_IO pio);
    ~Pin();

    STAGObj *getParent();

    bool hasInputConnection();

    virtual PIN_IO getIO() { return m_IO;}
    virtual PIN_DATA_TYPE getDataType()=0;

    virtual bool connect(Pin *tpin);
    virtual bool disconnect(Pin *tpin = NULL);

    virtual GUIObj *getObjectAtGlobal(sf::Vector2f tpos);
    virtual void draw(sf::RenderWindow *tscreen);
    //virtual void update();

    virtual void show();

};

class PinExecute: public Pin
{
private:

    void createSprite();

public:
    PinExecute(STAGObj *nparent, PIN_IO pio);
    ~PinExecute();
    PIN_DATA_TYPE getDataType() { return PIN_EXECUTE;}
};

class PinInt: public Pin
{
protected:

    InputBox m_InputBox;

    int m_Value;

public:
    PinInt(STAGObj *nparent, PIN_IO pio);
    ~PinInt();

    virtual PIN_DATA_TYPE getDataType() { return PIN_INT;}

    virtual GUIObj *getObjectAtGlobal(sf::Vector2f tpos);

    void draw(sf::RenderWindow *tscreen);
    void update();
};
#endif // CLASS_PIN
