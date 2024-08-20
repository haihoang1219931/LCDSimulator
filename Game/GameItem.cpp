#include "GameItem.h"

GameItem::GameItem(GameMenu* gameMenu, int gameID)
{
    m_gameMenu = gameMenu;
    m_gameID = gameID;
}

void GameItem::loop() {

}
int GameItem::gameState() {
    return m_state;
}
void GameItem::setState(GAME_PLAY_STATE state) {
    m_state = state;
}

int GameItem::gameID() {
    return m_gameID;
}
