#include <QApplication>
#include "soundboard.h"

int main(int argc, char *argv[])
{
    Debug::setup();
    QApplication a(argc, argv);
    Soundboard w;
    w.show();    return a.exec();
}
