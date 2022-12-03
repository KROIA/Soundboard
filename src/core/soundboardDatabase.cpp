#include "soundboardDatabase.h"


DATABASE_USE_OBJECT(Sound)

SoundboardDatabase SoundboardDatabase::m_instance;
SoundboardDatabase::SoundboardDatabase()
{
    //m_instance = this;
    m_database.defineSaveableObject<Sound>();


}
SoundboardDatabase::~SoundboardDatabase()
{
    //m_instance = nullptr;
    //if(m_databaseFile.size())
    //    save();
}

bool SoundboardDatabase::load(const std::string &filePath)
{
    //SD_INSTANCE_RET(false);
    m_instance.m_databaseFile = filePath;
    return m_instance.m_database.load(filePath);
}
bool SoundboardDatabase::save(const std::string &filePath)
{
    //SD_INSTANCE_RET(false);
    return m_instance.m_database.save(filePath);
}
bool SoundboardDatabase::save()
{
    //SD_INSTANCE_RET(false);
    if(m_instance.m_databaseFile.size() == 0)
    {
        CRITICAL("Database kann nicht gespeichert werden, da die Ausgabedatei nicht definiert ist.");
        return false;
    }
    return m_instance.m_database.save(m_instance.m_databaseFile);
}
Sound* SoundboardDatabase::getSound(const std::string &id)
{
   // SD_INSTANCE_RET(nullptr);
    return m_instance.m_database.getObject<Sound>(id);
}
std::vector<Sound*> SoundboardDatabase::getSounds()
{
   // SD_INSTANCE_RET({});
    return m_instance.m_database.getObjects<Sound>();
}
size_t SoundboardDatabase::getSoundsCount()
{
   // SD_INSTANCE_RET(0);
    return m_instance.m_database.getObjectCount<Sound>();
}
Sound* SoundboardDatabase::addSound(const Sound &sound)
{
  //  SD_INSTANCE_RET(nullptr);
    Sound* copy = sound.clone();
    if(!m_instance.m_database.addObject(copy))
    {
        delete copy;
        return nullptr;
    }
    return copy;
}
bool SoundboardDatabase::removeSound(Sound *sound)
{
  //  SD_INSTANCE_RET(false);
    return m_instance.m_database.removeObject(sound);
}
