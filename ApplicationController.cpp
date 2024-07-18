#include "ApplicationController.h"

ApplicationController::ApplicationController()
{
    m_frameWidth = 128;
    m_frameHeight = 64;
    m_mainMenu = new MainMenu(this);
    m_gameMenu = new GameMenu(this);
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
int ApplicationController::getScreenWidth() {
    return m_frameWidth;
}

int ApplicationController::getScreenHeight() {
    return m_frameHeight;
}
unsigned char* ApplicationController::getScreenData() {
    return m_frameData;
}
