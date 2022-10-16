#include "soundboard.h"
#include <QApplication>


const ProjectInfo projectInfo{"SoundBoard",
                              "2022",
                              {
                                  "00.00.00",
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
                                   "Pele",
                                   "",
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
  Debug::setup();
  QApplication a(argc, argv);
  Soundboard w;
  w.show();
  return a.exec();
}
