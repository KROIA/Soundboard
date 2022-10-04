#ifndef UI_SOUND_H
#define UI_SOUND_H

#include <QWidget>

#include <string>
#include <vector>

#include "sound.h"
#include "debug.h"

#include "xmlSaveable.h"

namespace Ui {
class UI_Sound;
}

class UI_Sound : public QWidget, public XmlSaveable
{
        Q_OBJECT

    public:
        explicit UI_Sound(QWidget *parent = nullptr);
        ~UI_Sound();

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
        unsigned int getLoops() const;

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
         * toggleRepeat()
         * @brief Will toggle the autorepeat mode
         */
        void toggleRepeat(bool toggleOn);

        /**
         * isRepeating()
         * @return true  If the sound is in loop mode
         *         false If the sound is not in loop mode
         */
        bool isRepeating() const;

        /**
         * setName(...)
         * @param name The name of the Sound, can be any Text
        */
        void setName(const std::string &name);

    private:
        Ui::UI_Sound *ui;
        Sound m_sound;


};

#endif // UI_SOUND_H
