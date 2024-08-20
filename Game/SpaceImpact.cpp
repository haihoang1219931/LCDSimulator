#include "SpaceImpact.h"
#include "GameMenu.h"
#include "ApplicationController.h"
#include "Button.h"
#include "LCDLibrary.h"

// icon capture from this https://www.youtube.com/watch?v=tKobl50jrLk
const unsigned char shipSprite[][10][30] = {

    { // State Init
      // SPACESHIP_INIT symbol 1-5 tick
      {
          0x01,0x00,// 0000 0001 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x04,0x40,// 0000 0100 0100 0000
          0x01,0x00,// 0000 0001 0000 0000
          0x13,0x90,// 0001 0011 1001 0000
          0x07,0xC0,// 0000 0111 1100 0000
          0x13,0xF2,// 0001 0011 1111 0010
          0x01,0xF8,// 0000 0001 1111 1000
          0x13,0xF2,// 0001 0011 1111 0010
          0x07,0xC0,// 0000 0111 1100 0000
          0x13,0x90,// 0001 0011 1001 0000
          0x01,0x00,// 0000 0001 0000 0000
          0x04,0x40,// 0000 0100 0100 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x01,0x00,// 0000 0001 0000 0000
      },
      // SPACESHIP_INIT symbol 2-5 tick
      {
          0x00,0x00,// 0000 0000 0000 0000
          0x02,0x80,// 0000 0010 1000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x09,0x20,// 0000 1001 0010 0000
          0x03,0x80,// 0000 0011 1000 0000
          0x27,0xC4,// 0010 0111 1100 0100
          0x03,0xF0,// 0000 0011 1111 0000
          0x09,0xF9,// 0000 1001 1111 1001
          0x03,0xF0,// 0000 0011 1111 0000
          0x27,0xC4,// 0010 0111 1100 0100
          0x03,0x80,// 0000 0011 1000 0000
          0x09,0x20,// 0000 1001 0010 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x02,0x80,// 0000 0010 1000 0000
          0x00,0x00,// 0000 0000 0000 0000
      },
    },

    { // State Moving
      // SPACESHIP_MOVING symbol 1-1 tick
      {
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x80,// 0000 0000 1000 0000
          0x01,0xC0,// 0000 0001 1100 0000
          0x03,0xE0,// 0000 0011 1110 0000
          0x00,0xF8,// 0000 0000 1111 1000
          0x01,0xFC,// 0000 0001 1111 1100
          0x00,0xF8,// 0000 0000 1111 1000
          0x03,0xE0,// 0000 0011 1110 0000
          0x01,0xC0,// 0000 0001 1100 0000
          0x00,0x80,// 0000 0000 1000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
      },
      // SPACESHIP_MOVING symbol 2-2 tick
      {
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x80,// 0000 0000 1000 0000
          0x01,0xC0,// 0000 0001 1100 0000
          0x03,0xE0,// 0000 0011 1110 0000
          0x01,0xF8,// 0000 0001 1111 1000
          0x06,0xFC,// 0000 0110 1111 1100
          0x01,0xF8,// 0000 0001 1111 1000
          0x03,0xE0,// 0000 0011 1110 0000
          0x01,0xC0,// 0000 0001 1100 0000
          0x00,0x80,// 0000 0000 1000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
      },
      // SPACESHIP_MOVING symbol 3-3 tick
      {
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x80,// 0000 0000 1000 0000
          0x01,0xC0,// 0000 0001 1100 0000
          0x03,0xE0,// 0000 0011 1110 0000
          0x03,0xF8,// 0000 0011 1111 1000
          0x0E,0xFC,// 0000 1110 1111 1100
          0x03,0xF8,// 0000 0011 1111 1000
          0x03,0xE0,// 0000 0011 1110 0000
          0x01,0xC0,// 0000 0001 1100 0000
          0x00,0x80,// 0000 0000 1000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
      },
      // SPACESHIP_MOVING symbol 4-2 tick
      {
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x80,// 0000 0000 1000 0000
          0x01,0xC0,// 0000 0001 1100 0000
          0x03,0xE0,// 0000 0011 1110 0000
          0x01,0xF8,// 0000 0001 1111 1000
          0x06,0xFC,// 0000 0110 1111 1100
          0x01,0xF8,// 0000 0001 1111 1000
          0x03,0xE0,// 0000 0011 1110 0000
          0x01,0xC0,// 0000 0001 1100 0000
          0x00,0x80,// 0000 0000 1000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
      },
      // SPACESHIP_MOVING symbol 5-1 tick
      {
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x80,// 0000 0000 1000 0000
          0x01,0xC0,// 0000 0001 1100 0000
          0x03,0xE0,// 0000 0011 1110 0000
          0x00,0xF8,// 0000 0000 1111 1000
          0x01,0xFC,// 0000 0001 1111 1100
          0x00,0xF8,// 0000 0000 1111 1000
          0x03,0xE0,// 0000 0011 1110 0000
          0x01,0xC0,// 0000 0001 1100 0000
          0x00,0x80,// 0000 0000 1000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
      },
    },

    { // State Hit
      // SPACESHIP_HIT symbol 1-5 tick
      {
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000
          0x00,0x00,// 0000 0000 0000 0000

      },
    },
};

const unsigned char alien[][4][10] = {
    {
        // alien 8x7
        {
            0x08,// 0000 1000
            0x14,// 0001 0100
            0x68,// 0110 1000
            0xB4,// 1011 0100
            0x68,// 0110 1000
            0x14,// 0001 0100
            0x08,// 0000 1000
        },
        {
            0x08,// 0000 1000
            0x14,// 0001 0100
            0x68,// 0110 1000
            0xF4,// 1111 0100
            0x68,// 0110 1000
            0x14,// 0001 0100
            0x08,// 0000 1000
        }
    },
    {
        // alien 8x5
        {
            0x0F,// 0000 1111
            0x76,// 0111 0110
            0xFF,// 1111 1111
            0x76,// 0111 0110
            0x0F,// 0000 1111
        },
        // alien 8x5
        {
            0x0F,// 0000 1111
            0x76,// 0111 0110
            0xCF,// 1011 1111
            0x76,// 0111 0110
            0x0F,// 0000 1111
        }
    },
    {
        // alien 16x5
        {
            0x75,0x00, // 0111 0101 0000 0000
            0xEA,0x40, // 1110 1010 0100 0000
            0xD1,0x00, // 1101 0001 0000 0000
            0xEA,0x00, // 1110 1010 0000 0000
            0x74,0x80, // 0111 0100 1000 0000
        },
        {
            0x74,0x80, // 0111 0100 1000 0000
            0xEA,0x00, // 1110 1010 0000 0000
            0xD5,0x00, // 1101 0101 0000 0000
            0xEA,0x40, // 1110 1010 0100 0000
            0x75,0x00, // 0111 0101 0000 0000
        }
    },
    {
        // alien 8x7
        {
            0x18, // 00011000
            0x42, // 01000010
            0x18, // 00011000
            0xB5, // 10110101
            0x18, // 00011000
            0x42, // 01000010
            0x18, // 00011000
        },
        {
            0x18, // 00011000
            0x42, // 01000010
            0x18, // 00011000
            0xAD, // 10101101
            0x18, // 00011000
            0x42, // 01000010
            0x18, // 00011000
        }
    },
    {
        // alien 8x5
        {
            0x3b,
            0x5c,
            0xbb,
            0x5c,
            0x3b,
        },
        {
            0x3a,
            0x5c,
            0xba,
            0x5c,
            0x3a,
        }
    }
};

const unsigned char boss01[][4][72] = {
    {
        {// 'boss01, 20x24px
         0x03, 0xfe, 0x00, 0x07, 0xff, 0x00, 0x0d, 0xd5, 0x80, 0x1b, 0xf0, 0x40, 0x63, 0xe6, 0x40, 0x86,
         0xcb, 0x20, 0x87, 0xdf, 0x20, 0x85, 0x95, 0x20, 0x05, 0x5b, 0x20, 0x02, 0xa4, 0x20, 0x03, 0xe0,
         0x60, 0x01, 0xc0, 0xe0, 0x01, 0x81, 0xf0, 0x01, 0xc3, 0xf0, 0x01, 0x67, 0x90, 0x01, 0x23, 0x90,
         0x01, 0x27, 0x10, 0x01, 0x27, 0x30, 0x01, 0xec, 0x20, 0x00, 0x30, 0x40, 0x00, 0x00, 0x80, 0x23,
         0x01, 0x00, 0x1d, 0x8e, 0x00, 0x00, 0x70, 0x00,
        },
        {
            // 'boss01-01, 32x32px
        0x03, 0xfe, 0x00, 0x05, 0xc1, 0x00, 0x0d, 0xf4, 0x80, 0x0b, 0xf4, 0x40, 0x1a, 0xe7, 0x40, 0xde,
        0xcb, 0x20, 0x65, 0x95, 0x20, 0x04, 0x19, 0x20, 0x05, 0xca, 0x20, 0x03, 0xe4, 0x60, 0x03, 0xe0,
        0x60, 0x01, 0x80, 0xe0, 0x01, 0x81, 0x50, 0x01, 0x43, 0xd0, 0x01, 0x67, 0x90, 0x01, 0x27, 0x90,
        0x01, 0x27, 0x10, 0x01, 0x22, 0x20, 0x00, 0xfc, 0x20, 0x1c, 0x30, 0x40, 0x24, 0x00, 0x80, 0x02,
        0x03, 0x00, 0x01, 0x8e, 0x00, 0x00, 0xf0, 0x00
        },
    },
    {
        {// 'boss01, 32x32px
         0x03, 0xfe, 0x00, 0x07, 0xff, 0x00, 0x0d, 0xd5, 0x80, 0x1b, 0xf0, 0x40, 0x63, 0xe6, 0x40, 0x86,
         0xcb, 0x20, 0x87, 0xdf, 0x20, 0x85, 0x95, 0x20, 0x05, 0x5b, 0x20, 0x02, 0xa4, 0x20, 0x03, 0xe0,
         0x60, 0x01, 0xc0, 0xe0, 0x01, 0x81, 0xf0, 0x01, 0xc3, 0xf0, 0x01, 0x67, 0x90, 0x01, 0x23, 0x90,
         0x01, 0x27, 0x10, 0x01, 0x27, 0x30, 0x01, 0xec, 0x20, 0x00, 0x30, 0x40, 0x00, 0x00, 0x80, 0x23,
         0x01, 0x00, 0x1d, 0x8e, 0x00, 0x00, 0x70, 0x00,
        },
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        {
            // 'boss01-01, 32x32px
            0x03, 0xfe, 0x00, 0x05, 0xc1, 0x00, 0x0d, 0xf4, 0x80, 0x0b, 0xf4, 0x40, 0x1a, 0xe7, 0x40, 0xde,
            0xcb, 0x20, 0x65, 0x95, 0x20, 0x04, 0x19, 0x20, 0x05, 0xca, 0x20, 0x03, 0xe4, 0x60, 0x03, 0xe0,
            0x60, 0x01, 0x80, 0xe0, 0x01, 0x81, 0x50, 0x01, 0x43, 0xd0, 0x01, 0x67, 0x90, 0x01, 0x27, 0x90,
            0x01, 0x27, 0x10, 0x01, 0x22, 0x20, 0x00, 0xfc, 0x20, 0x1c, 0x30, 0x40, 0x24, 0x00, 0x80, 0x02,
            0x03, 0x00, 0x01, 0x8e, 0x00, 0x00, 0xf0, 0x00
        },
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
    },
};
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

const unsigned char heart[] = {
    0x36,// 0011 0110
    0x5F,// 0101 1111
    0x7F,// 0111 1111
    0x3E,// 0011 1110
    0x1C,// 0001 1100
    0x08,// 0000 1000
};

SpaceImpact::SpaceImpact(GameMenu* gameMenu, int gameID) :
    GameItem (gameMenu, gameID) {
    m_overlay = Rect(0,14,
                     m_gameMenu->app()->getScreenWidth(),
                     m_gameMenu->app()->getScreenHeight() - 14);
    m_invertBG = true;
    m_gameSpeed = 1;
    m_state = GAME_PLAY_STATE::GAME_PLAY_PLAYING;
    m_score = 0;
    m_life = 5;
    m_nukes = 0;
    m_newBullet = false;
    m_newBoss = false;
    m_tick = 0;
    int shipInitTimeSlot[] = {2,2};
    int shipMovingTimeSlot[] = {1,2,3,2,1};
    int shipHitTimeSlot[] = {5};
    m_spaceShip.setSpiteTimeSlot(SPACESHIP_INIT,shipInitTimeSlot,sizeof (shipInitTimeSlot) / sizeof (shipInitTimeSlot[0]));
    m_spaceShip.setSpiteTimeSlot(SPACESHIP_MOVING,shipMovingTimeSlot,sizeof (shipMovingTimeSlot) / sizeof (shipMovingTimeSlot[0]));
    m_spaceShip.setSpiteTimeSlot(SPACESHIP_HIT,shipHitTimeSlot,sizeof (shipHitTimeSlot) / sizeof (shipHitTimeSlot[0]));


}

SpaceImpact::~SpaceImpact() {

}

void SpaceImpact::loop() {
    switch (m_state) {
    case GAME_PLAY_STATE::GAME_PLAY_PLAYING:
        playGame();
        break;
    case GAME_PLAY_STATE::GAME_PLAY_SHOW_SCORE:
        showScore();
        break;
    case GAME_PLAY_STATE::GAME_PLAY_EXIT:
        exitGame();
        break;
    }
}

void SpaceImpact::playGame() {
    clearDisplay();
    // check input
    int dirX = 0;
    int dirY = 0;
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
    updateSpaceShip();
    updateBullets();
    drawSpaceShip();
    drawBullets();
    drawAliens();
    drawBoss();
    if(m_tick % m_gameSpeed == 0) {
        updateAliens();
        updateBoss();
    }
    drawOverlay();
    m_tick++;
//    if(m_tick % 60 == 0) m_invertBG = !m_invertBG;
//    printf("m_invertBG[%s]\r\n",m_invertBG?"true":"false");
    if(m_life<=0 ||
            m_gameMenu->app()->buttonState(BUTTON_ID::BTN_BACK) == BUTTON_STATE::BUTTON_PRESS) {
        setState(GAME_PLAY_STATE::GAME_PLAY_SHOW_SCORE);
    }
}
void SpaceImpact::showScore() {
    drawEndGameScores();
    if(m_gameMenu->app()->buttonState(BUTTON_ID::BTN_ENTER) == BUTTON_STATE::BUTTON_PRESS ||
            m_gameMenu->app()->buttonState(BUTTON_ID::BTN_BACK) == BUTTON_STATE::BUTTON_PRESS ) {
        setState(GAME_PLAY_STATE::GAME_PLAY_EXIT);
    }
}
void SpaceImpact::exitGame() {
    m_gameMenu->setMachineState(GAME_STATE::GAME_EXIT);
}

void SpaceImpact::clearDisplay() {
    LCDLibrary::clear(
                m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),m_invertBG);
}
Alien SpaceImpact::createAlien() {
    Alien m_tmpAlien;
    int newAliType = random()%5;

    // set alien type, size, timeslot
    switch (newAliType) {
    case 0:
    {
        int alien0TimeSlot[] = {10,10};
        m_tmpAlien.setType(0);
        m_tmpAlien.width = 8;
        m_tmpAlien.height = 7;
        m_tmpAlien.setSpiteTimeSlot(ALIEN_TOWARD,alien0TimeSlot,sizeof(alien0TimeSlot)/sizeof(alien0TimeSlot[0]));
    }
        break;
    case 1:
    {
        int alien1TimeSlot[] = {10,10};
        m_tmpAlien.setType(1);
        m_tmpAlien.width = 8;
        m_tmpAlien.height = 5;
        m_tmpAlien.setSpiteTimeSlot(ALIEN_TOWARD,alien1TimeSlot,sizeof(alien1TimeSlot)/sizeof(alien1TimeSlot[0]));
    }
        break;
    case 2:
    {
        int alien2TimeSlot[] = {10,10};
        m_tmpAlien.setType(2);
        m_tmpAlien.width = 16;
        m_tmpAlien.height = 5;
        m_tmpAlien.setSpiteTimeSlot(ALIEN_TOWARD,alien2TimeSlot,sizeof(alien2TimeSlot)/sizeof(alien2TimeSlot[0]));
    }
        break;
    case 3:
    {
        int alien3TimeSlot[] = {10,10};
        m_tmpAlien.setType(3);
        m_tmpAlien.width = 8;
        m_tmpAlien.height = 7;
        m_tmpAlien.setSpiteTimeSlot(ALIEN_TOWARD,alien3TimeSlot,sizeof(alien3TimeSlot)/sizeof(alien3TimeSlot[0]));
    }
        break;
    case 4:
    {
        int alien4TimeSlot[] = {10,10};
        m_tmpAlien.setType(4);
        m_tmpAlien.width = 8;
        m_tmpAlien.height = 5;
        m_tmpAlien.setSpiteTimeSlot(ALIEN_TOWARD,alien4TimeSlot,sizeof(alien4TimeSlot)/sizeof(alien4TimeSlot[0]));
    }
        break;
    }

    // set pos
    m_tmpAlien.x = m_overlay.width - 1 - m_tmpAlien.width/2;
    m_tmpAlien.y = m_tmpAlien.height/2 + random()%(m_overlay.height - m_tmpAlien.height);

    // set hit timeslot
    int alienhitTimeSlot[] = {5,5};
    m_tmpAlien.setSpiteTimeSlot(ALIEN_HIT,alienhitTimeSlot,sizeof(alienhitTimeSlot)/sizeof(alienhitTimeSlot[0]));
    return m_tmpAlien;
}
void SpaceImpact::updateMove(int x, int y) {
    m_spaceShip.setDirX(x);
    m_spaceShip.setDirY(y);
}
void SpaceImpact::updateBoss() {
    if(m_tick >= 30 && !m_newBoss) {
        m_newBoss = true;
        m_boss = Alien(m_overlay.width-5,m_overlay.height/2,24,24,0);
        int timeSlotMoving[] = {15,15};
        int timeSlotHit[] = {15,15,15,15};
        m_boss.setSpiteTimeSlot(ALIEN_STATE::ALIEN_INIT,timeSlotMoving,sizeof(timeSlotMoving) / sizeof(timeSlotMoving[0]));
        m_boss.setSpiteTimeSlot(ALIEN_STATE::ALIEN_TOWARD,timeSlotMoving,sizeof(timeSlotMoving) / sizeof(timeSlotMoving[0]));
        m_boss.setSpiteTimeSlot(ALIEN_STATE::ALIEN_HIT,timeSlotHit,sizeof(timeSlotHit) / sizeof(timeSlotHit[0]));
    }
    else if(m_newBoss) {
        switch (m_boss.state()) {
        case ALIEN_STATE::ALIEN_INIT:
        {
            if(m_boss.tick(m_boss.state())< m_boss.width/2+3){
                m_boss.setDirX(-1);
                m_boss.move();
            }
            else {
                m_boss.setState(ALIEN_STATE::ALIEN_TOWARD);
            }
        }
            break;
        case ALIEN_STATE::ALIEN_TOWARD:
        {
            m_boss.setDirX(0);
            if(m_boss.dirY() == 0 ) m_boss.setDirY(-1);
            m_boss.move();
            if(m_boss.y<m_boss.height/2+1) m_boss.setDirY(1);
            else if(m_boss.y> m_overlay.height - m_boss.height/2+1) m_boss.setDirY(-1);
        }
            break;
        case ALIEN_STATE::ALIEN_HIT:
        {
            m_boss.setDirX(0);
            if(m_boss.dirY() == 0 ) m_boss.setDirY(-1);
            m_boss.move();
            if(m_boss.y<m_boss.height/2+1) m_boss.setDirY(1);
            else if(m_boss.y> m_overlay.height - m_boss.height/2+1) m_boss.setDirY(-1);
            if(m_boss.tick(m_boss.state()) >= m_boss.totalTime(m_boss.state())) {
                m_boss.setState(ALIEN_STATE::ALIEN_TOWARD);
            }
        }
            break;
        }
        m_boss.increaseTick(m_boss.state(),1);
    }
}
void SpaceImpact::updateAliens() {
    if(m_tick % 30 == 0) {
        Alien newAli = createAlien();
        m_aliens.push_back(newAli);
    }
    for(int i = 0; i< m_aliens.size(); i++) {
        m_aliens[i].increaseTick(m_aliens[i].state(),1);
        switch (m_aliens[i].state()) {
        case ALIEN_STATE::ALIEN_INIT: {
            m_aliens[i].setState(ALIEN_STATE::ALIEN_TOWARD);
            break;
        }
        case ALIEN_STATE::ALIEN_TOWARD:
        {
            m_aliens[i].x --;
            if(m_aliens[i].x+m_aliens[i].width/2<1) m_aliens[i].setState(ALIEN_STATE::ALIEN_LOST);
            else if(m_aliens[i].collide(m_spaceShip)) {
                m_aliens[i].setState(ALIEN_STATE::ALIEN_HIT);
                m_score ++;
                if(m_spaceShip.state() != SPACESHIP_STATE::SPACESHIP_INIT)
                    m_spaceShip.setState(SPACESHIP_STATE::SPACESHIP_HIT);
            }
            break;
        }
        case ALIEN_STATE::ALIEN_LOST:
        {
            m_aliens.erase(m_aliens.begin()+i);
            break;
        }
        case ALIEN_STATE::ALIEN_HIT:
        {
            if(m_aliens[i].tick(m_aliens[i].state()) >= m_aliens[i].totalTime(m_aliens[i].state()))
                m_aliens.erase(m_aliens.begin()+i);
        }
            break;
        }

    }
}
void SpaceImpact::updateBullets() {
    if(m_newBullet) {
        m_newBullet = false;
        m_bullets.push_back(Bullet(m_spaceShip.x,m_spaceShip.y));
    }
    for(int i = 0; i< m_bullets.size(); i++) {
        switch (m_bullets[i].state()) {
        case BULLET_STATE::BULLET_INIT: {
            m_bullets[i].setState(BULLET_STATE::BULLET_FIRING);
            break;
        }
        case BULLET_STATE::BULLET_FIRING: {
            m_bullets[i].x ++;
            if(m_bullets[i].x >= m_overlay.width) m_bullets[i].setState(BULLET_STATE::BULLET_LOST);
            else {
                // check aliens hit
                for (int alien = 0; alien < m_aliens.size(); alien ++) {
                    if(m_aliens[alien].state() != ALIEN_STATE::ALIEN_HIT
                            && m_bullets[i].collide(m_aliens[alien])) {
                        m_bullets[i].setState(BULLET_STATE::BULLET_HIT);
                        m_aliens[alien].setState(ALIEN_STATE::ALIEN_HIT);
                    }
                }

                // check boss hit
                if(m_newBoss) {
                    if(m_bullets[i].state() != BULLET_HIT && m_bullets[i].collide(m_boss)){
                        m_bullets[i].setState(BULLET_STATE::BULLET_HIT);
                        m_boss.addHit(1);
                        m_boss.setState(ALIEN_STATE::ALIEN_HIT);
                    }
                }
            }
            break;
        }

        case BULLET_STATE::BULLET_HIT: {
            m_score ++;
        }
        case BULLET_STATE::BULLET_LOST: {
            m_bullets.erase(m_bullets.begin()+i);
            break;
        }
        }
    }
}
void SpaceImpact::updateSpaceShip() {
    switch (m_spaceShip.state()) {
    case SPACESHIP_INIT:
    {
        if(m_spaceShip.tick(m_spaceShip.state()) == 1) {
            m_spaceShip.x = 16/2;
            m_spaceShip.y = m_gameMenu->app()->getScreenHeight() / 2 - m_overlay.y;
            m_spaceShip.width = 10;
            m_spaceShip.height = 9;
        } else if(m_spaceShip.tick(m_spaceShip.state()) == 30) {
            m_spaceShip.setState( SPACESHIP_INIT );
        }
    }
        break;
    case SPACESHIP_MOVING:
    {
        if(m_spaceShip.tick(m_spaceShip.state()) == 1) {
            m_spaceShip.width = 10;
            m_spaceShip.height = 9;
        }
    }
        break;
    case SPACESHIP_HIT:
    {
        m_life --;
        m_spaceShip.setState( SPACESHIP_INIT );
    }
        break;
    }
    m_spaceShip.move();
    if(m_spaceShip.x < m_spaceShip.width/2) m_spaceShip.x = m_spaceShip.width/2;
    if(m_spaceShip.x + m_spaceShip.width/2 > m_overlay.width-3) m_spaceShip.x = m_overlay.width - m_spaceShip.width/2-3;
    if(m_spaceShip.y < m_spaceShip.height/2) m_spaceShip.y = m_spaceShip.height/2;
    if(m_spaceShip.y + m_spaceShip.height/2 > m_overlay.height-3) m_spaceShip.y = m_overlay.height - m_spaceShip.height/2-3;
    m_spaceShip.increaseTick(m_spaceShip.state(), 1);
}
void SpaceImpact::drawBullets() {
    for(int i = 0; i< m_bullets.size(); i++) {
        LCDLibrary::drawRect(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                             m_bullets[i].x + m_overlay.x+1, m_bullets[i].y + m_overlay.y+1,
                             m_bullets[i].width,m_bullets[i].height,1,false,m_invertBG);
    }
}
void SpaceImpact::drawSpaceShip() {
    LCDLibrary::drawObject(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                           (unsigned char*)shipSprite[m_spaceShip.state()][m_spaceShip.spiteID(m_spaceShip.state())],16,15,
            m_spaceShip.x + m_overlay.x+1-16/2,m_spaceShip.y+m_overlay.y+1-15/2,m_invertBG);
}
void SpaceImpact::drawAliens() {
    for(int i = 0; i< m_aliens.size(); i++) {
        switch (m_aliens[i].state()) {
        case ALIEN_STATE::ALIEN_INIT:
        case ALIEN_STATE::ALIEN_TOWARD: {
            LCDLibrary::drawObject(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                                   (unsigned char*)alien[m_aliens[i].type()][m_aliens[i].spiteID(m_aliens[i].state())],m_aliens[i].width,m_aliens[i].height,
                    m_aliens[i].x + m_overlay.x + 1-m_aliens[i].width/2, m_aliens[i].y + m_overlay.y + 1-m_aliens[i].height/2,m_invertBG);
            break;
        }
        case ALIEN_STATE::ALIEN_HIT: {
            LCDLibrary::drawObject(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                                   (unsigned char*)explosionSpite[m_aliens[i].spiteID(m_aliens[i].state())],8,8,
                    m_aliens[i].x + m_overlay.x + 1-8/2, m_aliens[i].y + m_overlay.y + 1-8/2,m_invertBG);
            break;
        }
        }
    }
}

void SpaceImpact::drawBoss() {
    switch (m_boss.state()) {
    case ALIEN_STATE::ALIEN_INIT: {
    }
    case ALIEN_STATE::ALIEN_TOWARD: {
        LCDLibrary::drawObject(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                               m_boss.type() == 0?(unsigned char*)boss01[0][m_boss.spiteID(m_boss.state())]:(unsigned char*)boss01[0][m_boss.spiteID(m_boss.state())],
            m_boss.width,m_boss.height,m_boss.x + m_overlay.x + 1-m_boss.width/2, m_boss.y + m_overlay.y + 1-m_boss.height/2,m_invertBG);
        break;
    }
    case ALIEN_STATE::ALIEN_HIT: {
        LCDLibrary::drawObject(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                               m_boss.type() == 0?(unsigned char*)boss01[1][m_boss.spiteID(m_boss.state())]:(unsigned char*)boss01[1][m_boss.spiteID(m_boss.state())],
            m_boss.width,m_boss.height,m_boss.x + m_overlay.x + 1-m_boss.width/2, m_boss.y + m_overlay.y + 1-m_boss.height/2,m_invertBG);
        break;
    }
    }
}

void SpaceImpact::drawOverlay() {
    // draw header
    // draw life left
    for(int i=0;i< m_life; i++) {
        LCDLibrary::drawObject(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                               (unsigned char*)heart,8,6,
                               1+i*(8+1), 5,m_invertBG);
    }
    // draw nuke left
    // draw score
    char score[16];
    sprintf(score,"%05d",m_score);
    LCDLibrary::drawString(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                         (const unsigned char**)openGLletters,score,
                           m_gameMenu->app()->getScreenWidth() - 6*8,2,1,m_invertBG);
    // draw boundary
    LCDLibrary::drawRect(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                         m_overlay.x,m_overlay.y,
                         m_overlay.width,m_overlay.height,1,false,m_invertBG);
}

void SpaceImpact::drawEndGameScores() {
    clearDisplay();
    LCDLibrary::drawRect(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                         10,0,
                         m_gameMenu->app()->getScreenWidth()-20,m_gameMenu->app()->getScreenHeight(),1,false,m_invertBG);

    LCDLibrary::drawString(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                           (const unsigned char**)openGLletters,"Time",
                           m_gameMenu->app()->getScreenWidth() / 2 - strlen("Time")*9/2 ,0*m_gameMenu->app()->getScreenHeight()/4+3,1,m_invertBG);
    char time[16] ;
    sprintf(time,"%d",m_tick/30);
    LCDLibrary::drawString(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                           (const unsigned char**)openGLletters,time,
                           m_gameMenu->app()->getScreenWidth() / 2 - strlen(time)*9/2 ,1*m_gameMenu->app()->getScreenHeight()/4+3,1,m_invertBG);

    LCDLibrary::drawString(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                           (const unsigned char**)openGLletters,"Score",
                           m_gameMenu->app()->getScreenWidth() / 2 - strlen("Time")*9/2 ,2*m_gameMenu->app()->getScreenHeight()/4+3,1,m_invertBG);
    char score[16] ;
    sprintf(score,"%d",m_score);
    LCDLibrary::drawString(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                           (const unsigned char**)openGLletters,score,
                           m_gameMenu->app()->getScreenWidth() / 2 - strlen(score)*9/2 ,3*m_gameMenu->app()->getScreenHeight()/4+3,1,m_invertBG);
}
