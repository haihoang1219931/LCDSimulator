#include "Button.h"
#include "ApplicationController.h"
Button::Button(ApplicationController* app, int buttonID) :
    m_app(app),
    m_buttonID(buttonID),
    m_buttonSignalHigh(false),
    m_buttonSignalHighTime(0),
    m_buttonSignalLowTime(0),
    m_buttonSignalHandling(false),
    m_buttonState(BUTTON_NOMAL)
{

}

void Button::checkState() {
    if(m_buttonSignalHigh && !m_buttonSignalHandling) {
        m_buttonSignalHighTime = m_app->getSystemTimeInMillis();
        m_buttonSignalHandling = true;
        m_buttonState = BUTTON_PRESS;
    }
    else if(!m_buttonSignalHigh && m_buttonSignalHandling)
    {
        m_buttonSignalLowTime = m_app->getSystemTimeInMillis();
        m_buttonSignalHandling = false;
        if(m_buttonSignalLowTime - m_buttonSignalHighTime >= 1) {
            m_app->printf("====== button[%03d] signal [%ld]ms\r\n",
                          m_buttonID,
                   (m_buttonSignalLowTime - m_buttonSignalHighTime));
            m_buttonState = BUTTON_NOMAL;
        }
    }
    if(m_buttonID == 2)
    m_app->printf("BTN[%03d] [%s]\r\n",m_buttonID, m_buttonState == BUTTON_PRESS ? "PRESSED":"RELEASED");
}

void Button::setPressed(bool pressed) {
    m_buttonSignalHigh = pressed;
}

bool Button::isPressed() {

    return m_buttonState == BUTTON_PRESS;
}

long Button::holdingTime() {
    return m_buttonSignalLowTime - m_buttonSignalHighTime;
}
