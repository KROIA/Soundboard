#include "LaunchpadButton.h"
#include <QVBoxLayout>
#include <QSpacerItem>
#include "soundboardDatabase.h"


bool LaunchpadButton::m_editMode = false;
std::vector<LaunchpadButton*> LaunchpadButton::m_buttons;
UI_SoundSettings *LaunchpadButton::m_settingsWindow = nullptr;
unsigned int LaunchpadButton::m_width = 50;
unsigned int LaunchpadButton::m_height = 50;

LaunchpadButton::LaunchpadButton(QWidget *parent)
    :   QPushButton(parent)
{
    m_sound = nullptr;
    m_thisOwnedSound = nullptr;

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
    setSound(nullptr);
    setEtitMode_internal();
    QFont f = QPushButton::font();
    f.setPointSize(6);
    QPushButton::setFont(f);
}
LaunchpadButton::~LaunchpadButton()
{
    if(m_thisOwnedSound)
    {
        deleteThisOwnedSound();
    }

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
        if(m_thisOwnedSound)
        {
            deleteThisOwnedSound();
        }
    }
    m_sound = sound;
    if(m_sound)
    {
        m_sound->setButtonCoord(m_buttonPos);
        connect(m_sound, &QObject::destroyed, this, &LaunchpadButton::onSoundDeleted);
        connect(m_sound, &Sound::onNameChanged, this, &LaunchpadButton::onSoundNameChanged);

        if(!m_sound->getSource().isValid())
        {
            //setEnabled(false);
            onSoundNameChanged("Sound\nFile\nnot\nfound");
        }
        else
        {
            //setEnabled(true);
            onSoundNameChanged(m_sound->getName());
        }
    }
    else
    {
        //setEnabled(false);
        onSoundNameChanged("Sound\nnot\ndefined");
    }
    setEtitMode_internal();
}
Sound *LaunchpadButton::getSound() const
{
    return m_sound;
}

void LaunchpadButton::setArrayPos(const Coord &pos)
{
    m_buttonPos = pos;
    //setToolTip("Pos: x="+QString::number(m_buttonPos.x)+" y="+QString::number(m_buttonPos.y));
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
    for(size_t i=0; i<m_buttons.size(); ++i)
    {
        m_buttons[i]->setEtitMode_internal();
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
void LaunchpadButton::createNewSound()
{
    if(m_thisOwnedSound)
    {
        deleteThisOwnedSound();
    }
    Sound s;
    s.setName("Neuer Sound");
    Sound *tmp = SoundboardDatabase::addSound(s);
    setSound(tmp);
    m_thisOwnedSound = tmp;
}
void LaunchpadButton::deleteThisOwnedSound()
{
    SoundboardDatabase::removeSound(m_thisOwnedSound);
    delete m_thisOwnedSound;
    m_thisOwnedSound = nullptr;
    m_sound = nullptr;
}
void LaunchpadButton::setEtitMode_internal()
{
    if(m_editMode)
    {
        setEnabled(true);
        if(m_sound)
            m_sound->stop();
        m_label->setPixmap(QPixmap(":/icons/settings.png").scaledToWidth(0.5f*m_width));
    }
    else
    {
        if(m_sound)
        {
            if(m_sound->getSource().getAbsolutePath() == "")
            {
                delete m_sound;
                m_sound = nullptr;
            }
        }

        if(m_sound)
        {
            setEnabled(m_sound->getSource().isValid());
            onSoundNameChanged(m_sound->getName());
        }
        else
        {
            setEnabled(false);
            onSoundNameChanged("Sound\nnot\ndefined");
        }
        m_label->setPixmap(QPixmap());
    }
}
void LaunchpadButton::setSize_internal(unsigned int width, unsigned int height)
{
    setMinimumSize(width, height);
    setMaximumSize(width, height);
}

void LaunchpadButton::onButtonPress()
{
    if(m_editMode && !m_settingsWindow->isVisible())
    {
        if(!m_sound)
            createNewSound();
        m_settingsWindow->setSound(m_sound);
        m_settingsWindow->show();
    }
    else if(!m_editMode)
    {
        if(m_sound)
        {
            /*if(m_sound->soundIsPlaying())
                m_sound->stop();
            else*/

            m_sound->play();
        }
    }
}
void LaunchpadButton::onSoundDeleted()
{
    m_sound = nullptr;
    setSound(nullptr);
}
void LaunchpadButton::onSoundNameChanged(const std::string &name)
{
    setText(name.c_str());
    //m_label->setText(name.c_str());
}
