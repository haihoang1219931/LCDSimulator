#include "ApplicationSim.h"
#include <sys/time.h>
#include <unistd.h>
#include "Button.h"

ApplicationSim::ApplicationSim(MainProcess* mainProcess)
{
    m_mainProcess = mainProcess;
    m_machineState = MACHINE_STATE::MACHINE_SHOW_MENU;
    ::printf("ApplicationSim constructor\r\n");
}
int ApplicationSim::printf(const char *fmt, ...) {
    char buffer[256];
    va_list args;
    va_start(args, fmt);
    int rc = vsprintf(buffer, fmt, args);
    va_end(args);
    ::printf("%s",buffer);
    return rc;
}
void ApplicationSim::msleep(int millis) {
#ifdef __linux__
    //linux code goes here
    struct timespec ts = { millis / 1000, (millis % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
#elif _WIN32
    // windows code goes here
    std::this_thread::sleep_for(std::chrono::milliseconds(millis));
#else
#endif
}

long ApplicationSim::getSystemTimeInMillis() {
    struct timeval curTime;
    gettimeofday(&curTime, NULL);
    return (curTime.tv_usec/1000 + curTime.tv_sec*1000);
}

void ApplicationSim::updateButtonState(BUTTON_ID btnID, bool pressed) {
    m_listButton[btnID]->setPressed(pressed);
}
