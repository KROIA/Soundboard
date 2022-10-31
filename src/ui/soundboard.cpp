#include "soundboard.h"
#include "ui_soundboard.h"
#include <QFileDialog>
#include "soundboardDatabase.h"


//DATABASE_USE_OBJECT(Sound)

using std::string;

Soundboard::Soundboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Soundboard)
{

    ui->setupUi(this);
    m_ribbon = new SoundboardRibbon(ui->ribbonTabWidget);

    m_settingsWindow = new UI_Settings(this);
    m_settingsWindow->hide();
    m_userSettings.read();
    m_settingsWindow->addSettings(&m_userSettings);



    // create a database which will load the saved sound profiles
    SoundboardDatabase database;

    // load from file
    database.load("test.json");


    // if no sound is in the database (file not available or empty),
    // then one sound will be added
    if(database.getSoundsCount() == 0)
    {
        SoundSource source;
        source.setRootPath(m_userSettings.getAudioRootPath());
        source.setRelativePath("lang.mp3");

        Sound sound;
        sound.setLoops(0);
        sound.setSource(source);
        sound.setVolume(1);
        sound.setPlaybackSpeed(1);
        sound.setName("Keine grosse Sache");
        database.addSound(sound);
    }

    // Get all saved sounds
    std::vector<Sound*> sounds = database.getSounds();
    for(size_t i=0; i<sounds.size(); ++i)
    {
        // Create a ui view for each sound
        UI_Sound *sound = new UI_Sound(this);

        // Set the sound to the UI-Element
        sound->setSound(*sounds[i]);

        // Add the UI-Element to the layout
        ui->scrollAreaWidgetContents->layout()->addWidget(sound);
    }

    // Save the database
    database.save();
}

Soundboard::~Soundboard()
{
    m_userSettings.save();

    delete ui;
}



void Soundboard::on_actionVersion_triggered()
{
    QMessageBox messageBox(this);
    messageBox.setWindowTitle("Versions Info");
    string dialog = "Project: " + projectInfo.projectName + "\n" +
                    projectInfo.versionsInfo.toString();
    messageBox.setText(dialog.c_str());
    messageBox.setStandardButtons(QMessageBox::Ok);
    if(messageBox.exec() == QMessageBox::Ok){
      // do something
    }else {
      // do something else
    }
}
void Soundboard::on_actionInfo_triggered()
{
    QMessageBox messageBox(this);
    messageBox.setWindowTitle("Info");
    string dialog = projectInfo.toString();
    messageBox.setText(dialog.c_str());
    messageBox.setStandardButtons(QMessageBox::Ok);
    if(messageBox.exec() == QMessageBox::Ok){
      // do something
    }else {
      // do something else
    }
}
void Soundboard::on_actionEinstellungen_triggered()
{
    m_settingsWindow->onShow();
    m_settingsWindow->show();
}


