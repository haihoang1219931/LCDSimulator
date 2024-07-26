#ifndef MAINMENU_H
#define MAINMENU_H

enum MENU_ID {
    MENU_MIN,
    MENU_CALL,
    MENU_MESSAGE,
    MENU_CONTACTS,
    MENU_GAME,
    MENU_MAX,
};

class ApplicationController;
class MainMenu
{
public:
    MainMenu(ApplicationController* app);
    void loop();
    void clearDisplay();
    void drawMenu();
    void drawScrollBar();
private:
    ApplicationController* m_app;
    int m_currentID;

};

#endif // MAINMENU_H
