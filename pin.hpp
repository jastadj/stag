#ifndef CLASS_PIN
#define CLASS_PIN

#include "stagobj.hpp"
#include "inputbox.hpp"

enum PIN_DATA_TYPE{PIN_INT, PIN_EXECUTE, PIN_STR};
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

class PinData: public Pin
{
protected:

    InputBox m_InputBox;

public:
    PinData(STAGObj *nparent, PIN_IO pio);
    ~PinData();

    virtual PIN_DATA_TYPE getDataType()=0;
    virtual void draw(sf::RenderWindow *tscreen);
    virtual void update();

};

class PinInt: public PinData
{
protected:

    int m_Value;

public:
    PinInt(STAGObj *nparent, PIN_IO pio);
    ~PinInt();

    virtual PIN_DATA_TYPE getDataType() { return PIN_INT;}

    virtual GUIObj *getObjectAtGlobal(sf::Vector2f tpos);

    int getValue();
    void setValue(int tval);

    void draw(sf::RenderWindow *tscreen);
    void update();
    virtual void show();
};

class PinStr: public Pin
{
protected:

public:
    PinStr(STAGObj *nparent, PIN_IO pio);
    ~PinStr();

    virtual PIN_DATA_TYPE getDataType() { return PIN_STR;}


};
#endif // CLASS_PIN
