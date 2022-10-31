#include "LaunchpadButton.h"
#include <QVBoxLayout>
#include <QSpacerItem>


bool LaunchpadButton::m_editMode = false;
std::vector<LaunchpadButton*> LaunchpadButton::m_buttons;
UI_SoundSettings *LaunchpadButton::m_settingsWindow = nullptr;
unsigned int LaunchpadButton::m_width = 50;
unsigned int LaunchpadButton::m_height = 50;

LaunchpadButton::LaunchpadButton(QWidget *parent)
    :   QPushButton(parent)
{
    m_sound = nullptr;

    // Add this button to the global button list
    m_buttons.push_back(this);

    connect(this, &QPushButton::pressed, this, &LaunchpadButton::onButtonPress);

    if(!m_settingsWindow)
        m_settingsWindow = new UI_SoundSettings();

    m_label = new QLabel(this);
    if(!layout())
    {
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->setContentsMargins(0,0,0,0);
        setLayout(layout);
    }
    layout()->addWidget(m_label);
    layout()->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    setSize_internal(m_width, m_height);
}
LaunchpadButton::~LaunchpadButton()
{
    m_sound = nullptr;

    // Remove this button from the global button list
    for(size_t i=0; i<m_buttons.size(); ++i)
        if(m_buttons[i] == this)
            m_buttons.erase(m_buttons.begin() +i);

    if(m_buttons.size() == 0)
    {
        delete m_settingsWindow;
        m_settingsWindow = nullptr;
    }
}

void LaunchpadButton::setSound(Sound *sound)
{
    if(m_sound)
    {
        disconnect(m_sound, &QObject::destroyed, this, &LaunchpadButton::onSoundDeleted);
        disconnect(m_sound, &Sound::onNameChanged, this, &LaunchpadButton::onSoundNameChanged);
    }
    m_sound = sound;
    if(m_sound)
    {
        m_sound->setButtonCoord(m_buttonPos);
        connect(m_sound, &QObject::destroyed, this, &LaunchpadButton::onSoundDeleted);
        connect(m_sound, &Sound::onNameChanged, this, &LaunchpadButton::onSoundNameChanged);
        onSoundNameChanged(m_sound->getName());
        setEnabled(m_sound->getSource().isValid());

    }
    else
        setEnabled(false);
}
Sound *LaunchpadButton::getSound() const
{
    return m_sound;
}

void LaunchpadButton::setArrayPos(const Coord &pos)
{
    m_buttonPos = pos;
    if(m_sound)
        m_sound->setButtonCoord(m_buttonPos);
}
const Coord &LaunchpadButton::getArrayPos()
{
    return m_buttonPos;
}

void LaunchpadButton::setEditMode(bool editEnable)
{
    m_editMode = editEnable;
    if(m_editMode)
    {
        for(size_t i=0; i<m_buttons.size(); ++i)
        {
            m_buttons[i]->setEnabled(true);
            m_buttons[i]->m_sound->stop();
            //m_buttons[i]->setText("");
            //m_buttons[i]->setIcon(QIcon(":/icons/audio.png"));
            m_buttons[i]->m_label->setPixmap(QPixmap(":/icons/settings.png").scaledToWidth(0.5f*m_width));

        }
    }
    else
    {
        for(size_t i=0; i<m_buttons.size(); ++i)
        {
            if(m_buttons[i]->m_sound)
            {
                m_buttons[i]->setEnabled(m_buttons[i]->m_sound->getSource().isValid());
                m_buttons[i]->onSoundNameChanged(m_buttons[i]->m_sound->getName());
            }
            else
            {
                m_buttons[i]->setEnabled(false);
                m_buttons[i]->onSoundNameChanged("");
            }
            //m_buttons[i]->setIcon(QIcon());
            m_buttons[i]->m_label->setPixmap(QPixmap());

        }
    }
}
bool LaunchpadButton::getEditMode()
{
    return m_editMode;
}
void LaunchpadButton::setSize(unsigned int width, unsigned int height)
{
    m_width = width;
    m_height = height;
    for(size_t i=0; i<m_buttons.size(); ++i)
    {
        m_buttons[i]->setSize_internal(width, height);
    }
}
void LaunchpadButton::setSize_internal(unsigned int width, unsigned int height)
{
    setMinimumSize(width, height);
    setMaximumSize(width, height);
}

void LaunchpadButton::onButtonPress()
{
    if(!m_sound)
        return;
    if(m_editMode && !m_settingsWindow->isVisible())
    {
        m_settingsWindow->setSound(m_sound);
        m_settingsWindow->show();
    }
    else if(!m_editMode)
    {
        m_sound->play();
    }
}
void LaunchpadButton::onSoundDeleted()
{
    m_sound = nullptr;
}
void LaunchpadButton::onSoundNameChanged(const std::string &name)
{
    setText(name.c_str());
    //m_label->setText(name.c_str());
}
