#include "soundboard.h"
#include <QApplication>


const ProjectInfo projectInfo{"SoundBoard",
                              "2022",
                              {
                                  "00.01.01",
                                  __DATE__,
                                  __TIME__,
                              },
                              {Author{
                                   "Luca",
                                   "Loop",
                                   "",
                                   "",
                               },
                               Author{
                                   "David",
                                   "Feldmann",
                                   "",
                                   "",
                               },
                               Author{
                                   "Alex",
                                   "Krieg",
                                   "alex.krieg@ost.ch",
                                   "",
                               }
                               }};

int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    // Enable scaling for high resolution displays
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif
#endif
    QApplication a(argc, argv);


    Soundboard w;
    w.show();
    return a.exec();
}
