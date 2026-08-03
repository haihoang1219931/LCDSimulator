#include "DinosaurRun.h"
#include "GameMenu.h"
#include "ApplicationController.h"
#include "Button.h"
#include "LCDLibrary.h"
#include <random>
#ifndef random
    #define random rand
#endif
#define DINOSAUR_MAX_SPRITE 32
#define DINOSAUR_SIZE 32*16
#define GROUND_LEVEL 300.0f
#define GRAVITY      0.6f
#define JUMP_FORCE   -6.0f
const unsigned char birdSpriteLeft[][DINOSAUR_MAX_SPRITE][DINOSAUR_SIZE] = {

    { // State int
      // BIRD symbol 2-5 tick
      {
          0x00,0x80,0x00, // 0000 0000 1000 0000 0000 0000
          0x00,0xC0,0x00, // 0000 0000 1100 0000 0000 0000
          0x00,0xE0,0x00, // 0000 0000 1110 0000 0000 0000
          0x06,0x70,0x00, // 0000 0110 0111 0000 0000 0000
          0x0E,0x78,0x00, // 0000 1110 0111 1000 0000 0000
          0x1F,0x7C,0x00, // 0001 1111 0111 1100 0000 0000
          0x3F,0x7E,0x00, // 0011 1111 0111 1110 0000 0000
          0x7F,0xFE,0x00, // 0111 1111 1111 1110 0000 0000
          0x01,0xFF,0x00, // 0000 0001 1111 1111 0000 0000
          0x00,0xFF,0xFF, // 0000 0000 1111 1111 1111 1111
          0x00,0x7F,0xF0, // 0000 0000 0111 1111 1111 0000
          0x00,0x3F,0xFC, // 0000 0000 0011 1111 1111 1100
          0x00,0x1F,0xE0, // 0000 0000 0001 1111 1110 0000
      },
      // BIRD symbol 3-5 tick
      {
          0x06,0x70,0x00, // 0000 0110 0000 0000 0000 0000
          0x0E,0x78,0x00, // 0000 1110 0000 0000 0000 0000
          0x1F,0x7C,0x00, // 0001 1111 0000 0000 0000 0000
          0x3F,0x7E,0x00, // 0011 1111 0000 0000 0000 0000
          0x7F,0xFE,0x00, // 0111 1111 1111 1110 0000 0000
          0x01,0xFF,0x00, // 0000 0001 1111 1111 0000 0000
          0x00,0xFF,0xFF, // 0000 0000 1111 1111 1111 1111
          0x00,0xFF,0xF0, // 0000 0000 1111 1111 1111 0000
          0x00,0xFF,0xFC, // 0000 0000 1111 1111 1111 1100
          0x00,0xFF,0xE0, // 0000 0000 1111 1111 1110 0000
          0x00,0xE0,0x00, // 0000 0000 1110 0000 0000 0000
          0x00,0xC0,0x00, // 0000 0000 1100 0000 0000 0000
          0x00,0x80,0x00, // 0000 0000 1000 0000 0000 0000
      },
    },
};
const unsigned char dinoSpriteLeft[][DINOSAUR_MAX_SPRITE][DINOSAUR_SIZE] = {

    { // State stand
      // DINO_LEFT_STAND
      {
          0x01,0xFC, // 0000 0001 1111 1100
          0x03,0x7F, // 0000 0011 0111 1111
          0x03,0xFF, // 0000 0011 1111 1111
          0x03,0xF0, // 0000 0011 1111 0000
          0x43,0xFC, // 0100 0011 1111 1100
          0xC3,0xC0, // 1100 0011 1100 0000
          0xC7,0xC0, // 1100 0111 1100 0000
          0xFF,0xF0, // 1111 1111 1111 0000
          0xFF,0xD0, // 1111 1111 1101 0000
          0xFF,0xC0, // 1111 1111 1100 0000
          0x7F,0xC0, // 0111 1111 1100 0000
          0x3F,0xC0, // 0011 1111 1100 0000
          0x1F,0xC0, // 0001 1111 1100 0000
          0x0C,0x40, // 0000 1100 0100 0000
          0x04,0x40, // 0000 0100 0100 0000
          0x06,0x60  // 0000 0110 0110 0000
      },
    },
    { // State run go
      // DINO_LEFT_RUN_STAND symbol 1-2 tick
      {
          0x01,0xFC, // 0000 0001 1111 1100
          0x03,0x7F, // 0000 0011 0111 1111
          0x03,0xFF, // 0000 0011 1111 1111
          0x03,0xF0, // 0000 0011 1111 0000
          0x43,0xFC, // 0100 0011 1111 1100
          0xC3,0xE0, // 1100 0011 1110 0000
          0xC7,0xE0, // 1100 0111 1110 0000
          0xFF,0xF8, // 1111 1111 1111 1000
          0xFF,0xE8, // 1111 1111 1110 1000
          0xFF,0xE0, // 1111 1111 1110 0000
          0x7F,0xE0, // 0111 1111 1110 0000
          0x3F,0xE0, // 0011 1111 1110 0000
          0x0C,0xC0, // 0000 1100 1100 0000
          0x06,0x40, // 0000 0110 0100 0000
          0x00,0x40, // 0000 0000 0100 0000
          0x00,0x60  // 0000 0000 0110 0000
      },
      // DINO_LEFT_RUN_STAND symbol 2-2 tick
      {
          0x01,0xFC, // 0000 0001 1111 1100
          0x03,0x7F, // 0000 0011 0111 1111
          0x03,0xFF, // 0000 0011 1111 1111
          0x03,0xF0, // 0000 0011 1111 0000
          0x43,0xFC, // 0100 0011 1111 1100
          0xC3,0xE0, // 1100 0011 1110 0000
          0xC7,0xE0, // 1100 0111 1110 0000
          0xFF,0xF8, // 1111 1111 1111 1000
          0xFF,0xE8, // 1111 1111 1110 1000
          0xFF,0xE0, // 1111 1111 1110 0000
          0x7F,0xE0, // 0111 1111 1110 0000
          0x3F,0xC0, // 0011 1111 1100 0000
          0x0E,0x70, // 0000 1110 0111 0000
          0x0C,0x00, // 0000 1100 0000 0000
          0x08,0x00, // 0000 1000 0000 0000
          0x0C,0x00  // 0000 1100 0000 0000
      },
    },
    { // State jump go up
      // DINO_LEFT_STAND
      {
          0x01,0xFC, // 0000 0001 1111 1100
          0x03,0x7F, // 0000 0011 0111 1111
          0x03,0xFF, // 0000 0011 1111 1111
          0x03,0xF0, // 0000 0011 1111 0000
          0x43,0xFC, // 0100 0011 1111 1100
          0xC3,0xC0, // 1100 0011 1100 0000
          0xC7,0xC0, // 1100 0111 1100 0000
          0xFF,0xF0, // 1111 1111 1111 0000
          0xFF,0xD0, // 1111 1111 1101 0000
          0xFF,0xC0, // 1111 1111 1100 0000
          0x7F,0xC0, // 0111 1111 1100 0000
          0x3F,0xC0, // 0011 1111 1100 0000
          0x1F,0xC0, // 0001 1111 1100 0000
          0x0C,0x40, // 0000 1100 0100 0000
          0x04,0x40, // 0000 0100 0100 0000
          0x06,0x60  // 0000 0110 0110 0000
      },
    },
    { // State duck go
      // DINO_LEFT_RUN_DUCK symbol 1-1 tick
      {
          0x60,0xFE,0x7E, // 0110 0001 1111 1110 0111 1110
          0x3B,0xFF,0xDF, // 0011 1011 1111 1111 1101 1111
          0x1F,0xFF,0xFF, // 0001 1111 1111 1111 1111 1111
          0x0F,0xFF,0xF0, // 0000 1111 1111 1111 1111 0000
          0x07,0xFF,0x3E, // 0000 0111 1111 1111 0011 1110
          0x03,0xFE,0x00, // 0000 0011 1111 1110 0000 0000
          0x01,0xFC,0x00, // 0000 0001 1111 1100 0000 0000
          0x00,0xCC,0x00, // 0000 0000 1100 1100 0000 0000
          0x00,0x64,0x00, // 0000 0000 0110 0100 0000 0000
          0x00,0x04,0x00, // 0000 0000 0000 0100 0000 0000
          0x00,0x06,0x00  // 0000 0000 0000 0110 0000 0000
      },
      // DINO_LEFT_RUN_DUCK symbol 2-2 tick
      {
          0x60,0xFE,0x7E, // 0110 0001 1111 1110 0111 1110
          0x3B,0xFF,0xDF, // 0011 1011 1111 1111 1101 1111
          0x1F,0xFF,0xFF, // 0001 1111 1111 1111 1111 1111
          0x0F,0xFF,0xF0, // 0000 1111 1111 1111 1111 0000
          0x07,0xFF,0x3E, // 0000 0111 1111 1111 0011 1110
          0x03,0xFE,0x00, // 0000 0011 1111 1110 0000 0000
          0x01,0xFC,0x00, // 0000 0001 1111 1100 0000 0000
          0x00,0xCC,0x00, // 0000 0000 1100 1100 0000 0000
          0x00,0x46,0x00, // 0000 0000 0100 0110 0000 0000
          0x00,0x40,0x00, // 0000 0000 0100 0000 0000 0000
          0x00,0x60,0x00  // 0000 0000 0110 0000 0000 0000
      },
    },
};

const unsigned char starType1Sprite[][DINOSAUR_MAX_SPRITE][DINOSAUR_SIZE] = {
    { // STATE_GO
      {
          0x10, // 0001 0000
          0x54, // 0101 0100
          0x10, // 0001 0000
          0xFE, // 1111 1110
          0x10, // 0001 0000
          0x54, // 0101 0100
          0x10, // 0001 0000
      },
    },
};

const unsigned char starType2Sprite[][DINOSAUR_MAX_SPRITE][DINOSAUR_SIZE] = {
    { // STATE_GO
      {
          0x10, // 0001 0000
          0x10, // 0001 0000
          0x7C, // 0111 1100
          0x10, // 0001 0000
          0x10, // 0001 0000
      },
    },
};

const unsigned char treeType1Sprite[][DINOSAUR_MAX_SPRITE][DINOSAUR_SIZE] = {
    { // STATE_GO
      {
          0x01,0x80, // 0000 0001 1000 0000
          0x03,0xC4, // 0000 0011 1100 0100
          0x03,0xCE, // 0000 0011 1100 1110
          0x03,0xCE, // 0000 0011 1100 1110
          0x03,0xFE, // 0000 0011 1111 1110
          0x43,0xFC, // 0100 0011 1111 1100
          0xE3,0xF8, // 1110 0011 1111 1000
          0xE3,0xC0, // 1110 0011 1100 0000
          0xE3,0xC0, // 1110 0011 1100 0000
          0x7F,0xC0, // 0111 1111 1100 0000
          0x3F,0xC0, // 0011 1111 1100 0000
          0x1F,0xC0, // 0001 1111 1100 0000
          0x03,0xC0, // 0000 0011 1100 0000
          0x03,0xC0, // 0000 0011 1100 0000
          0x03,0xC0, // 0000 0011 1100 0000
          0x03,0xC0, // 0000 0011 1100 0000
      },
    },
};

const unsigned char treeType2Sprite[][DINOSAUR_MAX_SPRITE][DINOSAUR_SIZE] = {
    { // STATE_GO
      {
          0x01,0x80, // 0000 0001 1000 0000
          0x43,0xC0, // 0100 0011 1100 0000
          0xE3,0xC0, // 1110 0011 1100 0000
          0xE3,0xC0, // 1110 0011 1100 0000
          0xFF,0xC0, // 1111 1111 1100 0000
          0x7F,0xC2, // 0111 1111 1100 0010
          0x3F,0xC7, // 0011 1111 1100 0111
          0x03,0xC7, // 0000 0011 1100 0111
          0x03,0xC7, // 0000 0011 1100 0111
          0x03,0xC7, // 0000 0011 1100 0111
          0x03,0xFE, // 0000 0011 1111 1110
          0x03,0xFC, // 0000 0011 1111 1100
          0x03,0xC0, // 0000 0011 1100 0000
          0x03,0xC0, // 0000 0011 1100 0000
          0x03,0xC0, // 0000 0011 1100 0000
          0x03,0xC0, // 0000 0011 1100 0000
      },
    },
};
const unsigned char cloudSprite[][DINOSAUR_MAX_SPRITE][DINOSAUR_SIZE] = {
    {
      {
          0x00,0x70,0x00, // 0000 0000 0111 0000 0000 0000
          0x00,0x88,0x00, // 0000 0000 1000 1000 0000 0000
          0x07,0x04,0x60, // 0000 0111 0000 0100 0110 0000
          0x18,0x03,0x98, // 0001 1000 0000 0011 1001 1000
          0x60,0x00,0x06, // 0110 0000 0000 0000 0000 0110
          0x80,0x00,0x01, // 1000 0000 0000 0000 0000 0001
          0x1F,0xFF,0xFE, // 0001 1111 1111 1111 1111 1110
      },
    },
};

const unsigned char moonSprite[][DINOSAUR_MAX_SPRITE][DINOSAUR_SIZE] = {
    {
      {
          0xC0,0x00, // 1100 0000 0000 0000
          0x70,0x00, // 0111 0000 0000 0000
          0x38,0x00, // 0011 1000 0000 0000
          0x1E,0x00, // 0001 1110 0000 0000
          0x0F,0x80, // 0000 1111 1000 0000
          0x07,0xC0, // 0000 0111 1100 0000
          0x07,0xE0, // 0000 0111 1110 0000
          0x07,0xE0, // 0000 0111 1110 0000
          0x07,0xE0, // 0000 0111 1110 0000
          0x07,0xE0, // 0000 0111 1110 0000
          0x07,0xE0, // 0000 0111 1110 0000
          0x07,0xC0, // 0000 0111 1100 0000
          0x0F,0x80, // 0000 1111 1000 0000
          0x1E,0x00, // 0001 1110 0000 0000
          0x38,0x00, // 0011 1000 0000 0000
          0x70,0x00, // 0111 0000 0000 0000
          0xC0,0x00, // 1100 0000 0000 0000
      },
    },
};
DinosaurRun::DinosaurRun(GameMenu* gameMenu, int gameID):
    GameItem (gameMenu, gameID)
{
    int dinoRunTimeSlot[] = {5,5};
    int noAnimateTimeSlot[] = {5};
    m_dino[GAME_PLAYER1].setSpiteTimeSlot(DINO_STAND,noAnimateTimeSlot,sizeof (noAnimateTimeSlot) / sizeof (noAnimateTimeSlot[0]));
    m_dino[GAME_PLAYER1].setSpiteTimeSlot(DINO_RUN_GO,dinoRunTimeSlot,sizeof (dinoRunTimeSlot) / sizeof (dinoRunTimeSlot[0]));
    m_dino[GAME_PLAYER1].setSpiteTimeSlot(DINO_JUMP_GO_UP,noAnimateTimeSlot,sizeof (noAnimateTimeSlot) / sizeof (noAnimateTimeSlot[0]));
    m_dino[GAME_PLAYER1].setSpiteTimeSlot(DINO_JUMP_GO_DOWN,noAnimateTimeSlot,sizeof (noAnimateTimeSlot) / sizeof (noAnimateTimeSlot[0]));
    m_dino[GAME_PLAYER1].setSpiteTimeSlot(DINO_DUCK_GO,dinoRunTimeSlot,sizeof (dinoRunTimeSlot) / sizeof (dinoRunTimeSlot[0]));
    m_dino[GAME_PLAYER1].setEnable(true);
    m_dino[GAME_PLAYER2].setEnable(false);
    m_dino[GAME_PLAYER1].setState(DINO_STAND);
    m_dino[GAME_PLAYER2].setState(DINO_STAND);
    for(int starID = 0; starID < 2; starID++) {
        m_stars[starID].setState(SKY_OBJECT_INIT);
        m_stars[starID].setSpiteTimeSlot(SKY_OBJECT_GO,noAnimateTimeSlot,sizeof (noAnimateTimeSlot) / sizeof (noAnimateTimeSlot[0]));
    }
    for(int cloudID = 0; cloudID < 2; cloudID++) {
        m_clouds[cloudID].setState(SKY_OBJECT_INIT);
        m_clouds[cloudID].setSpiteTimeSlot(SKY_OBJECT_GO,noAnimateTimeSlot,sizeof (noAnimateTimeSlot) / sizeof (noAnimateTimeSlot[0]));
    }
    m_moon.setState(SKY_OBJECT_INIT);
    m_moon.setSpiteTimeSlot(SKY_OBJECT_GO,noAnimateTimeSlot,sizeof (noAnimateTimeSlot) / sizeof (noAnimateTimeSlot[0]));

    for(int treeID = 0; treeID < MAX_NUM_TREE; treeID++) {
        m_trees[treeID].setState(SKY_OBJECT_INIT);
        m_trees[treeID].setSpiteTimeSlot(SKY_OBJECT_GO,noAnimateTimeSlot,sizeof (noAnimateTimeSlot) / sizeof (noAnimateTimeSlot[0]));
    }
    m_state = GAME_PLAY_STATE::GAME_PLAY_PLAYING;
    m_invertBG = false;
    m_wait = 0;
}

DinosaurRun::~DinosaurRun()
{

}

void DinosaurRun::loop() {
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

void DinosaurRun::playGame()
{
    clearDisplay();
    // check input
    if(m_wait < 30) {
        m_wait++;
    }
    int state = m_dino[GAME_PLAYER1].state();
    bool buttonEnterPressed = m_gameMenu->app()->buttonState(BUTTON_ID::BTN_ENTER) != BUTTON_STATE::BUTTON_NOMAL;
    bool buttonUpPressed = m_gameMenu->app()->buttonState(BUTTON_ID::BTN_UP) != BUTTON_STATE::BUTTON_NOMAL;
    bool buttonDownPressed = m_gameMenu->app()->buttonState(BUTTON_ID::BTN_DOWN) != BUTTON_STATE::BUTTON_NOMAL;
    if(buttonEnterPressed || buttonUpPressed) {
        if(state == DINO_STAND || state == DINO_DIE) {
            if(m_gameMenu->app()->buttonState(BUTTON_ID::BTN_ENTER) != BUTTON_STATE::BUTTON_HOLD &&
                    m_wait >= 30) {
                updateMove(GAME_PLAYER1, DINO_RUN);
            }
        } else {
            if(state != DINO_JUMP && state != DINO_JUMP_GO_UP && state != DINO_JUMP_GO_DOWN)
                updateMove(GAME_PLAYER1, DINO_JUMP);
        }
    }
    if(buttonDownPressed) {
        if(state != DINO_DUCK && state != DINO_DUCK_GO &&
                state != DINO_JUMP && state != DINO_JUMP_GO_UP && state != DINO_JUMP_GO_DOWN)
            updateMove(GAME_PLAYER1, DINO_DUCK);
    } else {
        if(state == DINO_DUCK_GO)
            updateMove(GAME_PLAYER1, DINO_RUN);
    }
    if(m_gameMenu->app()->buttonState(BUTTON_ID::BTN_BACK) == BUTTON_STATE::BUTTON_PRESS) {
        setState(GAME_PLAY_STATE::GAME_PLAY_EXIT);
        return;
    }
//    printf("enter[%d] up[%d] down[%d] dino state[%d]\r\n",
//           m_gameMenu->app()->buttonState(BUTTON_ID::BTN_ENTER),buttonUpPressed,buttonDownPressed,state);
    updateDinos();
//    updateTrees();
//    updateBirds();
//    updateBackground();
    drawDinos();
//    drawBirds();
//    drawTree();
//    drawBackground();
}

void DinosaurRun::showScore()
{

}

void DinosaurRun::exitGame()
{
    m_gameMenu->setMachineState(GAME_STATE::GAME_EXIT);
}

void DinosaurRun::clearDisplay()
{
    LCDLibrary::clear(
        m_gameMenu->app()->getScreenData(),
                m_gameMenu->app()->getScreenWidth(),
                m_gameMenu->app()->getScreenHeight(),m_invertBG);
}

GameObject DinosaurRun::createBird()
{

}

GameObject DinosaurRun::createTree()
{

}

GameObject DinosaurRun::createCloud()
{

}

GameObject DinosaurRun::createStar()
{

}

GameObject DinosaurRun::createSun()
{

}

void DinosaurRun::updateMove(int dinoID, int state)
{
    m_dino[dinoID].setState(state);
}

void DinosaurRun::updateBirds()
{

}

void DinosaurRun::updateTrees()
{
    float nearestPos = 0;

    for(int treeID = 0; treeID < MAX_NUM_TREE; treeID++) {
        if(m_trees[treeID].state() == SKY_OBJECT_GO) {
            if(m_trees[treeID].x > nearestPos) nearestPos = m_trees[treeID].x;
        }
    }
    for(int treeID = 0; treeID < MAX_NUM_TREE; treeID++) {
        switch (m_trees[treeID].state()) {
        case SKY_OBJECT_INIT: {
            if(nearestPos > 10) continue;
            m_trees[treeID].setType(random() % 2);
            m_trees[treeID].setState(SKY_OBJECT_GO);
            m_trees[treeID].setDirX(-4);
            m_trees[treeID].x = 128 + random() % 10;
            m_trees[treeID].y = 64;
            if(m_trees[treeID].type() == TREE_TYPE_1) {
                m_trees[treeID].width = 16;
                m_trees[treeID].height = 16;
            } else if(m_trees[treeID].type() == TREE_TYPE_2) {
                m_trees[treeID].width = 16;
                m_trees[treeID].height = 16;
            }
        }
        case SKY_OBJECT_GO: {
            if(m_trees[treeID].x < - m_trees[treeID].width) {
                m_trees[treeID].setState(SKY_OBJECT_INIT);
            }
        }
            break;
        }
        m_trees[treeID].move();
        m_trees[treeID].increaseTick(m_trees[treeID].state(), 1);
    }
}

void DinosaurRun::updateDinos()
{
    for(int playerID = 0; playerID < 2; playerID++){
        if(!m_dino[playerID].enabled()) continue;
        switch (m_dino[playerID].state()) {
        case DINO_STAND: {
            m_dino[playerID].x = 5;
            m_dino[playerID].y = 64;
            m_dino[playerID].width = 16;
            m_dino[playerID].height = 16;
        }
             break;
        case DINO_RUN: {
            m_dino[playerID].x = 5;
            m_dino[playerID].y = 64;
            m_dino[playerID].width = 16;
            m_dino[playerID].height = 16;
            m_dino[playerID].setState(DINO_RUN_GO);
        }
        case DINO_RUN_GO: {
            if(isDinoHitted(playerID))
                m_dino[playerID].setState(DINO_DIE);
        }
             break;
        case DINO_JUMP: {
            m_dino[playerID].x = 5;
            m_dino[playerID].y = 64;
            m_dino[playerID].width = 16;
            m_dino[playerID].height = 16;
            m_dino[playerID].setDirY(JUMP_FORCE);
            m_dino[playerID].setState(DINO_JUMP_GO_UP);
        }
        case DINO_JUMP_GO_UP: {
            float dirY = m_dino[playerID].dirY();
            if(m_dino[playerID].dirY() > 0) {
                m_dino[playerID].setDirY(0);
                m_dino[playerID].setState(DINO_JUMP_GO_DOWN);
            } else {
                dirY+=GRAVITY;
                m_dino[playerID].setDirY(dirY);
            }
            if(isDinoHitted(playerID))
                m_dino[playerID].setState(DINO_DIE);
        }
             break;
        case DINO_JUMP_GO_DOWN: {
            float dirY = m_dino[playerID].dirY();
            if(m_dino[playerID].y >= 64) {
                m_dino[playerID].setDirY(0);
                m_dino[playerID].setState(DINO_RUN);
            }else {
                dirY+=GRAVITY;
                m_dino[playerID].setDirY(dirY);
            }
            if(isDinoHitted(playerID))
                m_dino[playerID].setState(DINO_DIE);
        }
             break;
        case DINO_DUCK: {
            m_dino[playerID].x = 1;
            m_dino[playerID].y = 69;
            m_dino[playerID].width = 24;
            m_dino[playerID].height = 11;
            m_dino[playerID].setDirY(0);
            m_dino[playerID].setState(DINO_DUCK_GO);
        }
        case DINO_DUCK_GO: {
            if(isDinoHitted(playerID))
                m_dino[playerID].setState(DINO_DIE);
        }
             break;
        }
        m_dino[playerID].move();
        m_dino[playerID].increaseTick(m_dino[playerID].state(), 1);
        printf("dino state[%d] y[%.02f] dirY[%.02f]\r\n",
               m_dino[playerID].state(),
               m_dino[playerID].y,
               m_dino[playerID].dirY());
    }
}

void DinosaurRun::updateBackground()
{
    // update stars
    for(int starID = 0; starID < 2; starID++) {
        switch (m_stars[starID].state()) {
        case SKY_OBJECT_INIT: {
            m_stars[starID].setType(random() % 2);
            m_stars[starID].setState(SKY_OBJECT_GO);
            m_stars[starID].setDirX(-1);
            m_stars[starID].x = 128 + random() % 100;
            m_stars[starID].y = random() % 20;
            if(m_stars[starID].type() == STAR_TYPE_1) {
                m_stars[starID].width = 8;
                m_stars[starID].height = 7;
            } else if(m_stars[starID].type() == STAR_TYPE_2) {
                m_stars[starID].width = 8;
                m_stars[starID].height = 5;
            }
        }
        case SKY_OBJECT_GO: {
            if(m_stars[starID].x < - m_stars[starID].width) {
                m_stars[starID].setState(SKY_OBJECT_INIT);
            }
        }
            break;
        }
        m_stars[starID].move();
        m_stars[starID].increaseTick(m_stars[starID].state(), 1);
    }

    // update clouds
    for(int starID = 0; starID < 2; starID++) {
        switch (m_clouds[starID].state()) {
        case SKY_OBJECT_INIT: {
            m_clouds[starID].setType(random() % 2);
            m_clouds[starID].setState(SKY_OBJECT_GO);
            m_clouds[starID].setDirX(-1);
            m_clouds[starID].x = 128 + random() % 100;
            m_clouds[starID].y = random() % 20;
            m_clouds[starID].width = 24;
            m_clouds[starID].height = 7;
        }
        case SKY_OBJECT_GO: {
            if(m_clouds[starID].x < - m_clouds[starID].width) {
                m_clouds[starID].setState(SKY_OBJECT_INIT);
            }
        }
            break;
        }
        m_clouds[starID].move();
        m_clouds[starID].increaseTick(m_clouds[starID].state(), 1);
    }

    // update moon
    switch (m_moon.state()) {
    case SKY_OBJECT_INIT: {
        m_moon.setType(random() % 2);
        m_moon.setState(SKY_OBJECT_GO);
        m_moon.setDirX(-1);
        m_moon.x = 128 + random() % 64;
        m_moon.y = random() % 10;
        m_moon.width = 16;
        m_moon.height = 17;
    }
    case SKY_OBJECT_GO: {
        if(m_moon.x < - m_moon.width) {
            m_moon.setState(SKY_OBJECT_INIT);
        }
    }
        break;
    }
    m_moon.move();
    m_moon.increaseTick(m_moon.state(), 1);
}
void DinosaurRun::drawBirds()
{

}

void DinosaurRun::drawTree()
{
    for(int treeID = 0; treeID < MAX_NUM_TREE; treeID++) {
        if(m_trees[treeID].type() == TREE_TYPE_1) {
            LCDLibrary::drawObject(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                (unsigned char*)treeType1Sprite[m_trees[treeID].state()][m_trees[treeID].spiteID(m_trees[treeID].state())],
                m_trees[treeID].width,m_trees[treeID].height,
                m_trees[treeID].x ,m_trees[treeID].y,m_invertBG);
        } else if(m_trees[treeID].type() == TREE_TYPE_2) {
            LCDLibrary::drawObject(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                (unsigned char*)treeType2Sprite[m_trees[treeID].state()][m_trees[treeID].spiteID(m_trees[treeID].state())],
                m_trees[treeID].width,m_trees[treeID].height,
                m_trees[treeID].x ,m_trees[treeID].y,m_invertBG);
        }
    }
}

void DinosaurRun::drawDinos()
{
    for(int playerID = 0; playerID < 2; playerID++) {
        if(m_dino[playerID].enabled()) {
            int spriteID = 0;
            switch (m_dino[playerID].state()) {
            case DINO_STAND:
                spriteID = 0;
                break;
            case DINO_RUN_GO:
                spriteID = 1;
                break;
            case DINO_JUMP_GO_UP:
            case DINO_JUMP_GO_DOWN:
                spriteID = 2;
            break;
            case DINO_DUCK_GO:
                spriteID = 3;
            break;
            }
            LCDLibrary::drawObject(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                (unsigned char*)dinoSpriteLeft[spriteID][m_dino[playerID].spiteID(m_dino[playerID].state())],
                m_dino[playerID].width,m_dino[playerID].height,
                m_dino[playerID].x ,m_dino[playerID].y,m_invertBG);
        }
    }
}

void DinosaurRun::drawBackground()
{
    // draw stars
    for(int starID = 0; starID < 2; starID++) {
        if(m_stars[starID].type() == STAR_TYPE_1) {
            LCDLibrary::drawObject(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                (unsigned char*)starType1Sprite[m_stars[starID].state()][m_stars[starID].spiteID(m_stars[starID].state())],
                m_stars[starID].width,m_stars[starID].height,
                m_stars[starID].x ,m_stars[starID].y,m_invertBG);
        } else if(m_stars[starID].type() == STAR_TYPE_2) {
            LCDLibrary::drawObject(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
                (unsigned char*)starType2Sprite[m_stars[starID].state()][m_stars[starID].spiteID(m_stars[starID].state())],
                m_stars[starID].width,m_stars[starID].height,
                m_stars[starID].x ,m_stars[starID].y,m_invertBG);
        }
    }

    // draw clouds
    for(int cloudID = 0; cloudID < 2; cloudID++) {
        LCDLibrary::drawObject(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
            (unsigned char*)cloudSprite[m_clouds[cloudID].state()][m_clouds[cloudID].spiteID(m_clouds[cloudID].state())],
            m_clouds[cloudID].width,m_clouds[cloudID].height,
            m_clouds[cloudID].x ,m_clouds[cloudID].y,m_invertBG);
    }

    // draw moon
    LCDLibrary::drawObject(m_gameMenu->app()->getScreenData(),m_gameMenu->app()->getScreenWidth(),m_gameMenu->app()->getScreenHeight(),
        (unsigned char*)moonSprite[m_moon.state()][m_moon.spiteID(m_moon.state())],
        m_moon.width,m_moon.height,
        m_moon.x ,m_moon.y,m_invertBG);
}

void DinosaurRun::drawOverlay()
{

}

void DinosaurRun::drawEndGameScores()
{

}

bool DinosaurRun::isDinoHitted(int dinoID)
{
    return false;
}
