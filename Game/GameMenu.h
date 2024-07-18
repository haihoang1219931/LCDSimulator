#ifndef GAMEMENU_H
#define GAMEMENU_H

enum GAME_STATE {
    GAME_SHOW_MENU,
    GAME_SPACE_IMPACT,
    GAME_SNAKE,
    GAME_TANK,
    GAME_RACING
};
class ApplicationController;
class GameMenu
{
public:
    GameMenu(ApplicationController* app);
    void loop();
    void draw();
private:
    GAME_STATE m_machineState;
    ApplicationController* m_app;
    int m_currentID;
};

#endif // GAMEMENU_H
