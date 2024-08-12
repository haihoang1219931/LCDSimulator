#include "ApplicationController.h"
#include <memory.h>
#include "LCDLibrary.h"
#include "Button.h"
ApplicationController::ApplicationController()
{
    m_frameWidth = 128;
    m_frameHeight = 64;
    m_mainMenu = new MainMenu(this);
    m_gameMenu = new GameMenu(this);
    memset(m_frameData,0x00,sizeof(m_frameData));
    for(int i=0;i< BUTTON_ID::BTN_MAX; i++) {
        m_listButton[i] = new Button(this,i);
    }
    ::printf("ApplicationController constructor\r\n");
}

ApplicationController::~ApplicationController() {

}

void ApplicationController::loop() {
    switch(m_machineState) {
        case MACHINE_STATE::MACHINE_SHOW_MENU:
            m_mainMenu->loop();
            break;
        case MACHINE_STATE::MACHINE_ENTER_GAME:
            m_gameMenu->loop();
            break;
    }

}

void ApplicationController::checkAllButtonState() {
    for(int i=0;i< BUTTON_ID::BTN_MAX; i++) {
        m_listButton[i]->checkState();
    }
}

int ApplicationController::buttonState(BUTTON_ID buttonID) {
    return m_listButton[buttonID]->buttonState();
}

MACHINE_STATE ApplicationController::stateMachine() {
    return m_machineState;
}

void ApplicationController::setMachineState(MACHINE_STATE machineState) {
    if(machineState != m_machineState) {
        m_machineState = machineState;
        LCDLibrary::clear(getScreenData(),getScreenWidth(),getScreenHeight(),0x00);
    }
}

int ApplicationController::getScreenWidth() {
    return m_frameWidth;
}

int ApplicationController::getScreenHeight() {
    return m_frameHeight;
}
unsigned char* ApplicationController::getScreenData() {
    return m_frameData;
}
