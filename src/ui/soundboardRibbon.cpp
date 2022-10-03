#include "soundboardRibbon.h"

const string SoundboardRibbon::m_externIconsPath = "icons";
const string SoundboardRibbon::m_externIconsExtention = ".png";
const string SoundboardRibbon::m_qIconBasePath = ":/"+m_externIconsPath+"/";

SoundboardRibbon *SoundboardRibbon::m_instance = nullptr;
SoundboardRibbon::SoundboardRibbon(Ribbon* ribbonWidget)
    : QWidget(nullptr)
{
    m_instance = this;
    m_ribbon = ribbonWidget;

    connect(m_ribbon,&QTabWidget::currentChanged,this,&SoundboardRibbon::onRibbonTabChanged);

    buildButtons();

    // Add tabs to ribbon

    //m_ribbon->addTab(QIcon((m_qIconBasePath+"monitor_1"+m_externIconsExtention).c_str()), "View");

    //m_ribbon->addTab(QIcon((m_qIconBasePath+"information_1"+m_externIconsExtention).c_str()), "Help");




    /*

    // Add 'Open project' button
    QToolButton *openProjectButton = new QToolButton;
    openProjectButton->setText(tr("Open"));
    openProjectButton->setToolTip(tr("Open existing project"));
    openProjectButton->setIcon(QIcon(qIconBasePath+"live_folder_2.png"));
    openProjectButton->setEnabled(true);
    m_ribbon->addButton("Project", "Project", openProjectButton);

    // Add 'New project' button
    QToolButton *newProjectButton = new QToolButton;
    newProjectButton->setText(tr("New"));
    newProjectButton->setToolTip(tr("Create new project"));
    newProjectButton->setIcon(QIcon(qIconBasePath+"create_new_2.png"));
    newProjectButton->setEnabled(true);
    m_ribbon->addButton("Project", "Project", newProjectButton);

    // Add 'Save project' button
    QToolButton *saveProjectButton = new QToolButton;
    saveProjectButton->setText(tr("Save"));
    saveProjectButton->setToolTip(tr("Save project"));
    saveProjectButton->setIcon(QIcon(qIconBasePath+"save_2.png"));
    saveProjectButton->setEnabled(false);
    m_ribbon->addButton("Project", "Project", saveProjectButton);

    // Add 'Open file' button
    QToolButton *openFileButton = new QToolButton(this);
    openFileButton->setText(tr("File"));
    openFileButton->setToolTip(tr("Open file or directory"));
    openFileButton->setIcon(QIcon(qIconBasePath+"add_folder_2.png"));

    // Add dropdown menu to button
    openFileButton->setPopupMode(QToolButton::MenuButtonPopup);
    QMenu *menu = new QMenu("Title");
    //menu->addAction(QIcon(":/icons/folder_2.png"),
    //                "Recent directory");
    menu->addAction(QIcon(qIconBasePath+"file_2.png"), "Recent file 1");
    menu->addAction(QIcon(qIconBasePath+"file_2.png"), "Recent file 2");
    menu->addAction(QIcon(qIconBasePath+"file_2.png"), "Recent file 3");
    openFileButton->setMenu(menu);

    m_ribbon->addButton("Project", "Import", openFileButton);

    // Add 'Open database' button
    QToolButton *openDatabaseButton = new QToolButton;
    openDatabaseButton->setText(tr("Database"));
    openDatabaseButton->setToolTip(tr("Connect to database"));
    openDatabaseButton->setIcon(QIcon(qIconBasePath+"add_database_2.png"));
    m_ribbon->addButton("Project", "Import", openDatabaseButton);


    // Add 'Connect to web service' button
    QToolButton *connectWebserviceButton = new QToolButton;
    connectWebserviceButton->setText(tr("Web service"));
    connectWebserviceButton->setToolTip(tr("Connect to web service"));
    connectWebserviceButton->setIcon(QIcon(qIconBasePath+"add_link_2.png"));
    m_ribbon->addButton("Project", "Import", connectWebserviceButton);*/
}
SoundboardRibbon::~SoundboardRibbon()
{

}
SoundsButtons SoundboardRibbon::getSoundButtons()
{
    if(m_instance == nullptr) return SoundsButtons{nullptr};
    return m_instance->m_soundButtons;
}

void SoundboardRibbon::selectTab(int tab)
{
    if(m_instance == nullptr) return;
    m_instance->m_ribbon->setCurrentIndex(tab);
}

template<typename T>
T *SoundboardRibbon::buttonFactory(const string &text, const string &toolTip,const string &iconName,
                           bool enabled,const string &tab,const string &group)
{
    T *button = new T;
    button->setText(tr(text.c_str()));
    button->setToolTip(tr(toolTip.c_str()));
    button->setIcon(QIcon((m_qIconBasePath+iconName+m_externIconsExtention).c_str()));
    m_ribbon->addButton(tab.c_str(), group.c_str(), button);
    button->setEnabled(enabled);
    return button;
}
void SoundboardRibbon::onRibbonTabChanged(int index)
{
    emit ribbonTabChanged(index);
}
void SoundboardRibbon::buildButtons()
{
    buildSoundButtons();
}
void SoundboardRibbon::buildSoundButtons()
{
    string tab = "Sounds";
    string group = "Sounds";
    m_ribbon->addTab(QIcon((m_qIconBasePath+"document"+m_externIconsExtention).c_str()), tab.c_str());
   // m_soundButtons.load   = buttonFactory<QToolButton>("Laden","Lädt",
   //                                                 "refresh", true, tab, group);

   // m_soundButtons.save = buttonFactory<QToolButton>("Speichern","Speichert die Software Option Datenbank",
   //                                                 "floppy-disk", true, tab, group);

    m_soundButtons.addNew   = buttonFactory<QToolButton>("Neu","Neuer Sound definieren",
                                                    "audio-add", true, tab, group);

}

