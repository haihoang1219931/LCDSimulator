#ifndef SPACEIMPACT_H
#define SPACEIMPACT_H

#include "GameItem.h"
#include <vector>

enum BULLET_STATE {
    BULLET_INIT,
    BULLET_FIRING,
    BULLET_LOST,
    BULLET_HIT,
};

enum ALIEN_STATE {
    ALIEN_INIT,
    ALIEN_TOWARD,
    ALIEN_LOCK,
    ALIEN_LOST,
    ALIEN_HIT
};

enum SPACESHIP_STATE {
    SPACESHIP_INIT,
    SPACESHIP_MOVING,
    SPACESHIP_HIT
};

class Alien : public GameObject {
public:
    Alien(int _x = 0, int _y = 0, int _width = 0, int _height = 0, int _type = 0) : GameObject(_x,_y,_width,_height) {
        m_type = _type;
        m_hit = 0;
    }
    void setType(int type) {m_type = type;}
    int type() {return m_type;}
    int hit() { return m_hit;}
    void addHit(int hit) { m_hit += hit;}
private:
    int m_type;
    int m_hit;
};
class Bullet : public GameObject {
public:
    Bullet(int _x = 0, int _y = 0) : GameObject(_x,_y,2,1) {
        m_state = BULLET_INIT;
    }
};

class SpaceShip : public GameObject {
public:
    SpaceShip(int _x = 0, int _y = 0, int _width = 0, int _height = 0) : GameObject(_x,_y,_width,_height) {
        m_state = SPACESHIP_INIT;
    }
};

class GameMenu;
class SpaceImpact: public GameItem
{
public:
    SpaceImpact(GameMenu* gameMenu, int gameID);
    ~SpaceImpact() override;
    void loop() override;
    void playGame();
    void showScore();
    void exitGame();
    void clearDisplay();
    Alien createAlien();
    void updateMove(int x, int y);
    void updateBoss();
    void updateAliens();
    void updateBullets();
    void updateSpaceShip();
    void drawBullets();
    void drawSpaceShip();
    void drawAliens();
    void drawBoss();
    void drawOverlay();
    void drawEndGameScores();

private:
    // play parameters
    bool m_invertBG;
    int m_gameSpeed;
    int m_score;
    int m_life;
    int m_nukes;
    bool m_newBullet;
    Rect m_overlay;
    int m_tick;
    bool m_newBoss;
    Alien m_tmpAlien[5];
    Alien m_boss;
    std::vector<Alien> m_aliens;
    std::vector<Bullet> m_bullets;
    SpaceShip m_spaceShip;
};

#endif // SPACEIMPACT_H
