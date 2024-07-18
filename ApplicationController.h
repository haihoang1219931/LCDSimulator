#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include "MainMenu.h"
#include "Game/GameMenu.h"

enum MACHINE_STATE {
    MACHINE_SHOW_MENU,
    MACHINE_ENTER_GAME,
    MACHINE_ENTER_MESSAGE,
    MACHINE_ENTER_CALL,
};

enum BUTTON_ID {
    BTN_UP,
    BTN_DOWN,
    BTN_LEFT,
    BTN_RIGHT,
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
    virtual bool isButtonPressed(BUTTON_ID buttonID) = 0;
    virtual int printf(const char *fmt, ...) = 0;
    virtual void msleep(int millis) = 0;

protected:
    MACHINE_STATE m_machineState;
    int m_frameWidth;
    int m_frameHeight;
    unsigned char m_frameData[33177600];
    MainMenu* m_mainMenu;
    GameMenu* m_gameMenu;
    int m_currentGameID;
};

#endif // APPLICATIONCONTROLLER_H
