#include "performanceTimer.h"

PerformanceTimer::PerformanceTimer(bool autostart)
{
    m_isRunning = false;
    if(autostart)
        start();
}

double PerformanceTimer::getRuntimeMs() const
{
    std::chrono::duration<double> duration;
    if(m_isRunning)
        duration = std::chrono::high_resolution_clock::now() - m_start;
    else
        duration = m_end - m_start;
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    return ms.count();
}
std::string PerformanceTimer::getRuntimeMsStr() const
{
    double ms = getRuntimeMs();
    return std::to_string(ms)+"ms";
}

void PerformanceTimer::stop()
{
    if(!m_isRunning)
        return;
    m_end = std::chrono::high_resolution_clock::now();
    m_isRunning = true;
}
void PerformanceTimer::start()
{
    if(m_isRunning)
        return;
    m_isRunning = true;
    m_start = std::chrono::high_resolution_clock::now();
}
void PerformanceTimer::restart()
{
    stop();
    start();
}
bool PerformanceTimer::isRunning() const
{
    return m_isRunning;
}
