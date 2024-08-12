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
//#define DEBUG
void MainProcess::updateScreen() {
    if(m_render != nullptr)
    {
        int width = m_application->getScreenWidth();
        int height = m_application->getScreenHeight();
        unsigned char* binaryFrame = m_application->getScreenData();
#ifdef DEBUG
        printf("BinaryFrame:\r\n");
        for(int row = 0; row < height; row++) {
            for(int col = 0; col < width/8; col ++) {
                printf(BYTE_TO_BINARY_PATTERN "",BYTE_TO_BINARY (binaryFrame[row*width/8+col]));
            }
            printf("\r\n");
        }
        printf("\r\n");
        printf("RenderFrame:\r\n");
#endif
        int sRow = 8; int sCol = 8;
        for(int row = 0; row < height; row++) {
            for(int col = 0; col < width/8; col ++) {
                for(int bit = 0; bit <8; bit++){
                    // pixel value from
                    // (row * sRow, (col*8+bit)*sCol)
                    // to
                    // ((row+1) * sRow-1, (col*8+bit)*sCol-1)
                    unsigned char pixelValue = (binaryFrame[row*width/8+col] & (0x01 << (7-bit))) == 0 ? 0 : 0xFF;

                    for(int subRow = 0; subRow < sRow-2; subRow++) {
                        for(int subCol = 0; subCol < sCol-2; subCol ++) {
                            m_renderData[(row * sRow + subRow)* width * sCol + ((col*8 + bit)*sCol + subCol)] = pixelValue;
                        }
                    }

                }
                
            }
#ifdef DEBUG
            printf("\r\n");
#endif
        }
        m_render->handleNewFrame(m_renderData, width*sRow, height*sCol);
    }
}
void MainProcess::handleButtonPressed(int buttonID, bool pressed) {
//    printf("BTN[%d] [%s]\r\n",buttonID,pressed?"PRESSED":"RELEASED");
    m_application->updateButtonState((BUTTON_ID)buttonID, pressed);
}


