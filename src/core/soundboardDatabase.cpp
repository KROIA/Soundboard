#include "soundboardDatabase.h"


DATABASE_USE_OBJECT(Sound)

SoundboardDatabase::SoundboardDatabase()
{
    m_database.defineSaveableObject<Sound>();


}
SoundboardDatabase::~SoundboardDatabase()
{
    //if(m_databaseFile.size())
    //    save();
}

bool SoundboardDatabase::load(const std::string &filePath)
{
    m_databaseFile = filePath;
    return m_database.load(filePath);
}
bool SoundboardDatabase::save(const std::string &filePath) const
{
    return m_database.save(filePath);
}
bool SoundboardDatabase::save() const
{
    if(m_databaseFile.size() == 0)
    {
        CRITICAL("Database kann nicht gespeichert werden, da die Ausgabedatei nicht definiert ist.");
        return false;
    }
    return m_database.save(m_databaseFile);
}
Sound* SoundboardDatabase::getSound(const std::string &id) const
{
    return m_database.getObject<Sound>(id);
}
std::vector<Sound*> SoundboardDatabase::getSounds() const
{
    return m_database.getObjects<Sound>();
}
Sound* SoundboardDatabase::addSound(const Sound &sound)
{
    Sound* copy = sound.clone();
    if(!m_database.addObject(copy))
    {
        delete copy;
        return nullptr;
    }
    return copy;
}
