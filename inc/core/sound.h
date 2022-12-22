// Ersetzt das:
// #ifndef SOUND_H
// #define SOUND_H
// ...
// #endif
#pragma once
#include <string>
#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "soundsource.h"
#include "ISerializable.h"

// Enable debug informations for this class
#define DBG_SOUND

struct Coord
{
    int x;
    int y;
};


/*! \class Sound
    \brief Class to play sound

    This class will play the sound which
    was defined in the given SoundSource
*/
class Sound :   public QObject, public ISerializable
{
        Q_OBJECT

    public:
        enum Playmode
        {
            Music,
            Stackable
        };
        enum Loops
        {
            Infinite = -1,
            Once = 1
        };

        Sound();
        Sound(const Sound &other);

        /**
         * \brief Constructor
         * \see setSource(...)
         * \param source The source object which contains the path to
         *               the .mp3 file
         */
        Sound(const SoundSource &source);
        ~Sound();

        const Sound &operator=(const Sound &other);


        /**
         * \return Returns the source object to the .mp3 file
         */
        const SoundSource &getSource() const;

        /**
         * \return Returns the volume of the sound
         */
        float getVolume() const;

        /**
         * \return Returns the playback speed of the sound
         */
        float getPlaybackSpeed() const;

        /**
         * \return Returns the amount of loops the sound will play
         */
        int getLoops() const;

        /**
         * \return Returns the name of the sound
         */
        const std::string &getName() const;

        /**
         * \return true if the sound is currently playing
         */
        bool soundIsPlaying() const;

        /**
         * \return the current playMode
         */
        Playmode getPlaymode() const;



        IMPLEMENT_ISERIALIZABLE_CONST_FUNC(Sound)

        QJsonObject save() const override; //!< \see ISerializable::save()
        bool read(const QJsonObject &reader) override; //!< \see ISerializable::read()
        void postLoad() override; //!< \see ISerializable::postLoad()

        /**
         * \brief getButtonCoord
         * \return position in the launchpad button array
         */
        const Coord &getButtonCoord() const;

        /**
         * \brief Sets the default stack size of all sounds
         * \param size > 2
         */
        static void setDefaultStackSize(size_t size);

        /**
         * \return the default stacksize of all sounds
         */
        static size_t getDefaultStackSize();

    signals:
        /**
         * onPlaybackFinished()
         * \brief Will be called if the playback is finished
         */
        void onPlaybackFinished();

        /**
         * onPlaybackPaused()
         * \brief Will be called if the playback is paused
         */
        void onPlaybackPaused();

        /**
         * onPlaybackStopped()
         * \brief Will be called if the playback is stopped
         */
        void onPlaybackStopped();

        /**
         * \brief onNameChanged will be emitted after the name of the wound was changed
         */
        void onNameChanged(const std::string &name);




    public slots:
        /**
         * play()
         * \brief Will start the playback
         */
        void play();

        /**
         * pause()
         * \brief Will pause the current playback
         */
        void pause();

        /**
         * stop()
         * \brief Will stop the current playback
         */
        void stop();

        /**
         * setSource(...)
         * \param source The source object which contains the path to
         *               the .mp3 file
         */
        void setSource(const SoundSource &source);

        /**
         * setVolume(...)
         * \param volume The volume of the playback.
         *               Range [0 - 1]
         */
        void setVolume(float volume);

        /**
         * setPlaybackSpeed(...)
         * \param speed The speed of the playback.
         *              Default = 1, x<1 = faster
         */
        void setPlaybackSpeed(float speed);

        /**
         * setLoops(...)
         * \param count The amount for how often the playback will be repeated.
         *              QMediaPlayer::Infinite for infinite playback
         */
        void setLoops(int count);

        /**
         * setName(...)
         * \param name The name of the Sound, can be any Text
        */
        void setName(const std::string &name);

        /**
         * \brief Position in the launchpad button array
         * \param x position in the array
         * \param y position in the array
         */
        void setButtonCoord(int x, int y);

        /**
         * \brief Position in the launchpad button array
         * \param pos position in the array
         */
        void setButtonCoord(const Coord &pos);

        /**
         * \brief Sets the stacksize of the sound
         * \param size > 1
         */
        void setStackSize(size_t size);

        /**
         * \brief Sets the playmode of the sound
         * \param mode
         */
        void setPlaymode(Playmode mode);


    private slots:
        void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
    protected:

    private:
        void playMusic();
        void playStacked();

        std::string  m_name;
        Coord m_buttonPos;
        Playmode m_playMode;

        SoundSource  m_source;
        struct Player
        {
            QMediaPlayer* player;
            bool currentlyPlaying;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
            int loopCounter;
#else
            QAudioOutput *output;
#endif
        };

        std::vector<Player> m_player;
        #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        int m_loops;
        //std::vector<int> m_loopsCounter;
        float m_volume;
        static QAudioOutput *m_output;
        #endif
       // int m_soundIsPlaying;

        static size_t m_stackSize;

};
