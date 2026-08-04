#ifndef DINOSAURRUN_H
#define DINOSAURRUN_H

#include "GameItem.h"
#include <vector>
#define MAX_NUM_BIRD 1
#define MAX_NUM_TREE 1
enum OBJECT_STATE {
    OBJECT_INIT,
    OBJECT_TOWARD,
    OBJECT_LOST
};

enum DINO_STATE {
    DINO_STAND,
    DINO_RUN,
    DINO_RUN_GO,
    DINO_JUMP,
    DINO_JUMP_GO_UP,
    DINO_JUMP_GO_DOWN,
    DINO_DUCK,
    DINO_DUCK_GO,
    DINO_DIE,
};

enum STAR_TYPE {
    STAR_TYPE_1,
    STAR_TYPE_2,
};

enum TREE_TYPE {
    TREE_TYPE_1,
    TREE_TYPE_2,
};

enum SKY_OBJECT_STATE {
    SKY_OBJECT_INIT,
    SKY_OBJECT_GO,
};

class GameMenu;
class DinosaurRun: public GameItem
{
public:
    DinosaurRun(GameMenu* gameMenu, int gameID);
    ~DinosaurRun() override;
    void loop() override;
    void waitInput();
    void playGame();
    void showScore();
    void exitGame();
    void clearDisplay();
    GameObject createBird();
    GameObject createTree();
    GameObject createCloud();
    GameObject createStar();
    GameObject createSun();
    void updateMove(int dinoID, int state);
    void updateDinos();
    void updateObstacles();
    void updateBackground();
    void drawObstacles();
    void drawDinos();
    void drawBackground();
    void drawOverlay();
    void drawEndGameScores();

private:
    bool isDinoHitted(int dinoID);

private:
    bool m_invertBG;
    GameObject m_dino[2];
    GameObject m_birds[MAX_NUM_BIRD];
    GameObject m_trees[MAX_NUM_TREE];
    GameObject m_clouds[2];
    GameObject m_stars[2];
    GameObject m_moon;
    int m_wait = 0;
};

#endif // DINOSAURRUN_H
