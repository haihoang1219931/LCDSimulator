#include "Snake.h"
#include "GameMenu.h"
#include "ApplicationController.h"
#include "Button.h"
#include "LCDLibrary.h"
#include <math.h>
Snake::Snake(GameMenu* gameMenu, int gameID) :
    GameItem (gameMenu, gameID) {
    m_score = 0;
    m_dirX = 1;
    m_dirY = 0;
    m_bait.x = 100;
    m_bait.y = 32;

    for(int i=0; i< 10; i++)
        m_body.push_back(Point(i,14));

    m_baitState = BAIT_STATE::BAIT_NO_CONTACT;
}
Snake::~Snake()
{

}

void Snake::loop() {
    clearDisplay();
    drawOverlay();
    // check input
    int dirX = m_dirX;
    int dirY = m_dirY;
    m_gameMenu->app()->checkAllButtonState();
    if(m_gameMenu->app()->buttonState(BUTTON_ID::BTN_UP) == BUTTON_STATE::BUTTON_PRESS) {
        dirX = 0; dirY = m_dirY == 0? -1: m_dirY;
    } else if(m_gameMenu->app()->buttonState(BUTTON_ID::BTN_DOWN) == BUTTON_STATE::BUTTON_PRESS) {
        dirX = 0; dirY = m_dirY == 0? 1: m_dirY;
    } else if(m_gameMenu->app()->buttonState(BUTTON_ID::BTN_LEFT) == BUTTON_STATE::BUTTON_PRESS) {
        dirX = m_dirX == 0? -1: m_dirX; dirY = 0;
    } else if(m_gameMenu->app()->buttonState(BUTTON_ID::BTN_RIGHT) == BUTTON_STATE::BUTTON_PRESS) {
        dirX = m_dirX == 0? 1: m_dirX; dirY = 0;
    }
    updateMove(dirX, dirY);
    updateBait();
    drawBait();
    drawBody();
    if(m_gameMenu->app()->buttonState(BUTTON_ID::BTN_BACK) == BUTTON_STATE::BUTTON_PRESS) {
        m_gameMenu->setMachineState(GAME_STATE::GAME_EXIT);
    }
}

void Snake::updateMove(int x, int y) {
    m_dirX = x;
    m_dirY = y;
    Point head = m_body[m_body.size()-1];
    head.x += m_dirX;
    head.y += m_dirY;
    if(head.x < 0) head.x = m_gameMenu->app()->getScreenWidth() - 1;
    else if(head.x >= m_gameMenu->app()->getScreenWidth() - 1) head.x = 0;
    if(head.y < 13) head.y = m_gameMenu->app()->getScreenHeight() - 1;
    else if(head.y >= m_gameMenu->app()->getScreenHeight() - 1) head.y = 13;
    m_body.push_back(head);
    m_body.erase(m_body.begin());
}

void Snake::updateBait() {
    Point head = m_body[m_body.size()-1];
    Point tail = m_body[0];
    if(m_baitState == BAIT_STATE::BAIT_NO_CONTACT) {
        if(m_bait.x == head.x && m_bait.y == head.y) {
            m_baitState = BAIT_STATE::BAIT_EATING;
            m_score ++;
        }
    } else if(m_baitState == BAIT_STATE::BAIT_EATING) {
        if(m_bait.x == tail.x && m_bait.y == tail.y) {
            m_baitState = BAIT_STATE::BAIT_APPEND;
        }
    } else if(m_baitState == BAIT_STATE::BAIT_APPEND) {
        m_body.insert(m_body.begin(),m_bait);
        m_baitState = BAIT_STATE::BAIT_NO_CONTACT;
        m_bait.x = 1+random()%(m_gameMenu->app()->getScreenWidth()-1);
        m_bait.y = 13+1+random()%(m_gameMenu->app()->getScreenHeight()-1-13);
    }
}

void Snake::drawBait() {
    LCDLibrary::drawPixel(
            m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
            1,m_bait.x,m_bait.y);
}
void Snake::drawBody() {
    for(int i=0; i< m_body.size(); i++) {
        LCDLibrary::drawPixel(
                m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                1,m_body[i].x,m_body[i].y);
        LCDLibrary::drawPixel(
                m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                1,m_body[i].x,m_body[i].y);
    }
}

void Snake::drawOverlay() {
    // draw score
    int thousand = m_score / 1000;
    int hundred = (m_score - thousand * 1000) / 100;
    int dozen = (m_score - thousand * 1000 - hundred * 100) / 10;
    int unit = m_score % 10;
    LCDLibrary::drawChar(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                         (const unsigned char**)openGLletters,thousand + '0',0,1);
    LCDLibrary::drawChar(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                         (const unsigned char**)openGLletters,hundred + '0',10,1);
    LCDLibrary::drawChar(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                         (const unsigned char**)openGLletters,dozen + '0',20,1);
    LCDLibrary::drawChar(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                         (const unsigned char**)openGLletters,unit + '0',30,1);

    // draw bound
    LCDLibrary::drawLine(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                         0,13,m_gameMenu->app()->getScreenWidth(),13,1);
}

void Snake::clearDisplay() {
    LCDLibrary::clear(
                m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),0x00);
}
