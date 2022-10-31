#pragma once

#include <QDebug>
#include <QtGlobal>
#include <stdio.h>
#include <iostream>
//#include <wchar.h>
//#include <windows.h>
#include <string>

namespace Debug
{
    extern void setup();
    extern QString colorizeFunc(QString name);
    namespace Color
    {
        extern const std::string black;
        extern const std::string red;
        extern const std::string green;
        extern const std::string yellow;
        extern const std::string blue;
        extern const std::string purple;
        extern const std::string cyan;
        extern const std::string white;

        extern const std::string bBlack;
        extern const std::string bRed;
        extern const std::string bGreen;
        extern const std::string bYellow;
        extern const std::string bBlue;
        extern const std::string bPurple;
        extern const std::string bCyan;
        extern const std::string bWhite;
    }
}
#ifdef QT_DEBUG
#define CONSOLE_STREAM qDebug()
#define DEBUGLN(message) \
  CONSOLE_STREAM << message << "\n";

#define DEBUG(message) \
    CONSOLE_STREAM << message;

#define WARNING(message) \
    CONSOLE_STREAM << Debug::Color::bYellow.c_str() << "Warning "<<Debug::Color::white.c_str() << ":"  << Debug::colorizeFunc(Q_FUNC_INFO).toStdString().c_str() <<" "<< message;

#define CRITICAL(message) \
    CONSOLE_STREAM << Debug::Color::bRed.c_str() << "Critical"<<Debug::Color::white.c_str() << ":" << Debug::colorizeFunc(Q_FUNC_INFO).toStdString().c_str() <<" "<< message;

#define FATAL(message) \
    CONSOLE_STREAM << Debug::Color::bRed.c_str() << "Fatal   "<<Debug::Color::white.c_str() << ":" << Debug::colorizeFunc(Q_FUNC_INFO).toStdString().c_str() <<" "<< message;
#else
#define DEBUGLN(message)
#define DEBUG(message)
#define WARNING(message)
#define CRITICAL(message)
#define FATAL(message)
#endif


