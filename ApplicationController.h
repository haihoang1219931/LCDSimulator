#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include <QObject>
#include <QThread>
#include <QSize>
#include "VideoDisplay/VideoRender.h"
#include <SpaceImpact.h>

class ApplicationController : public QThread
{
    Q_OBJECT
    
public:
    explicit ApplicationController(QThread *parent = nullptr);
    virtual ~ApplicationController();
    
    void loop();
    
private:
    void resetGame();
public Q_SLOTS:
    void setRender(VideoRender* render);
    void renderFrame(unsigned char* frameData, int width, int height);
    void startService();
    void stopService();
    void handleAxisChanged(int x, int y);
    void handleBackPressed();
    void handleEnterPressed();
    void updateScreen();
    
Q_SIGNALS:
    void readyToUpdate();
private:
    void run() override;
    
private:
    bool m_stopped;
    VideoRender* m_render = nullptr;
    QSize m_frameSize;
    unsigned char m_frameData[33177600];
};

#endif // APPLICATIONCONTROLLER_H
