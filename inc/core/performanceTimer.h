#pragma once

#include <chrono>
#include <string>

class PerformanceTimer
{
    public:
        PerformanceTimer(bool autostart = false);

        double getRuntimeMs() const;
        std::string getRuntimeMsStr() const;

        void stop();
        void start();
        void restart();
        bool isRunning() const;
    private:
        std::chrono::system_clock::time_point m_start;
        std::chrono::system_clock::time_point m_end;
        bool m_isRunning;
};
