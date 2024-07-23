#ifndef MAINPROCESS_H
#define MAINPROCESS_H

#include <QObject>
#include <QThread>
#include "ApplicationSim.h"

class ButtonClass
{
    Q_GADGET
public:
    explicit ButtonClass();

    enum BUTTON_ID {
        BTN_UP = 0,
        BTN_DOWN = 1,
        BTN_LEFT = 2,
        BTN_RIGHT = 3,
        BTN_ENTER = 4,
        BTN_BACK = 5,
        BTN_MAX,
    };
    Q_ENUMS(MainProcess::BUTTON_ID)
};
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
    void handleButtonPressed(int buttonID, bool pressed);
private:
    unsigned char m_renderData[3110400]; // 1920x1080 I420
    bool m_stopped;
    QThread* m_thread;
    ApplicationSim* m_application;
    VideoRender* m_render = nullptr;

};

#endif // MAINPROCESS_H
