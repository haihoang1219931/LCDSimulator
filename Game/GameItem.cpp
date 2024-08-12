#include "GameItem.h"

GameItem::GameItem(GameMenu* gameMenu, int gameID)
{
    m_gameMenu = gameMenu;
    m_gameID = gameID;
}

void GameItem::loop() {

}

int GameItem::gameID() {
    return m_gameID;
}
