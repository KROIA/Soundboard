// Ersetzt das:
// #ifndef SOUND_H
// #define SOUND_H
// ...
// #endif
#pragma once

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "soundsource.h"
#include "debug.h"
#include "xmlSaveable.h"

// Enable debug informations for this class
#define DBG_SOUND


/*! \class Sound
    \brief Class to play sound

    This class will play the sound which
    was defined in the given SoundSource
*/
class Sound :   public QObject, public XmlSaveable
{
        Q_OBJECT
    public:
        Sound();

        /**
         * Constructor
         * @see setSource(...)
         * @param source The source object which contains the path to
         *               the .mp3 file
         */
        Sound(const SoundSource &source);
        ~Sound();


        /**
         * getSource()
         * @return Returns the source object to the .mp3 file
         */
        const SoundSource &getSource() const;

        /**
         * getVolume()
         * @return Returns the volume of the sound
         */
        float getVolume() const;

        /**
         * getPlaybackSpeed()
         * @return Returns the playback speed of the sound
         */
        float getPlaybackSpeed() const;

        /**
         * getLoops()
         * @return Returns the amount of loops the sound will play
         */
        int getLoops() const;

        /**
         * getName()
         * @return Returns the name of the sound
         */
        const std::string &getName() const;


        /**
         * save(...)
         * @brief Implementation of XmlSaveable
         * @param writer QXmlStreamWriter which will save the file
         */
        void save(QXmlStreamWriter *writer) override;

        /**
         * load(...)
         * @brief Implementation of XmlSaveable
         * @param reader QXmlStreamReader which will read from the file
         */
        void load(QXmlStreamReader *reader) override;

    signals:
        /**
         * onPlaybackFinished()
         * @brief Will be called if the playback is finished
         */
        void onPlaybackFinished();

        /**
         * onPlaybackPaused()
         * @brief Will be called if the playback is paused
         */
        void onPlaybackPaused();

        /**
         * onPlaybackStopped()
         * @brief Will be called if the playback is stopped
         */
        void onPlaybackStopped();



    public slots:
        /**
         * play()
         * @brief Will start the playback
         */
        void play();

        /**
         * pause()
         * @brief Will pause the current playback
         */
        void pause();

        /**
         * stop()
         * @brief Will stop the current playback
         */
        void stop();

        /**
         * setSource(...)
         * @param source The source object which contains the path to
         *               the .mp3 file
         */
        void setSource(const SoundSource &source);

        /**
         * setVolume(...)
         * @param volume The volume of the playback.
         *               Range [0 - 1]
         */
        void setVolume(float volume);

        /**
         * setPlaybackSpeed(...)
         * @param speed The speed of the playback.
         *              Default = 1, x<1 = faster
         */
        void setPlaybackSpeed(float speed);

        /**
         * setLoops(...)
         * @param count The amount for how often the playback will be repeated.
         *              QMediaPlayer::Infinite for infinite playback
         */
        void setLoops(int count);

        /**
         * setName(...)
         * @param name The name of the Sound, can be any Text
        */
        void setName(const std::string &name);

    private slots:
        void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
    protected:

    private:
        std::string m_name;
        SoundSource  m_source;
        QMediaPlayer m_player;
        QAudioOutput m_output;
};
