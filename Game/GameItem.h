#ifndef GAMEITEM_H
#define GAMEITEM_H
#include <stdio.h>
#include <math.h>
class GameMenu;
#define MAX_OBJECT_STATE 10
enum GAME_PLAYER {
    GAME_PLAYER1,
    GAME_PLAYER2,
};
enum GAME_PLAY_STATE {
    GAME_PLAY_PLAYING,
    GAME_PLAY_SHOW_SCORE,
    GAME_PLAY_EXIT,
};

class Point{
public:
    Point(float _x = 0, float _y = 0) : x(_x), y (_y) {}
    float x;
    float y;
} ;
class Rect {
public:
    Rect(float _x = 0, float _y = 0, float _width = 0, float _height = 0) : x(_x), y (_y), width(_width), height(_height) {}
    float x;
    float y;
    float width;
    float height;
};
class GameObject : public Rect{
public:
    GameObject(float _x = 0, float _y = 0, float _width = 0, float _height = 0) : Rect(_x,_y,_width,_height) {
        for(int i=0; i< MAX_OBJECT_STATE; i++) {
            m_tick[i] = 0;
            m_numSlot[i] = 0;
            m_spiteID[i] = 0;
            m_totalTime[i] = 1;
        }
        m_dirX = 0;
        m_dirY = 0;
        m_state = 0;
        m_enabled = 0;
    }
    Point center() { return Point(x+width/2+1,y+height/2+1);}
    bool collide(GameObject& otherObject) {
        return abs(x-otherObject.x) < (width + otherObject.width)/2 &&
                abs(y-otherObject.y) < (height + otherObject.height)/2;
    }
    int state() {return m_state;}
    void setState(int state) {
        if(m_state != state) {
            m_tick[state] = 0;
            m_state = state;
        }
    }
    int tick(int state) {return m_tick[state];}
    void setTick(int state, int tick) {
//        printf("setTick state[%d] tick[%d]\r\n",state,tick);
        m_tick[state] = tick;
        m_spiteID[state] = 0;
//        printf("m_totalTime[%d][%d]\r\n",state,m_totalTime[state]);
        int timeFrame = m_tick[state]%m_totalTime[state];
        int timeCheck = 0;
        for(int i=0; i<m_numSlot[state]; i++) {
            if(timeFrame >= timeCheck && timeFrame < timeCheck+m_timeSlot[m_state][i]) {
                m_spiteID[state] = i;
                break;
            } else {
                timeCheck+= m_timeSlot[m_state][i];
            }
        }
//        printf("setTick state[%d] tick[%d] done\r\n",state,tick);
    }
    void increaseTick(int state, int dTick) { setTick(state,m_tick[state]+ dTick);}
    void setSpiteTimeSlot(int state, int* timeSlot, int numSlot) {
        m_totalTime[state] = 0;
//        m_state = state;
        m_numSlot[state] = numSlot;
        for(int i=0; i< numSlot; i++) {
            m_timeSlot[state][i] = timeSlot[i];
            m_totalTime[state] += timeSlot[i];
        }
    }
    int totalTime(int state) { return m_totalTime[state];}
    int spiteID(int state) {
        return m_spiteID[state];
    }
    float dirX() {return m_dirX;}
    void setDirX(float dirX) {m_dirX = dirX;}

    float dirY() {return m_dirY;}
    void setDirY(float dirY) {m_dirY = dirY;}

    void move() {
        x += m_dirX;
        y += m_dirY;
    }
    int enabled() {return m_enabled;}
    void setEnable(int enable) {
        if(m_enabled != enable) {
            m_enabled = enable;
        }
    }
    int type() { return m_type; }
    void setType(int type) {
        if(m_type != type) {
            m_type = type;
        }
    }
protected:
    int m_state;
    float m_dirX;
    float m_dirY;
    int m_tick[MAX_OBJECT_STATE];
    int m_spiteID[MAX_OBJECT_STATE];
    int m_timeSlot[MAX_OBJECT_STATE][10];
    int m_numSlot[MAX_OBJECT_STATE];
    int m_totalTime[MAX_OBJECT_STATE];
    int m_enabled;
    int m_type;
};
class GameItem
{
public:
    explicit GameItem(GameMenu* gameMenu, int gameID);
    virtual ~GameItem() {}
    virtual void loop();
    int gameState();
    void setState(GAME_PLAY_STATE state);
    int gameID();
protected:
    int m_state;
    int m_gameID;
    GameMenu* m_gameMenu;
};

#endif // GAMEITEM_H
