#pragma once

#include <string>
#include <filesystem>
#include <algorithm>
#include "debug.h"

/*! \class SoundSource
    \brief Class to handle audiofiles

    This class contains the path to
    the audio files on the device.
*/
class SoundSource
{
    public:
        SoundSource();

        /**
         * Constructor
         * @see setAbsolutePath(...)
         * @param absolutePath The full path to the .mp3 file
         */
        SoundSource(const std::string &absolutePath);

        /**
         * Constructor
         * @see setRootPath(...)
         * @see setRelativePath(...)
         * @param root The path to a directory, that contains the .mp3 file in some
         *             folder structure
         * @param relativePath The second part of the path to the .mp3 file.
         *                     <root>/<relativePath> = <absolutePath>
         */
        SoundSource(const std::string &root, const std::string &relativePath);
        ~SoundSource();

        /**
         * setAbsolutePath(...)
         * @param absolutePath The full path to the .mp3 file
         */
        void setAbsolutePath(const std::string absolutePath);

        /**
         * setRootPath(...)
         * @param root The path to a directory, that contains the .mp3 file in some
         *             folder structure
         */
        void setRootPath(const std::string &path);

        /**
         * setRelativePath(...)
         * @param relativePath The second part of the path to the .mp3 file.
         *                     <root>/<relativePath> = <absolutePath>
         */
        void setRelativePath(const std::string &path);

        /**
         * isValid()
         * @return true  if: The <absolutePath> is an existing .mp3 file
         *         false if: The <absolutePath> does not exist or is not a file
         */
        bool isValid() const;

        /**
         * getRootPath()
         * @return root folder to the .mp3 file
         */
        const std::string &getRootPath() const;

        /**
         * getRelativePath()
         * @return relative path containing the filename to the .mp3 file
         */
        const std::string &getRelativePath() const;

        /**
         * getAbsolutePath()
         * @return absolute path containing the filename to the .mp3 file
         */
        std::string getAbsolutePath() const;

        /**
         * save(...)
         * @brief Implementation of XmlSaveable
         * @param writer QXmlStreamWriter which will save the file
         */
     //   void save(QXmlStreamWriter *writer) override;

        /**
         * load(...)
         * @brief Implementation of XmlSaveable
         * @param reader QXmlStreamReader which will read from the file
         */
     //   void load(QXmlStreamReader *reader) override;

    protected:

    private:
        std::string m_rootPath;
        std::string m_relativePath;

};
