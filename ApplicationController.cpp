#include "ApplicationController.h"

ApplicationController::ApplicationController(QThread *parent) : QThread(parent)
{
    resetGame();
}

ApplicationController::~ApplicationController() {

}
void ApplicationController::resetGame() {

}

void ApplicationController::startService() {
    m_stopped = false;
    start();
}

void ApplicationController::stopService() {
    m_stopped = true;
}
void ApplicationController::setRender(VideoRender* render)
{
    m_render = render;
}
void ApplicationController::renderFrame(unsigned char* frameData, int width, int height)
{
    if(m_render != nullptr)
    {
        m_frameSize.setWidth(width);
        m_frameSize.setHeight(height);
        m_render->handleNewFrame(frameData,width,height);        
    }
}
void ApplicationController::loop() {
    
}
void ApplicationController::run() {
    resetGame();
    while(!m_stopped) {
        loop();
        readyToUpdate();
        msleep(30);
    }
    printf("Exit\r\n");
}
void ApplicationController::handleAxisChanged(int x, int y) {
    
}
void ApplicationController::handleBackPressed() {

}
void ApplicationController::handleEnterPressed() {

}
void ApplicationController::updateScreen() {
    renderFrame(m_frameData,128,64);
    printf(".");
}