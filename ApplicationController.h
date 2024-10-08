#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include "MainMenu.h"
#include "Game/GameMenu.h"
class Button;
enum MACHINE_STATE {
    MACHINE_SHOW_MENU,
    MACHINE_ENTER_GAME,
    MACHINE_ENTER_MESSAGE,
    MACHINE_ENTER_CALL,
    MACHINE_ENTER_CONTACTS,
};

enum BUTTON_ID {
    BTN_UP,
    BTN_DOWN,
    BTN_LEFT,
    BTN_RIGHT,
    BTN_ENTER,
    BTN_BACK,
    BTN_MAX,
};
class ApplicationController
{
public:
    explicit ApplicationController();
    virtual ~ApplicationController();
    
    int getScreenWidth();
    int getScreenHeight();
    unsigned char* getScreenData();
    void loop();
    void checkAllButtonState();
    int buttonState(BUTTON_ID buttonID);
    MACHINE_STATE stateMachine();
    void setMachineState(MACHINE_STATE machineState);
    virtual int printf(const char *fmt, ...) = 0;
    virtual void msleep(int millis) = 0;
    virtual long getSystemTimeInMillis() = 0;

protected:
    MACHINE_STATE m_machineState;
    int m_frameWidth;
    int m_frameHeight;
    unsigned char m_frameData[9600]; // 320x240 bit
    MainMenu* m_mainMenu;
    GameMenu* m_gameMenu;
    Button* m_listButton[BUTTON_ID::BTN_MAX];
};

#endif // APPLICATIONCONTROLLER_H
