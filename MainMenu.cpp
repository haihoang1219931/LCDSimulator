#include "MainMenu.h"
#include "ApplicationController.h"
#include "LCDLibrary.h"
MainMenu::MainMenu(ApplicationController* app)
{
    m_app = app;
    m_currentID = MENU_MESSAGE;
}
void MainMenu::loop() {
    // check input
    if(m_app->isButtonPressed(BUTTON_ID::BTN_LEFT)){
        if(m_currentID + 1 < MENU_ID::MENU_MAX) {
            m_currentID ++;
        }
    } else if(m_app->isButtonPressed(BUTTON_ID::BTN_RIGHT)){
        if(m_currentID - 1 > MENU_ID::MENU_MIN) {
            m_currentID --;
        }
    }
    
    // draw main
    switch ((MENU_ID)m_currentID) {
    case MENU_MESSAGE:
    {
        LCDLibrary::drawString(
                    m_app->getScreenData(),m_app->getScreenWidth(),m_app->getScreenHeight(),
                    (const unsigned char**)fonts58,"MESSAGE",
                    m_app->getScreenWidth() / 2 - strlen("MESSAGE")*9/2 ,3);
    }
        break;
    case MENU_CALL:
        LCDLibrary::drawString(
                    m_app->getScreenData(),m_app->getScreenWidth(),m_app->getScreenHeight(),
                    (const unsigned char**)fonts58,"CALL",
                    m_app->getScreenWidth() / 2 - strlen("CALL")*9/2 ,3);
        break;
    case MENU_GAME:
        LCDLibrary::drawString(
                    m_app->getScreenData(),m_app->getScreenWidth(),m_app->getScreenHeight(),
                    (const unsigned char**)fonts58,"GAME",
                    m_app->getScreenWidth() / 2 - strlen("GAME")*9/2 ,3);
        break;
    }

    // draw navigation left button
//    {
//        unsigned char object[200] = {
//            000,000,000,000,000,000,000,000,000,255,
//            000,000,000,000,000,000,000,000,255,255,
//            000,000,000,000,000,000,000,255,255,255,
//            000,000,000,000,000,000,255,255,255,255,
//            000,000,000,000,000,255,255,255,255,255,
//            000,000,000,000,255,255,255,255,255,255,
//            000,000,000,255,255,255,255,255,255,255,
//            000,000,255,255,255,255,255,255,255,255,
//            000,255,255,255,255,255,255,255,255,255,
//            255,255,255,255,255,255,255,255,255,255,
//            255,255,255,255,255,255,255,255,255,255,
//            000,255,255,255,255,255,255,255,255,255,
//            000,000,255,255,255,255,255,255,255,255,
//            000,000,000,255,255,255,255,255,255,255,
//            000,000,000,000,255,255,255,255,255,255,
//            000,000,000,000,000,255,255,255,255,255,
//            000,000,000,000,000,000,255,255,255,255,
//            000,000,000,000,000,000,000,255,255,255,
//            000,000,000,000,000,000,000,000,255,255,
//            000,000,000,000,000,000,000,000,000,255,
//        };

//        LCDLibrary::drawObject(m_app->getScreenData(),m_app->getScreenWidth(),m_app->getScreenHeight(),
//                               object,10,20,10,m_app->getScreenHeight()/2 - 20/2);
//    }

    // draw navigation right button
//    {
//        unsigned char object[200] = {
//            255,000,000,000,000,000,000,000,000,000,
//            255,255,000,000,000,000,000,000,000,000,
//            255,255,255,000,000,000,000,000,000,000,
//            255,255,255,255,000,000,000,000,000,000,
//            255,255,255,255,255,000,000,000,000,000,
//            255,255,255,255,255,255,000,000,000,000,
//            255,255,255,255,255,255,255,000,000,000,
//            255,255,255,255,255,255,255,255,000,000,
//            255,255,255,255,255,255,255,255,255,000,
//            255,255,255,255,255,255,255,255,255,255,
//            255,255,255,255,255,255,255,255,255,255,
//            255,255,255,255,255,255,255,255,255,000,
//            255,255,255,255,255,255,255,255,000,000,
//            255,255,255,255,255,255,255,000,000,000,
//            255,255,255,255,255,255,000,000,000,000,
//            255,255,255,255,255,000,000,000,000,000,
//            255,255,255,255,000,000,000,000,000,000,
//            255,255,255,000,000,000,000,000,000,000,
//            255,255,000,000,000,000,000,000,000,000,
//            255,000,000,000,000,000,000,000,000,000,

//        };

//        LCDLibrary::drawObject(m_app->getScreenData(),m_app->getScreenWidth(),m_app->getScreenHeight(),
//                               object,10,20,m_app->getScreenWidth()-10-10,m_app->getScreenHeight()/2 - 20/2);
//    }


}

void MainMenu::draw() {

}
