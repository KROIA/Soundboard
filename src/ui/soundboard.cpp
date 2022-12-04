#include "soundboard.h"
#include "ui_soundboard.h"
#include <QFileDialog>

#include "LaunchpadButton.h"

using std::string;

Soundboard::Soundboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Soundboard)
{

    ui->setupUi(this);

    m_ribbon = new SoundboardRibbon(ui->ribbonTabWidget);
    SoundsButtons sb = m_ribbon->getSoundsButtons();
    connect(sb.edit, &QPushButton::clicked, this, &Soundboard::onRibbonEditSoundsPressed);

    m_settingsWindow = new UI_Settings(this);
    m_settingsWindow->hide();
    m_userSettings.read();
    m_settingsWindow->addSettings(&m_userSettings);
    m_launchpad = new UI_Launchpad(this);
    ui->scrollAreaWidgetContents->layout()->addWidget(m_launchpad);




    // load from file
    SoundboardDatabase::load("test.json");
    m_launchpad->addSound(SoundboardDatabase::getSounds());

}

Soundboard::~Soundboard()
{
    m_userSettings.save();
    SoundboardDatabase::save();
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

void Soundboard::onRibbonEditSoundsPressed()
{
    SoundsButtons sb = m_ribbon->getSoundsButtons();
    sb.edit->setOverlayEnable(!sb.edit->overlayEnabled());
    LaunchpadButton::setEditMode(sb.edit->overlayEnabled());
}
