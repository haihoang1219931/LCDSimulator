#ifndef SPACEIMPACT_H
#define SPACEIMPACT_H

#include "GameItem.h"
#include <vector>


enum BULLET_STATE {
    BULLET_INIT,
    BULLET_FIRING,
    BULLET_HIT,
};

enum ALIEN_STATE {
    ALIEN_INIT,
    ALIEN_TOWARD,
    ALIEN_LOCK,
    ALIEN_HIT
};

enum SPACESHIP_STATE {
    SPACESHIP_INIT,
    SPACESHIP_MOVING,
    SPACESHIP_HIT
};

/*
*/
class Alien : public GameObject {
public:
    Alien(int _x = 0, int _y = 0, int _width = 0, int _height = 0, int _type = 0) : GameObject(_x,_y,_width,_height) {
        m_state = ALIEN_INIT;
        m_type = _type;
    }
    void setType(int type) {m_type = type;}
    int type() {return m_type;}
private:
    int m_type;
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
    void clearDisplay();
    void updateMove(int x, int y);
    void updateAliens();
    void updateBullets();
    void updateSpaceShip();
    void drawBullets();
    void drawSpaceShip();
    void drawAliens();
    void drawOverlay();
private:
    int m_dirX;
    int m_dirY;
    bool m_newBullet;
    Rect m_overlay;
    int m_tick;
    std::vector<Alien> m_aliens;
    std::vector<Bullet> m_bullets;
    SpaceShip m_spaceShip;
};

#endif // SPACEIMPACT_H
