#include "soundboard.h"
#include "ui_soundboard.h"
#include <QFileDialog>
#include "database.h"

using std::string;

Soundboard::Soundboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Soundboard)
{

    ui->setupUi(this);
    m_ribbon = new SoundboardRibbon(ui->ribbonTabWidget);

    m_settingsWindow = new UI_Settings(this);
    m_settingsWindow->hide();

    //m_userSettings.setAudioRootPath("C:\\Users\\alexk\\Documents\\Privat\\Softwareentwicklung\\QT\\Projekte\\Soundboard\\sounds");
    m_userSettings.read();

    m_settingsWindow->addSettings(&m_userSettings);



    //SoundSource source("C:\\Users\\alexk\\Documents\\Privat\\Softwareentwicklung\\QT\\Projekte\\Soundboard\\sounds\\lang.mp3");
    SoundSource source;
    source.setRootPath(m_userSettings.getAudioRootPath());
    source.setRelativePath("lang.mp3");





    m_sound = new UI_Sound(this);
    m_sound->setSource(source);
    m_sound->setVolume(1);
    m_sound->setPlaybackSpeed(1);
    m_sound->setName("Keine grosse Sache");

    QJsonObject writer;

    Sound sound;
    sound.setLoops(5);
    sound.setSource(source);
    sound.setVolume(1);
    sound.setPlaybackSpeed(1);
    sound.setName("Keine grosse Sache");
    sound.setID("random");

    //sound.save(writer);

    Database database;
    database.load("test.json");
    database.add(&sound);
    database.add(&sound);

    database.save("test.json");

    qDebug() << "ObjectCount" << database.getObjectCount();

    Sound *imported = database.getSound("random");
    if(imported)
    {
        qDebug() << imported->getName().c_str();
    }
    database.add(imported);
               /*
    QFile output("testOut.xml");
    output.open(QFile::OpenModeFlag::WriteOnly);
    QXmlStreamWriter stream(&output);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();

    //m_sound->save(&stream);

    stream.writeEndDocument();
    output.close();*/
/*

    QFile file("testOut.xml");
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Cannot read file" << file.errorString();
        exit(0);
    }
    QXmlStreamReader reader(&file);
    if(reader.readNextStartElement()) {
        qDebug() << reader.name();

        while(reader.readNextStartElement()) {
            qDebug() << reader.attributes().toVector()[0].value();
            if(reader.name() ==QString("rootPath"))
               qDebug() << reader.name() << "  Value= "<<reader.readElementText();
        }

    }*/
    ui->scrollAreaWidgetContents->layout()->addWidget(m_sound);
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


