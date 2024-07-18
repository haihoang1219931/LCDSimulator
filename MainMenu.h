#ifndef MAINMENU_H
#define MAINMENU_H

enum MENU_ID {
    MENU_MIN,
    MENU_MESSAGE,
    MENU_CALL,
    MENU_GAME,
    MENU_MAX,
};

class ApplicationController;
class MainMenu
{
public:
    MainMenu(ApplicationController* app);
    void loop();
    void draw();
private:
    ApplicationController* m_app;
    int m_currentID;

};

#endif // MAINMENU_H
