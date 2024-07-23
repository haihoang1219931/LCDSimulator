#include "Button.h"

Button::Button()
{

}

bool Button::isPressed() {
    return false;
}

long Button::holdingTime() {
    return m_buttonSignalLowTime - m_buttonSignalHighTime;
}
