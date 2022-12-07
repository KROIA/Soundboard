#pragma once

#include <QDebug>
#include <QtGlobal>
#include <string>
//#include <iostream>

namespace Debug
{
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
//#define USE_COLORED_FUNC
static QDebug  __dbg = qDebug().nospace().noquote();
#define CONSOLE_STREAM __dbg
//#define CONSOLE_STREAM std::cout
#define DEBUGLN(message) \
  CONSOLE_STREAM << message << "\n";

#define DEBUG(message) \
    CONSOLE_STREAM << message;

#ifdef USE_COLORED_FUNC
#define COLORED_FUNC << Debug::colorizeFunc(Q_FUNC_INFO).toStdString().c_str()
#else
#define COLORED_FUNC
#endif
#define WARNING(message) \
    CONSOLE_STREAM << Debug::Color::bYellow.c_str() << "Warning  "<<Debug::Color::white.c_str() << ":" COLORED_FUNC <<" "<< message;

#define CRITICAL(message) \
    CONSOLE_STREAM << Debug::Color::bRed.c_str() << "Critical "<<Debug::Color::white.c_str() << ":" COLORED_FUNC <<" "<< message;

#define FATAL(message) \
    CONSOLE_STREAM << Debug::Color::bRed.c_str() << "Fatal    "<<Debug::Color::white.c_str() << ":" COLORED_FUNC <<" "<< message;
#else
#define DEBUGLN(message)
#define DEBUG(message)
#define WARNING(message)
#define CRITICAL(message)
#define FATAL(message)
#endif


