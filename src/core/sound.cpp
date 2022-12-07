#include "sound.h"
#include <QCoreApplication>

#ifdef QT_DEBUG
#define PERFORMANCE_TEST
#endif

#ifdef PERFORMANCE_TEST
#include "performanceTimer.h"
#endif


#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
QAudioOutput *Sound::m_output = nullptr;
#endif


size_t Sound::m_stackSize = 10;
Sound::Sound()
    : QObject()
    , ISerializable()
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    if(!m_output)
        m_output = new QAudioOutput;
#else
   // m_output = new QAudioOutput;
#endif
    //for(size_t i=0; i<m_player.size(); ++i)
    //    connect(m_player[i],&QMediaPlayer::mediaStatusChanged,this,&Sound::onMediaStatusChanged);
    m_buttonPos.x = 0;
    m_buttonPos.y = 0;
    //setStackSize(1);
    setPlaymode(Playmode::Music);
    #if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
    //m_player.setAudioOutput(m_output);

    #else
    m_loops = 0;

    #endif
    setVolume(1);
    //m_soundIsPlaying = false;
}
Sound::Sound(const Sound &other)
    : QObject()
    , ISerializable(other)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    if(!m_output)
        m_output = new QAudioOutput;
#else
    //m_output = new QAudioOutput;
#endif
    setPlaymode(Playmode::Music);
    //m_player.setAudioOutput(m_output);
    //connect(&m_player,&QMediaPlayer::mediaStatusChanged,this,&Sound::onMediaStatusChanged);
    this->operator=(other);
}
Sound::Sound(const SoundSource &source)
    : QObject()
    , ISerializable()
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    if(!m_output)
        m_output = new QAudioOutput;
#else
   // m_output = new QAudioOutput;
#endif
    //connect(&m_player,&QMediaPlayer::mediaStatusChanged,this,&Sound::onMediaStatusChanged);
    m_buttonPos.x = 0;
    m_buttonPos.y = 0;
    m_source = source;
    setPlaymode(Playmode::Music);
    #if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)

    //m_player.setAudioOutput(m_output);
    #else
    m_loops = 0;

    #endif
    //m_soundIsPlaying = false;
}
Sound::~Sound()
{

}
const Sound &Sound::operator=(const Sound &other)
{
    ISerializable::operator=(other);
    m_name = other.m_name;
    if(other.m_source.isValid())
        setSource(other.m_source);
    m_buttonPos = other.m_buttonPos;
    setPlaybackSpeed(other.getPlaybackSpeed());
    setLoops(other.getLoops());
    setVolume(other.getVolume());
    return *this;
}

/*const QAudioOutput &Sound::getAudioOutput()
{
    return *m_output;
}
*/
const SoundSource &Sound::getSource() const
{
    return m_source;
}
float Sound::getVolume() const
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    return m_volume;
#else
    return m_player[0].output->volume();
#endif
}
float Sound::getPlaybackSpeed() const
{
    return (float)m_player[0].player->playbackRate();
}
int Sound::getLoops() const
{
    #if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
        return m_player[0].player->loops();
    #else
        return m_loops;
    #endif
}
const std::string &Sound::getName() const
{
    return m_name;
}
bool Sound::soundIsPlaying() const
{
    bool isPlaying = false;
    for(size_t i=0; i<m_player.size(); ++i)
        isPlaying |= m_player[i].currentlyPlaying;
    return isPlaying;
}
QJsonObject Sound::save() const
{
    return combine(ISerializable::save(),
    QJsonObject
    {
        {"name", m_name.c_str()},
        {"loops", getLoops()},
        {"volume", getVolume()},
        {"speed", getPlaybackSpeed()},
        {"source", m_source.getAbsolutePath().c_str()},
        {"x",m_buttonPos.x},
        {"y",m_buttonPos.y},
        {"playmode",m_playMode}
    });
}
bool Sound::read(const QJsonObject &reader)
{

#ifdef PERFORMANCE_TEST
    PerformanceTimer timer(true);
    DEBUG("        Extract reader... ");
#endif
    ISerializable::read(reader);
    bool success = true;

    int loops = 0;
    float volume = 0.5;
    float speed = 1;
    int mode = Playmode::Music;
    std::string source;
    success &= extract(reader,m_name,"name");
    success &= extract(reader,loops,"loops");
    success &= extract(reader,volume,"volume");
    success &= extract(reader,speed,"speed");
    success &= extract(reader,source,"source");
    success &= extract(reader,m_buttonPos.x,"x");
    success &= extract(reader,m_buttonPos.y,"y");
    extract(reader, mode, "playmode");
#ifdef PERFORMANCE_TEST
    DEBUGLN("      fertig "<<timer.getRuntimeMsStr().c_str());

#endif


    if(!success)
    {
        WARNING("Kann Sound "<<m_name.c_str()<<" nicht korrekt laden.");
        return false;
    }
#ifdef PERFORMANCE_TEST
    {
    PerformanceTimer timer1(true);
    DEBUG("        setPlaymode... ");
#endif
    setPlaymode((Playmode)mode);
#ifdef PERFORMANCE_TEST
    DEBUGLN("      fertig "<<timer1.getRuntimeMsStr().c_str());
    }
#endif

#ifdef PERFORMANCE_TEST
    {
    PerformanceTimer timer1(true);
    DEBUG("        setLoops... ");
#endif
    setLoops(loops);
#ifdef PERFORMANCE_TEST
    DEBUGLN("      fertig "<<timer1.getRuntimeMsStr().c_str());
    }
#endif

#ifdef PERFORMANCE_TEST
    {
    PerformanceTimer timer1(true);
    DEBUG("        setVolume... ");
#endif
    setVolume(volume);
#ifdef PERFORMANCE_TEST
    DEBUGLN("      fertig "<<timer1.getRuntimeMsStr().c_str());
    }
#endif

#ifdef PERFORMANCE_TEST
    {
    PerformanceTimer timer1(true);
    DEBUG("        setPlaybackSpeed... ");
#endif
    setPlaybackSpeed(speed);
#ifdef PERFORMANCE_TEST
    DEBUGLN("      fertig "<<timer1.getRuntimeMsStr().c_str());
    }
#endif

#ifdef PERFORMANCE_TEST
    {
    PerformanceTimer timer1(true);
    DEBUG("        setSource... ");
#endif
    m_source.setAbsolutePath(source);
    setSource(m_source);
#ifdef PERFORMANCE_TEST
    DEBUGLN("      fertig "<<timer1.getRuntimeMsStr().c_str());
    }
#endif





    return true;
}
void Sound::postLoad()
{

}

void Sound::play()
{

    if(!m_source.isValid())
    {
        WARNING("Path: \""<<m_source.getAbsolutePath().c_str()<<"\" is not valid");
        return;
    }

    switch(m_playMode)
    {
        case Playmode::Music:
        {
            playMusic();
            break;
        }
        case Playmode::Stackable:
        {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
            if(m_loops == Loops::Infinite)
#else
            if(m_player[0].player->loops() == Loops::Infinite)
#endif
                playMusic();
            else
                playStacked();
            break;
        }
    }
}
void Sound::playMusic()
{
    if(m_player[0].currentlyPlaying)
    {
        stop();
        return;
    }
    m_player[0].currentlyPlaying = true;
#ifdef DBG_SOUND
DEBUGLN("Starting mono sound: \""<<m_source.getAbsolutePath().c_str()<<"\"");
#endif
    m_player[0].player->play();
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    ++m_player[0].loopCounter;
#endif
}
void Sound::playStacked()
{
    for(size_t i=0; i<m_player.size(); ++i)
    {
        if(!m_player[i].currentlyPlaying)
        {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
            ++m_player[i].loopCounter;
#endif
            m_player[i].currentlyPlaying = true;
#ifdef DBG_SOUND
DEBUGLN("Starting stacked sound["<<i<<"]: \""<<m_source.getAbsolutePath().c_str()<<"\"");
#endif
            m_player[i].player->play();
            break;
        }
    }
}
void Sound::pause()
{
    for(size_t i=0; i<m_player.size(); ++i)
        m_player[i].player->pause();
    emit onPlaybackPaused();
}
void Sound::stop()
{
    for(size_t i=0; i<m_player.size(); ++i)
    {
        m_player[i].player->stop();
        m_player[i].currentlyPlaying = false;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        m_player[i].loopCounter = 0;
#endif
    }
    emit onPlaybackStopped();
}

void Sound::setSource(const SoundSource &source)
{
    m_source = source;
    if(m_source.getAbsolutePath() == "")
        return;
    if(!m_source.isValid())
    {
        WARNING("Path: \""<<m_source.getAbsolutePath().c_str()<<"\" is not valid, trying relative path...\n");
        SoundSource testSrc(QCoreApplication::applicationDirPath().toStdString()+ "\\"+source.getAbsolutePath());
        if(!testSrc.isValid())
        {
            WARNING("Path: \""<<testSrc.getAbsolutePath().c_str()<<"\" is not valid\n");
            return;
        }
        m_source = testSrc;
    }
#if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
    QUrl url = QUrl::fromLocalFile(m_source.getAbsolutePath().c_str());
    for(size_t i=0; i<m_player.size(); ++i)
        m_player[i].player->setSource(url);
#else
    for(size_t i=0; i<m_player.size(); ++i)
        m_player[i].player->setMedia(QUrl::fromLocalFile(m_source.getAbsolutePath().c_str()));
#endif
}
void Sound::setVolume(float volume)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    m_volume = volume;
    qreal linearVolume = QAudio::convertVolume(volume, QAudio::LogarithmicVolumeScale,
                                                       QAudio::LinearVolumeScale);
    for(size_t i=0; i<m_player.size(); ++i)
        m_player[i].player->setVolume(qRound(linearVolume*100));
#else
    for(size_t i=0; i<m_player.size(); ++i)
        m_player[i].output->setVolume(volume);
#endif
}
void Sound::setPlaybackSpeed(float speed)
{
    for(size_t i=0; i<m_player.size(); ++i)
        m_player[i].player->setPlaybackRate((qreal)speed);
}
void Sound::setLoops(int count)
{
    #if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
    for(size_t i=0; i<m_player.size(); ++i)
        m_player[i].player->setLoops(count);
    #else
    m_loops = count;
    #endif
}
void Sound::setName(const std::string &name)
{
    m_name = name;
    emit onNameChanged(m_name);
}
void Sound::setButtonCoord(int x, int y)
{
    m_buttonPos.x = x;
    m_buttonPos.y = y;
}

void Sound::setButtonCoord(const Coord &pos)
{
    m_buttonPos = pos;
}

void Sound::setStackSize(size_t size)
{
    if(size == 0)
        size = 1;
    if(m_player.size() == size)
        return;


    if(m_player.size() > size)
    {
        std::vector<Player> players = m_player;
/*#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        std::vector<int> loopsCount = m_loopsCounter;
        m_loopsCounter.clear();
#endif*/
        m_player.clear();
        size_t removed = 0;
        while(players.size()-removed > size)
        {
            delete players[players.size()-1].player;
            players[players.size()-1].player = nullptr;
            ++removed;
        }
        for(size_t i=0; i<players.size(); ++i)
            if(players[i].player)
            {
                m_player.push_back(players[i]);
/*#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
                m_loopsCounter.push_back(loopsCount[i]);
#endif*/
            }
        return;
    }
    m_player.reserve(size);
    while(m_player.size() < size)
    {
        Player player;
#ifdef PERFORMANCE_TEST
        PerformanceTimer timer(true);
        DEBUG("      new QMediaPlayer... ");
#endif
        player.player = new QMediaPlayer;
#ifdef PERFORMANCE_TEST
        DEBUGLN("      fertig "<<timer.getRuntimeMsStr().c_str());
#endif


        player.currentlyPlaying = false;
#if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
        player.output = new QAudioOutput;
        player.player->setAudioOutput(player.output);
#endif
        connect(player.player, &QMediaPlayer::mediaStatusChanged, this, &Sound::onMediaStatusChanged);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        //m_loopsCounter.push_back(0);
        player.loopCounter = 0;
#endif
        m_player.push_back(player);

    }


    stop();
    setSource(m_source);
}
Sound::Playmode Sound::getPlaymode() const
{
    return m_playMode;
}
void Sound::setPlaymode(Playmode mode)
{
    m_playMode = mode;
    switch(m_playMode)
    {
        case Playmode::Music:
        {
            setStackSize(1);
            break;
        }
        case Playmode::Stackable:
        {
            setStackSize(m_stackSize);
            break;
        }
        default:
#ifdef DBG_SOUND
            DEBUGLN("No such playmode: "<<mode);
#endif
    }
}

const Coord &Sound::getButtonCoord() const
{
    return m_buttonPos;
}
void Sound::setDefaultStackSize(size_t size)
{
    if(size < 2)
        size = 2;
    m_stackSize = size;
}
size_t Sound::getDefaultStackSize()
{
    return m_stackSize;
}

void Sound::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    size_t currentPlayerIndex = 0;
    QMediaPlayer *currentPlayer = dynamic_cast<QMediaPlayer*>(QObject::sender());
    if(currentPlayer)
    {
        for(size_t i=0; i<m_player.size(); ++i)
            if(m_player[i].player == currentPlayer)
            {
                currentPlayerIndex = i;
            }
    }
    switch(status)
    {
        case QMediaPlayer::MediaStatus::NoMedia:
        {
#ifdef DBG_SOUND
            DEBUGLN("Sound["<<currentPlayerIndex<<"]: NoMedia");
#endif
            break;
        }
        case QMediaPlayer::MediaStatus::LoadingMedia:
        {
            break;
        }
        case QMediaPlayer::MediaStatus::LoadedMedia:
        {
            break;
        }
        case QMediaPlayer::MediaStatus::StalledMedia:
        {
            break;
        }
        case QMediaPlayer::MediaStatus::BufferingMedia:
        {

            break;
        }
        case QMediaPlayer::MediaStatus::BufferedMedia:
        {
            break;
        }
        case QMediaPlayer::MediaStatus::EndOfMedia:
        {

            m_player[currentPlayerIndex].currentlyPlaying = false;
#ifdef DBG_SOUND
            DEBUGLN("Sound["<<currentPlayerIndex<<"]: \""<<m_source.getAbsolutePath().c_str()<<"\" finished playback");
#endif
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)

            if(m_loops == Loops::Infinite)
            {
                play();
                return;
            }
            if(currentPlayer)
            {
                if(m_player[currentPlayerIndex].loopCounter >= m_loops)
                {
                    m_player[currentPlayerIndex].loopCounter = 0;
                    emit onPlaybackFinished();
                }
                else
                {
                    play();
                }
            }
#else
            if(!soundIsPlaying())
                emit onPlaybackFinished();

#endif
            break;
        }
        case QMediaPlayer::MediaStatus::InvalidMedia:
        {
#ifdef DBG_SOUND
            DEBUGLN("Sound["<<currentPlayerIndex<<"]: InvalidMedia");
#endif
            break;
        }
    }
}
