#include "GameMenu.h"
#include "../ApplicationController.h"
#include "../LCDLibrary.h"
#include "../Button.h"
#include "Snake.h"
#include "SpaceImpact.h"
GameMenu::GameMenu(ApplicationController* app)
{
    m_app = app;
    m_currentID = GAME_MIN;
    m_gameTittle[GAME_SPACE_IMPACT] = "Space Impact";
    m_gameTittle[GAME_SPACE_IMPACT_2] = "Space Impact II";
    m_gameTittle[GAME_RACING] = "Racing";
    m_gameTittle[GAME_SNAKE] = "Snake";
    m_gameTittle[GAME_TANK] = "Tank";
    m_gameTittle[GAME_TANK_2] = "Tank II";
    m_gameTittle[GAME_SPACE_INVADER] = "Space Invader";
    m_gameTittle[GAME_CHESS] = "Chess";
    m_machineState = GAME_STATE::GAME_SHOW_MENU;
    m_gameItem = nullptr;
}
void GameMenu::loop(){
    switch(m_machineState) {
    case GAME_STATE::GAME_SHOW_MENU:
        showMenu();
        break;
    case GAME_STATE::GAME_PLAY:
        playGame();
        break;
    case GAME_STATE::GAME_EXIT:
        exitGame();
        break;

    }

}

void GameMenu::showMenu() {
    if(m_currentID == GAME_MIN) {
        clearDisplay();
        m_currentID = GAME_MIN+1;
    }
    int currentID = m_currentID;
    // check input
    m_app->checkAllButtonState();

    // check navigate button state
    if(m_app->buttonState(BUTTON_ID::BTN_RIGHT) == BUTTON_STATE::BUTTON_PRESS ||
            m_app->buttonState(BUTTON_ID::BTN_DOWN) == BUTTON_STATE::BUTTON_PRESS){
        currentID ++;
        if(currentID >= GAME_ID::GAME_MAX) {
            currentID = GAME_ID::GAME_MIN + 1;
        }
    }
    else if(m_app->buttonState(BUTTON_ID::BTN_LEFT) == BUTTON_STATE::BUTTON_PRESS ||
            m_app->buttonState(BUTTON_ID::BTN_UP) == BUTTON_STATE::BUTTON_PRESS){
        currentID --;
        if(currentID <= GAME_ID::GAME_MIN) {
            currentID = GAME_ID::GAME_MAX - 1;
        }
    }
    if(currentID != m_currentID) {
        m_currentID = currentID;
        clearDisplay();
    }

    drawMenu();
    if(m_app->buttonState(BUTTON_ID::BTN_BACK) == BUTTON_STATE::BUTTON_PRESS) {
        m_app->setMachineState(MACHINE_STATE::MACHINE_SHOW_MENU);
    } else if(m_app->buttonState(BUTTON_ID::BTN_ENTER) == BUTTON_STATE::BUTTON_PRESS) {
        setMachineState(GAME_STATE::GAME_PLAY);
    }
}

void GameMenu::playGame() {
    if(m_gameItem == nullptr) {
        switch (m_currentID) {
        case GAME_ID::GAME_SNAKE: {
            m_gameItem = new Snake(this,m_currentID);
        }
            break;
        case GAME_ID::GAME_SPACE_IMPACT: {
            m_gameItem = new SpaceImpact(this,m_currentID);
        }
            break;
        }
    } else {
        m_gameItem->loop();
    }
}

void GameMenu::exitGame() {
    if(m_gameItem != nullptr) {
        delete m_gameItem;
        m_gameItem = nullptr;
        setMachineState(GAME_STATE::GAME_SHOW_MENU);
    }
}

ApplicationController* GameMenu::app() {
    return m_app;
}
GAME_STATE GameMenu::machineState() {
    return (GAME_STATE)m_machineState;
}
void GameMenu::setMachineState(GAME_STATE newState) {
    m_machineState = newState;
    clearDisplay();
}

void GameMenu::clearDisplay() {
    LCDLibrary::clear(m_app->getScreenData(),m_app->getScreenWidth(),m_app->getScreenHeight(),0x00);
}
void GameMenu::drawMenu() {
    int rowLimit = 4;
    int currentRow = 0;
    // draw content
    //   print previous items
    int startDrawItem = GAME_MIN + 1;
    if(m_currentID > rowLimit) {
        startDrawItem = m_currentID - (rowLimit - 1);
    }
    int stopDrawItem = rowLimit;
    if(m_currentID > rowLimit) {
        stopDrawItem = m_currentID;
    }
    for(int row = startDrawItem; row <m_currentID; row ++) {
        LCDLibrary::drawString(
                    m_app->getScreenData(),m_app->getScreenWidth(),m_app->getScreenHeight(),
                    (const unsigned char**)openGLletters,m_gameTittle[row],
                    0,currentRow  * m_app->getScreenHeight() / rowLimit  + (m_app->getScreenHeight() / rowLimit/2-13/2));
        currentRow ++;
    }
    //   print current item
    LCDLibrary::drawRect(
                m_app->getScreenData(),m_app->getScreenWidth(),m_app->getScreenHeight(),
                0,currentRow * m_app->getScreenHeight() / rowLimit,
                m_app->getScreenWidth(),m_app->getScreenHeight() / rowLimit,1,true);
    LCDLibrary::drawString(
                m_app->getScreenData(),m_app->getScreenWidth(),m_app->getScreenHeight(),
                (const unsigned char**)openGLletters,m_gameTittle[m_currentID],
                0,currentRow * m_app->getScreenHeight() / rowLimit + (m_app->getScreenHeight() / rowLimit/2-13/2),true);
    currentRow ++;
    //   print next items
    for(int row = m_currentID + 1; row <= stopDrawItem; row ++) {
        LCDLibrary::drawString(
                    m_app->getScreenData(),m_app->getScreenWidth(),m_app->getScreenHeight(),
                    (const unsigned char**)openGLletters,m_gameTittle[row],
                    0,currentRow * m_app->getScreenHeight() / rowLimit  + (m_app->getScreenHeight() / rowLimit/2-13/2));
        currentRow++;
    }
}
void GameMenu::drawScrollBar() {
    // 00100
    // 11111
    // 10001
    // 10001
    // 10001
    // 11111
    // 00100
    LCDLibrary::drawLine(m_app->getScreenData(),m_app->getScreenWidth(),m_app->getScreenHeight(),
                         m_app->getScreenWidth()-4,0,
                         m_app->getScreenWidth()-4,m_app->getScreenHeight(),1);
    LCDLibrary::drawRect(m_app->getScreenData(),m_app->getScreenWidth(),m_app->getScreenHeight(),
                         m_app->getScreenWidth()-6,(m_currentID-GAME_MIN-1) * m_app->getScreenHeight()/(GAME_MAX - GAME_MIN - 1),
                         5,m_app->getScreenHeight()/(GAME_MAX - GAME_MIN-1),1,true);
}
