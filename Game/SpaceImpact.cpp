#include "SpaceImpact.h"
#include "GameMenu.h"
#include "ApplicationController.h"
#include "Button.h"
#include "LCDLibrary.h"
/* SPACESHIP_MOVING symbol 1,5 - 1 tick
    0000 0000 0010 0000
    0000 0000 0111 0000
    0000 0000 1111 1000
    0000 0000 0011 1110
    0000 0000 0111 1111
    0000 0000 0011 1110
    0000 0000 1111 1000
    0000 0000 0111 0000
    0000 0000 0010 0000
*/
/* SPACESHIP_MOVING symbol 2,4 - 2 tick
    0000 0000 0010 0000
    0000 0000 0111 0000
    0000 0000 1111 1000
    0000 0001 0011 1110
    0000 0110 0111 1111
    0000 0001 0011 1110
    0000 0000 1111 1000
    0000 0000 0111 0000
    0000 0000 0010 0000
*/
/* SPACESHIP_MOVING symbol 3 - 3 tick
    0000 0000 0010 0000
    0000 0000 0111 0000
    0000 0000 1111 1000
    0000 0011 0011 1110
    0000 1110 0111 1111
    0000 0011 0011 1110
    0000 0000 1111 1000
    0000 0000 0111 0000
    0000 0000 0010 0000
*/
const unsigned char shipSprite[][10][18] = {

    { // State Init
        {   0x00,0x20,
            0x00,0x70,
            0x00,0xF8,
            0x00,0x3E,
            0x00,0x7F,
            0x00,0x3E,
            0x00,0xF8,
            0x00,0x70,
            0x00,0x20,
        },
        {   0x00,0x20,
            0x00,0x70,
            0x00,0xF8,
            0x01,0x3E,
            0x06,0x7F,
            0x01,0x3E,
            0x00,0xF8,
            0x00,0x70,
            0x00,0x20,
        },
        {
            0x00,0x20,
            0x00,0x70,
            0x00,0xF8,
            0x03,0x3E,
            0x0E,0x7F,
            0x03,0x3E,
            0x00,0xF8,
            0x00,0x70,
            0x00,0x20,
        },
        {   0x00,0x20,
            0x00,0x70,
            0x00,0xF8,
            0x01,0x3E,
            0x06,0x7F,
            0x01,0x3E,
            0x00,0xF8,
            0x00,0x70,
            0x00,0x20,
        },
        {   0x00,0x20,
            0x00,0x70,
            0x00,0xF8,
            0x00,0x3E,
            0x00,0x7F,
            0x00,0x3E,
            0x00,0xF8,
            0x00,0x70,
            0x00,0x20,
        },
    },

    { // State Moving
        {   0x00,0x20,
            0x00,0x70,
            0x00,0xF8,
            0x00,0x3E,
            0x00,0x7F,
            0x00,0x3E,
            0x00,0xF8,
            0x00,0x70,
            0x00,0x20,
        },
        {   0x00,0x20,
            0x00,0x70,
            0x00,0xF8,
            0x01,0x3E,
            0x06,0x7F,
            0x01,0x3E,
            0x00,0xF8,
            0x00,0x70,
            0x00,0x20,
        },
        {
            0x00,0x20,
            0x00,0x70,
            0x00,0xF8,
            0x03,0x3E,
            0x0E,0x7F,
            0x03,0x3E,
            0x00,0xF8,
            0x00,0x70,
            0x00,0x20,
        },
        {   0x00,0x20,
            0x00,0x70,
            0x00,0xF8,
            0x01,0x3E,
            0x06,0x7F,
            0x01,0x3E,
            0x00,0xF8,
            0x00,0x70,
            0x00,0x20,
        },
        {   0x00,0x20,
            0x00,0x70,
            0x00,0xF8,
            0x00,0x3E,
            0x00,0x7F,
            0x00,0x3E,
            0x00,0xF8,
            0x00,0x70,
            0x00,0x20,
        },
    },
};

/*
    1111 1100
    0001 1010
    0000 1111
    0001 1010
    1111 1100
*/
const unsigned char alien1[] = {
    0xFC,
    0x1A,
    0x0F,
    0x1A,
    0xFC,
};
/*
    0000 1110
    0000 0100
    0000 0100
    0011 1101
    1111 1111
    0011 1101
    0000 0100
    0000 0100
    0000 1110
*/
const unsigned char alien2[] = {
    0x0E,
    0x04,
    0x04,
    0x3D,
    0xFF,
    0x3D,
    0x04,
    0x04,
    0x0E,
};
/*
 * 0000 0000
 * 0000 0010
 * 0100 0000
 * 0001 1000
 * 0001 1000
 * 1000 0001
 * 0000 0000
 * 0000 0000
*/
/*
 * 0000 1011
 * 0110 0011
 * 0110 0000
 * 0000 1000
 * 0001 1100
 * 1000 1001
 * 0000 0011
 * 0110 1000
*/
const unsigned char explosionSpite[][8] = {
    {
        0x00,
        0x02,
        0x40,
        0x18,
        0x18,
        0x81,
        0x00,
        0x00,
    },
    {
        0x2B,
        0x63,
        0x60,
        0x08,
        0x1C,
        0x89,
        0x03,
        0x58
    },
};

SpaceImpact::SpaceImpact(GameMenu* gameMenu, int gameID) :
    GameItem (gameMenu, gameID) {
    m_overlay = Rect(0,13,
                     m_gameMenu->app()->getScreenWidth(),
                     m_gameMenu->app()->getScreenHeight() - 13);
    m_dirX = 0;
    m_dirY = 0;
    m_newBullet = false;
    m_spaceShip.x = 0;
    m_spaceShip.y = m_gameMenu->app()->getScreenHeight() / 2 - m_overlay.y;
    m_spaceShip.width = 11;
    m_spaceShip.height = 7;
    m_tick = 0;
    int shipMovingTimeSlot[] = {1,2,3,2,1};
    m_spaceShip.setSpiteTimeSlot(SPACESHIP_MOVING,shipMovingTimeSlot,sizeof (shipMovingTimeSlot) / sizeof (shipMovingTimeSlot[0]));
}

SpaceImpact::~SpaceImpact() {

}

void SpaceImpact::loop() {
    clearDisplay();
    // check input
    int dirX = 0;
    int dirY = 0;
    m_gameMenu->app()->checkAllButtonState();
    if(m_gameMenu->app()->buttonState(BUTTON_ID::BTN_UP) != BUTTON_STATE::BUTTON_NOMAL) {
        dirY = -1;
    }
    if(m_gameMenu->app()->buttonState(BUTTON_ID::BTN_DOWN) != BUTTON_STATE::BUTTON_NOMAL) {
        dirY = 1;
    }
    if(m_gameMenu->app()->buttonState(BUTTON_ID::BTN_LEFT) != BUTTON_STATE::BUTTON_NOMAL) {
        dirX = -1;
    }
    if(m_gameMenu->app()->buttonState(BUTTON_ID::BTN_RIGHT) != BUTTON_STATE::BUTTON_NOMAL) {
        dirX = 1;
    }

    if(m_gameMenu->app()->buttonState(BUTTON_ID::BTN_ENTER) == BUTTON_STATE::BUTTON_PRESS) {
        m_newBullet = true;
    }
    updateMove(dirX, dirY);
    updateAliens();
    updateBullets();
    updateSpaceShip();
    drawSpaceShip();
    drawBullets();
    drawAliens();
    drawOverlay();
    m_tick++;
    m_tick %= 30;
    if(m_gameMenu->app()->buttonState(BUTTON_ID::BTN_BACK) == BUTTON_STATE::BUTTON_PRESS) {
        m_gameMenu->setMachineState(GAME_STATE::GAME_EXIT);
    }
}
void SpaceImpact::clearDisplay() {
    LCDLibrary::clear(
                m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),0x00);
}
void SpaceImpact::updateMove(int x, int y) {
    m_dirX = x;
    m_dirY = y;
}
void SpaceImpact::updateAliens() {
    if(m_tick == 0) {
        if(random()%2){
            Alien newAli(m_overlay.width-5,random()% m_overlay.height,8,5,0);
            int destructionTimeSlot[] = {5,5};
            newAli.setSpiteTimeSlot(ALIEN_STATE::ALIEN_HIT,destructionTimeSlot,sizeof (destructionTimeSlot) / sizeof (destructionTimeSlot[0]));
            m_aliens.push_back(newAli);
        } else {
            Alien newAli(m_overlay.width-5,random()% m_overlay.height,8,9,1);
            int destructionTimeSlot[] = {5,5};
            newAli.setSpiteTimeSlot(ALIEN_STATE::ALIEN_HIT,destructionTimeSlot,sizeof (destructionTimeSlot) / sizeof (destructionTimeSlot[0]));
            m_aliens.push_back(newAli);
        }
    }
    for(int i = 0; i< m_aliens.size(); i++) {
        switch (m_aliens[i].state()) {
        case ALIEN_STATE::ALIEN_INIT: {
            m_aliens[i].setState(ALIEN_STATE::ALIEN_TOWARD);
            break;
        }
        case ALIEN_STATE::ALIEN_TOWARD: {
            m_aliens[i].x --;
            if(m_aliens[i].x+m_aliens[i].width <= 0) m_aliens[i].setState(ALIEN_STATE::ALIEN_LOST);
            break;
        }
        case ALIEN_STATE::ALIEN_LOST: {
            m_aliens.erase(m_aliens.begin()+i);
            break;
        }
        case ALIEN_STATE::ALIEN_HIT: {
            m_aliens[i].increaseTick(1);
            if(m_aliens[i].tick() >= m_aliens[i].totalTime())
            m_aliens.erase(m_aliens.begin()+i);
            break;
        }
        }
    }
}
void SpaceImpact::updateBullets() {
    if(m_newBullet) {
        m_newBullet = false;
        m_bullets.push_back(Bullet(m_spaceShip.x + m_spaceShip.width+2,m_spaceShip.center().y+1));
    }
    for(int i = 0; i< m_bullets.size(); i++) {
        switch (m_bullets[i].state()) {
        case BULLET_STATE::BULLET_INIT: {
            m_bullets[i].setState(BULLET_STATE::BULLET_FIRING);
            break;
        }
        case BULLET_STATE::BULLET_FIRING: {
            m_bullets[i].x ++;
            if(m_bullets[i].x >= m_overlay.width) m_bullets[i].setState(BULLET_STATE::BULLET_HIT);
            else {
                for (int alien = 0; alien < m_aliens.size(); alien ++) {
                    if(m_bullets[i].collide(m_aliens[alien])) {
                        m_bullets[i].setState(BULLET_STATE::BULLET_HIT);
                        m_aliens[alien].setState(ALIEN_STATE::ALIEN_HIT);
                    }
                }
            }
            break;
        }
        case BULLET_STATE::BULLET_HIT: {
            m_bullets.erase(m_bullets.begin()+i);
            break;
        }
        }
    }
}
void SpaceImpact::updateSpaceShip() {
    m_spaceShip.x += m_dirX;
    m_spaceShip.y += m_dirY;
    m_spaceShip.increaseTick(1);
    switch (m_spaceShip.state()) {
    case SPACESHIP_INIT:
        m_spaceShip.setState( SPACESHIP_MOVING );
        break;
    case SPACESHIP_MOVING:
        if(m_spaceShip.x<0) m_spaceShip.x = 0;
        if(m_spaceShip.x + m_spaceShip.width >= m_overlay.width-2) m_spaceShip.x = m_overlay.width - m_spaceShip.width-2;
        if(m_spaceShip.y<0) m_spaceShip.y = 0;
        if(m_spaceShip.y + m_spaceShip.height >= m_overlay.height-2) m_spaceShip.y = m_overlay.height - m_spaceShip.height-2;
        break;
    case SPACESHIP_HIT:
        break;
    }
}
void SpaceImpact::drawBullets() {
    for(int i = 0; i< m_bullets.size(); i++) {
        LCDLibrary::drawRect(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                 m_bullets[i].x + m_overlay.x, m_bullets[i].y + m_overlay.y,
                 m_bullets[i].width,m_bullets[i].height);
    }
}
void SpaceImpact::drawSpaceShip() {
    switch (m_spaceShip.state()) {
    case SPACESHIP_INIT:

        break;
    case SPACESHIP_MOVING:
    {
    }
        break;
    case SPACESHIP_HIT:
        break;
    }
    LCDLibrary::drawObject(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                           (unsigned char*)shipSprite[m_spaceShip.state()][m_spaceShip.spiteID()],16,9,
                           m_spaceShip.x + m_overlay.x+1,m_spaceShip.y+m_overlay.y+1);
}
void SpaceImpact::drawAliens() {


    for(int i = 0; i< m_aliens.size(); i++) {
        switch (m_aliens[i].state()) {
        case ALIEN_STATE::ALIEN_INIT: {

            break;
        }
        case ALIEN_STATE::ALIEN_TOWARD: {
            LCDLibrary::drawObject(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                        m_aliens[i].type() == 0?(unsigned char*)alien1:(unsigned char*)alien2,m_aliens[i].width,m_aliens[i].height,
                        m_aliens[i].x + m_overlay.x + 1, m_aliens[i].y + m_overlay.y + 1);
            break;
        }
        case ALIEN_STATE::ALIEN_HIT: {
//            printf("m_aliens[%d] tick[%d/%d] spiteID[%d]\r\n",
//                   i, m_aliens[i].tick(),m_aliens[i].totalTime(),m_aliens[i].spiteID());
            LCDLibrary::drawObject(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                        (unsigned char*)explosionSpite[m_aliens[i].spiteID()],8,8,
                        m_aliens[i].x + m_overlay.x + 1, m_aliens[i].y + m_overlay.y + 1);
            break;
        }
        }

    }
}
void SpaceImpact::drawOverlay() {
    LCDLibrary::drawRect(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                         m_overlay.x,m_overlay.y,
                         m_overlay.width,m_overlay.height);
}
