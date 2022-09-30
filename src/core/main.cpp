#include <QApplication>
#include "soundboard.h"

const ProjectInfo projectInfo
{
    .projectName = "SoundBoard",
    .projectYear = "2022",
    .versionsInfo
    {
        .version         = "00.00.00",
        .compilationDate = __DATE__,
        .compilationTime = __TIME__,
    },
    .authors
    {
        Author
        {
            .firstName = "Luca",
            .lastName  = "Loop",
            .email     = "",
            .phone     = "",
        },
        Author
        {
            .firstName = "David",
            .lastName  = "Feldmann",
            .email     = "",
            .phone     = "",
        },
        Author
        {
            .firstName = "Alex",
            .lastName  = "Krieg",
            .email     = "alex.krieg@ost.ch",
            .phone     = "",
        }
    }
};

int main(int argc, char *argv[])
{
    Debug::setup();
    QApplication a(argc, argv);
    Soundboard w;
    w.show();    return a.exec();
}
