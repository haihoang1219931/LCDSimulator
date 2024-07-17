#include "MainProcess.h"
#include <unistd.h>
MainProcess::MainProcess(QThread *parent) :
    QThread(parent),
    m_thread(nullptr),
    m_stopped(false)

{
    m_application = new ApplicationSim(this);
}

MainProcess::~MainProcess()
{
    stopService();
    sleep(2);
}
void MainProcess::run() {
    while(!m_stopped) {
        m_application->loop();
        Q_EMIT readyToUpdate();
        m_application->msleep(30);
    }
    m_application->printf("Exit\r\n");
}
void MainProcess::startService() {
    if(m_thread != nullptr)
        m_thread->start();
    else start();
}
void MainProcess::stopService() {
    m_stopped = true;
    m_thread->terminate();
}
void MainProcess::setRender(VideoRender* render)
{
    m_render = render;
}

void MainProcess::updateScreen() {
    if(m_render != nullptr)
    {
        m_render->handleNewFrame(
                    m_application->getScreenData(),
                    m_application->getScreenWidth(),
                    m_application->getScreenHeight());
    }
}



