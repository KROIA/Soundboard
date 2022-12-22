#pragma once

#include <chrono>
#include <string>

#ifdef QT_DEBUG
/**
 * \author Alex Krieg
 * \date   12.10.2022
 *
 * \brief The PerformanceTimer class
 * \details This is a small helper class to measure the time interval between two time points
 *
 */
class PerformanceTimer
{
    public:
        /**
         * \brief PerformanceTimer constructor
         * \param autostart to start the timer after the object got created
         */
        PerformanceTimer(bool autostart = false);

        /**
         * \return The current runtime in ms
         */
        double getRuntimeMs() const;

        /**
         * \return The current time in ms as a string
         */
        std::string getRuntimeMsStr() const;

        /**
         * \brief Stops the timer
         */
        void stop();

        /**
         * \brief Starts the timer
         */
        void start();

        /**
         * \brief Resets the timer and strts it again
         */
        void restart();

        /**
         * \return true if the timer is currently running
         *         false if the timer is stopped
         */
        bool isRunning() const;
    private:
        std::chrono::system_clock::time_point m_start;
        std::chrono::system_clock::time_point m_end;
        bool m_isRunning;
};
#endif
