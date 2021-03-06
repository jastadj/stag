#ifndef CLASS_PIN
#define CLASS_PIN

#include "stagobj.hpp"
#include "inputbox.hpp"
#include "checkbox.hpp"

enum PIN_DATA_TYPE{PIN_INT, PIN_EXECUTE, PIN_STR, PIN_BOOL};
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
    bool hasOutputConnection();
    bool isConnected();

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

    PinExecute *getNextExecutionPin();

    //virtual bool connect(Pin *tpin);
    //virtual bool disconnect(Pin *tpin = NULL);

    virtual void show();

};

///////////////////////////////////////////////////////////////////
// DATA PINS

class PinData: public Pin
{
protected:



public:
    PinData(STAGObj *nparent, PIN_IO pio);
    ~PinData();


    virtual PIN_DATA_TYPE getDataType()=0;
    virtual GUIObj *getObjectAtGlobal(sf::Vector2f tpos);

    virtual void draw(sf::RenderWindow *tscreen);
    virtual void update();
    virtual void show();

};

class PinInt: public PinData
{
protected:

    int m_Value;
    InputBox m_InputBox;

public:
    PinInt(STAGObj *nparent, PIN_IO pio);
    ~PinInt();

    virtual PIN_DATA_TYPE getDataType() { return PIN_INT;}
    virtual GUIObj *getObjectAtGlobal(sf::Vector2f tpos);

    int getValue();
    void setValue(int tval);

    virtual void draw(sf::RenderWindow *tscreen);
    virtual void update();
    virtual void show();
};

class PinStr: public PinData
{
protected:

    std::string m_String;
    InputBox m_InputBox;

public:
    PinStr(STAGObj *nparent, PIN_IO pio);
    ~PinStr();

    virtual PIN_DATA_TYPE getDataType() { return PIN_STR;}
    virtual GUIObj *getObjectAtGlobal(sf::Vector2f tpos);

    std::string getString();
    void setString(std::string tstring);

    virtual void draw(sf::RenderWindow *tscreen);
    virtual void update();
    virtual void show();


};

class PinBool: public PinData
{
protected:

    bool m_Bool;

    CheckBox m_Checkbox;

public:
    PinBool(STAGObj *nparent, PIN_IO pio);
    ~PinBool();

    virtual PIN_DATA_TYPE getDataType() { return PIN_BOOL;}
    virtual GUIObj *getObjectAtGlobal(sf::Vector2f tpos);

    bool getBool();
    void setBool(bool tbool);

    virtual void draw(sf::RenderWindow *tscreen);
    virtual void update();
    virtual void show();
};
#endif // CLASS_PIN
