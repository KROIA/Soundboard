#include "soundboard.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Soundboard w;
    w.show();
    return a.exec();
}
