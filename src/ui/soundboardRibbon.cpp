#include "soundboardRibbon.h"


using std::string;

// path to the icons resources, relative to the .pro file
const string SoundboardRibbon::m_externIconsPath = "icons";
const string SoundboardRibbon::m_externIconsExtention = ".png";
const string SoundboardRibbon::m_qIconBasePath = ":/"+m_externIconsPath+"/";


SoundboardRibbon *SoundboardRibbon::RIBBON_INSTANCE_NAME = nullptr;
SoundboardRibbon::SoundboardRibbon(Ribbon* ribbonWidget)
    : QWidget(nullptr)
{
    RIBBON_INSTANCE_NAME = this;
    RIBBON_OBJ_NAME = ribbonWidget;

    // builds the buttons
    buildButtons();
    connect(m_ribbon,&QTabWidget::currentChanged,this,&SoundboardRibbon::onRibbonTabChanged);
}
SoundboardRibbon::~SoundboardRibbon()
{}

// NEW_BUTTONS [3]:
// Add a new line with this macro and your new button struct name
void SoundboardRibbon::buildButtons()
{
    RIBBON_CALL_SETUP(SoundsButtons);
    // RIBBON_CALL_SETUP(NEW_BUTTON_STRUCT_NAME);
}

// Implementation of the SoundsButton struct setup function
RIBBON_SETUP_FUNC_IMPL(SoundsButtons)
{
    string tab   = "Sounds";    // define in which tab the buttons shuld be located
    string group = "Sounds";    // define the group in the tab for the buttons

    addTab(m_qIconBasePath+"document"+m_externIconsExtention, tab);

   // RIBBON_BUTTONS(SoundsButtons).load = buttonFactory<QToolButton>("Laden","Lädt",
   //                                                 resourcePath("refresh"), true, tab, group);

   // RIBBON_BUTTONS(SoundsButtons).save = buttonFactory<QToolButton>("Speichern","Speichert die Software Option Datenbank",
   //                                                 resourcePath("floppy-disk"), true, tab, group);

    RIBBON_BUTTONS(SoundsButtons).addNew = buttonFactory<QToolButton>("Neu","Neuer Sound definieren",
                                                                      resourcePath("audio-add"), true, tab, group);
}

// NEW_BUTTONS [4]:
/*
RIBBON_SETUP_FUNC_IMPL(NEW_BUTTON_STRUCT_NAME)
{
    string tab   = "NewTab";      // define in which tab the buttons shuld be located
    string group = "NewGroup";    // define the group in the tab for the buttons

    // If you change the Tab, you also have to create the new tab using:
    addTab(m_qIconBasePath+"document"+m_externIconsExtention, tab);

    // No function needed to change the group, just change the variable and the next
    //  button you create will be in the new group.

    // To create the buttons in the struct, you have to call the following function
    //  The macro will let you access to the struct instance by the struct name.
    //  then uset "." to access the button pointer variable you defined in the struct.
    // The buttonFactory<...> function will instantiate a new button object with the given parameters.
    //  See buttonFactory<...>(...) in .h
   // RIBBON_BUTTONS(NEW_BUTTON_STRUCT_NAME).buttonOne = buttonFactory<QToolButton>("Laden","Lädt",
   //                                                 resourcePath("refresh"), true, tab, group);

   // RIBBON_BUTTONS(NEW_BUTTON_STRUCT_NAME).buttonTwo = buttonFactory<QToolButton>("Speichern","Speichert die Software Option Datenbank",
   //                                                 resourcePath("floppy-disk"), true, tab, group);

}
*/


void SoundboardRibbon::selectTab(int tab)
{
    if(m_instance == nullptr) return;
    if(m_instance->m_ribbon->count() > tab)
        m_instance->m_ribbon->setCurrentIndex(tab);
}

template<typename T>
T *SoundboardRibbon::buttonFactory(const string &text,
                                   const string &toolTip,
                                   const string &iconPath,
                                   bool enabled,
                                   const string &tab,
                                   const string &group)
{
    T *button = new T;
    button->setText(tr(text.c_str()));
    button->setToolTip(tr(toolTip.c_str()));
    button->setIcon(QIcon(iconPath.c_str()));
    m_ribbon->addButton(tab.c_str(), group.c_str(), button);
    button->setEnabled(enabled);
    return button;
}
void SoundboardRibbon::addTab(const string &iconPath, const string tabName)
{
    m_ribbon->addTab(QIcon(iconPath.c_str()), tabName.c_str());
}
string SoundboardRibbon::resourcePath(const string &iconName)
{
    return m_qIconBasePath+iconName+m_externIconsExtention;
}
void SoundboardRibbon::onRibbonTabChanged(int index)
{
    emit ribbonTabChanged(index);
}
