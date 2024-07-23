#include "MainProcess.h"
#include "LCDLibrary.h"
MainProcess::MainProcess(QThread *parent) :
    QThread(parent),
    m_thread(nullptr),
    m_stopped(false)

{
    m_application = new ApplicationSim(this);
    memset(m_renderData,0,sizeof(m_renderData));
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
        int width = m_application->getScreenWidth();
        int height = m_application->getScreenHeight();
        unsigned char* binaryFrame = m_application->getScreenData();
//        printf("BinaryFrame:\r\n");
//        for(int row = 0; row < height; row++) {
//            for(int col = 0; col < width/8; col ++) {
//                printf(BYTE_TO_BINARY_PATTERN "",BYTE_TO_BINARY (binaryFrame[row*width/8+col]));
//            }
//            printf("\r\n");
//        }
//        printf("\r\n");
//        printf("RenderFrame:\r\n");
        for(int row = 0; row < height; row++) {
            for(int col = 0; col < width/8; col ++) {
                for(int bit = 0; bit <8; bit++){
                    m_renderData[row*width+col*8+bit] = 
                            (binaryFrame[row*width/8+col] & (0x01 << (7-bit))) == 0 ? 0 : 0xFF;
                }
                
            }
//            printf("\r\n");
        }
        m_render->handleNewFrame(m_renderData, width, height);
    }
}



