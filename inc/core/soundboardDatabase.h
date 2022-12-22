#pragma once

#include "database.h"
#include "sound.h"


/**
 * \author Alex Krieg
 * \date   12.10.2022
 *
 * \brief The SoundboardDatabase class
 * \details This is the project specific database wrapper
 *          It helps to manage the sound resources of the project
 *
 */
class SoundboardDatabase
{
public:
    SoundboardDatabase();
    ~SoundboardDatabase();

    /**
     * \brief Loads a saved json file
     * \param filePath to the file
     * \return true if the loading was successful
     *         false if the file can't be loaded
     */
    static bool load(const std::string &filePath);

    /**
     * \brief Saves all sounds to a json file
     * \param filePath to the target file
     * \return true if the saving was successful
     *         false if the file can't be written
     */
    static bool save(const std::string &filePath);

    /**
     * \brief Saves all sounds to a json file
     * \details The path to the file must already be given using \see load(...) or \see save(...)
     * \return true if the saving was successful
     *         false if the file can't be written
     */
    static bool save();

    /**
     * \brief Gets the sound with the given id
     * \param id to the searched sound
     * \return pointer to the found sound
     *         nullptr if no sound with such a id was found
     */
    static Sound* getSound(const std::string &id);

    /**
     * \return a vector of all sounds
     */
    static std::vector<Sound*> getSounds();

    /**
     * \return the sounds count
     */
    static size_t getSoundsCount();

    /**
     * \brief Adds a sound as a copy of the given sound
     * \param sound to copy from
     * \return pointer to the instantiated Sound object, stored in the database
     */
    static Sound* addSound(const Sound &sound);

    /**
     * \brief Removes a given sound
     * \details Removing does not delete the object
     * \param obj which shuld be removed
     * \return true if the object was successfully removed
     *         false if the object was not found in the database
     */
    static bool removeSound(Sound *sound);

private:
    static SoundboardDatabase m_instance;
    Database m_database;
    std::string m_databaseFile;
};

/*#define SD_INSTANCE_RET(ret)\
if(!m_instance) \
{ \
    SD_NO_INSTANCE; \
return ret;\
}
#define SD_INSTANCE_VOID \
if(!m_instance) \
{ \
    SD_NO_INSTANCE; \
    return;\
}

#define SD_NO_INSTANCE qDebug() << __PRETTY_FUNCTION__ << " No instance of type SoundboardDatabase";
*/
