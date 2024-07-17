#include "ApplicationController.h"
#include "LCDLibrary.h"
ApplicationController::ApplicationController()
{
    m_frameWidth = 128;
    m_frameHeight = 64;
}

ApplicationController::~ApplicationController() {

}

void ApplicationController::loop() {
    switch(m_machineState) {
        case MACHINE_STATE::SHOW_MENU:
            showMenu();
            break;
        case MACHINE_STATE::PLAYING_SPACE_IMPACT:
            playSpaceImpact();
            break;
        case MACHINE_STATE::PLAYING_SNAKE:
            playSnake();
            break;
        case MACHINE_STATE::PLAYING_TANK:
            playTank();
            break;
        case MACHINE_STATE::PLAYING_RACING:
            playRacing();
            break;
    }

}
int ApplicationController::getScreenWidth() {
    return m_frameWidth;
}
void ApplicationController::showMenu() {
//    for(char i = 'A'; i < 'N'+1; i ++)
//    LCDLibrary::drawChar(m_frameData,m_frameWidth,m_frameHeight,
//                         (const unsigned char**)fonts58,i,(i-'A')* (8+1) ,0);

//    for(char i = 'M'; i < 'Z'+1; i ++)
//    LCDLibrary::drawChar(m_frameData,m_frameWidth,m_frameHeight,
//                         (const unsigned char**)fonts58,i,(i-'M')* (8+1) ,13+1);

//    for(char i = 'a'; i < 'z'; i ++)
//    LCDLibrary::drawChar(m_frameData,m_frameWidth,m_frameHeight,
//                         (const unsigned char**)fonts58,i,(i-'a')* (8+1) ,(13+1)*2+1);
//    for(char i = '0'; i < '9'; i ++)
//    LCDLibrary::drawChar(m_frameData,m_frameWidth,m_frameHeight,
//                         (const unsigned char**)fonts58,i,(i-'0')* (8+1) ,(13+1)*3+1);
    LCDLibrary::drawString(m_frameData,m_frameWidth,m_frameHeight,
                         (const unsigned char**)fonts58,"GAME SELECT",
                           m_frameWidth / 2 - strlen("GAME SELECT")*9/2 ,3);
}
void ApplicationController::playSpaceImpact() {}
void ApplicationController::playSnake() {}
void ApplicationController::playTank() {}
void ApplicationController::playRacing() {}
int ApplicationController::getScreenHeight() {
    return m_frameHeight;
}
unsigned char* ApplicationController::getScreenData() {
    return m_frameData;
}
