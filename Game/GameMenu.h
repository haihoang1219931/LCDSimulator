#ifndef GAMEMENU_H
#define GAMEMENU_H

class GameItem;
enum GAME_STATE {
    GAME_SHOW_MENU,
    GAME_PLAY,
    GAME_EXIT,
};

enum GAME_ID {
    GAME_MIN,
    GAME_SPACE_IMPACT,
    GAME_DINO_RUN,
    GAME_MAX,
};

class ApplicationController;
class GameMenu
{
public:
    GameMenu(ApplicationController* app);
    void loop();
    void showMenu();
    void playGame();
    void exitGame();
    ApplicationController* app();
    GAME_STATE machineState();
    void setMachineState(GAME_STATE newState);

private:
    void clearDisplay();
    void drawMenu();
    void drawScrollBar();

private:
    char* m_gameTittle[GAME_MAX];
    ApplicationController* m_app;
    GameItem* m_gameItem;
    int m_currentID;
    int m_machineState;

};

#endif // GAMEMENU_H
