#pragma once

#include "database.h"
#include "sound.h"

class SoundboardDatabase
{
public:
    SoundboardDatabase();
    ~SoundboardDatabase();

    bool load(const std::string &filePath);
    bool save(const std::string &filePath) const;
    bool save() const;

    Sound* getSound(const std::string &id) const;
    std::vector<Sound*> getSounds() const;
    Sound* addSound(const Sound &sound);

private:
    Database m_database;
    std::string m_databaseFile;
};
