#ifndef GAMEITEM_H
#define GAMEITEM_H
#include <stdio.h>
#include <math.h>
class GameMenu;
class Point{
public:
    Point(int _x = 0, int _y = 0) : x(_x), y (_y) {}
    int x;
    int y;
} ;
class Rect {
public:
    Rect(int _x = 0, int _y = 0, int _width = 0, int _height = 0) : x(_x), y (_y), width(_width), height(_height) {}
    int x;
    int y;
    int width;
    int height;
};
class GameObject : public Rect{
public:
    GameObject(int _x = 0, int _y = 0, int _width = 0, int _height = 0) : Rect(_x,_y,_width,_height) {
        m_tick = 0;
        m_numSlot = 0;
        m_spiteID = 0;
    }
    Point center() { return Point(x+width/2+1,y+height/2+1);}
    bool collide(GameObject& otherObject) {
        return abs(center().x-otherObject.center().x) < (width + otherObject.width)/2 &&
                abs(center().y-otherObject.center().y) < (height + otherObject.height)/2;
    }
    int state() {return m_state;}
    void setState(int state) {m_state = state;}
    int tick() {return m_tick;}
    void setTick(int tick) {
        m_tick = tick;
        m_spiteID = 0;
        int timeFrame = m_tick%m_totalTime;
        int timeCheck = 0;
        for(int i=0; i<m_numSlot; i++) {
            if(timeFrame >= timeCheck && timeFrame < timeCheck+m_timeSlot[m_state][i]) {
                m_spiteID = i;
                break;
            } else {
                timeCheck+= m_timeSlot[m_state][i];
            }
        }
    }
    void increaseTick(int dTick) { setTick(m_tick+ dTick);}
    void setSpiteTimeSlot(int state, int* timeSlot, int numSlot) {
        m_totalTime = 0;
//        m_state = state;
        m_numSlot = numSlot;
        for(int i=0; i< numSlot; i++) {
            m_timeSlot[state][i] = timeSlot[i];
            m_totalTime += timeSlot[i];
        }
    }
    int totalTime() { return m_totalTime;}
    int spiteID() {
        return m_spiteID;
    }
protected:
    int m_state;
    int m_tick;
    int m_spiteID;
    int m_timeSlot[10][10];
    int m_numSlot;
    int m_totalTime;
};
class GameItem
{
public:
    explicit GameItem(GameMenu* gameMenu, int gameID);
    virtual ~GameItem() {}
    virtual void loop();
    int gameID();
protected:
    GameMenu* m_gameMenu;
    int m_gameID;
};

#endif // GAMEITEM_H
