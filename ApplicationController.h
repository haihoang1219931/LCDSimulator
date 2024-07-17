#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include "Game/GameItem.h"

enum MACHINE_STATE {
    SHOW_MENU,
    PLAYING_SPACE_IMPACT,
    PLAYING_SNAKE,
    PLAYING_TANK,
    PLAYING_RACING
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
    void showMenu();
    void playSpaceImpact();
    void playSnake();
    void playTank();
    void playRacing();
    virtual int printf(const char *fmt, ...) = 0;
    virtual void msleep(int millis) = 0;

protected:
    MACHINE_STATE m_machineState;
    int m_frameWidth;
    int m_frameHeight;
    unsigned char m_frameData[33177600];
    GameItem* m_gameList;
    int m_currentGameID;
};

#endif // APPLICATIONCONTROLLER_H
