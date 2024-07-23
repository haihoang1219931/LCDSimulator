#ifndef BUTTON_H
#define BUTTON_H

enum BUTTON_STATE {
    BUTTON_NOMAL,
    BUTTON_PRESS,
    BUTTON_HOLD,
};

class ApplicationController;
class Button
{
public:
    Button(ApplicationController* app, int buttonID);
    void checkState();
    void setPressed(bool pressed);
    bool isPressed();
    long holdingTime();
private:
    ApplicationController* m_app;
    int m_buttonID;
    bool m_buttonSignalHigh;
    long m_buttonSignalHighTime;
    long m_buttonSignalLowTime;
    bool m_buttonSignalHandling;
    BUTTON_STATE m_buttonState;
};

#endif // BUTTON_H
