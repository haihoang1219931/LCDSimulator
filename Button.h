#ifndef BUTTON_H
#define BUTTON_H

class Button
{
public:
    Button();
    void setPressed(bool m_pressed);
    bool isPressed();
    long holdingTime();
private:
    int m_buttonID;
    bool m_buttonSignalHigh;
    long m_buttonSignalHighTime;
    long m_buttonSignalLowTime;
    bool m_buttonSignalHandling;
};

#endif // BUTTON_H
