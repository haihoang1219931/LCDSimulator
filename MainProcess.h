#ifndef MAINPROCESS_H
#define MAINPROCESS_H

#include <QObject>
#include <QThread>
#include "ApplicationSim.h"

class MainProcess : public QThread
{
    Q_OBJECT
public:
    explicit MainProcess(QThread *parent = nullptr);
    ~MainProcess();
Q_SIGNALS:
    void readyToUpdate();

public Q_SLOTS:
    void run() override;
    void startService();
    void stopService();
    void setRender(VideoRender* render);
    void updateScreen();
private:
    bool m_stopped;
    QThread* m_thread;
    ApplicationSim* m_application;
    VideoRender* m_render = nullptr;

};

#endif // MAINPROCESS_H
