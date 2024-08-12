#ifndef SNAKE_H
#define SNAKE_H

#include "GameItem.h"
#include <vector>
enum BAIT_STATE {
    BAIT_NO_CONTACT,
    BAIT_EATING,
    BAIT_APPEND,
};

class GameMenu;
class Snake: public GameItem
{
public:
    Snake(GameMenu* gameMenu, int gameID);
    ~Snake() override;
    void loop() override;
    void clearDisplay();
    void updateMove(int x, int y);
    void updateBait();
    void drawBait();
    void drawBody();
    void drawOverlay();
private:
    int m_score;
    int m_baitState;
    int m_dirX;
    int m_dirY;
    std::vector<Point> m_body;
    Point m_bait;
};

#endif // SNAKE_H
