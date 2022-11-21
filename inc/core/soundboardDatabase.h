#pragma once

#include "database.h"
#include "sound.h"
#include <QDebug>

class SoundboardDatabase
{
public:
    SoundboardDatabase();
    ~SoundboardDatabase();

    static bool load(const std::string &filePath);
    static bool save(const std::string &filePath);
    static bool save();

    static Sound* getSound(const std::string &id);
    static std::vector<Sound*> getSounds();
    static size_t getSoundsCount();
    static Sound* addSound(const Sound &sound);
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
