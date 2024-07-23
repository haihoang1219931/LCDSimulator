#include "ApplicationSim.h"

ApplicationSim::ApplicationSim(MainProcess* mainProcess)
{
    m_mainProcess = mainProcess;
    m_machineState = MACHINE_STATE::MACHINE_SHOW_MENU;
}
bool ApplicationSim::isButtonPressed(BUTTON_ID buttonID) {
    return false;
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
