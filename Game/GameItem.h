#ifndef GAMEITEM_H
#define GAMEITEM_H

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
