#pragma once

#include <unordered_map>
#include <vector>
#include "sound.h"
#include "debug.h"


class Database
{
    public:
        Database();
        ~Database();

        bool load(const std::string &jsonFile);
        bool save(const std::string &jsonFile);

        bool add(ISerializable* obj);
        bool remove(ISerializable* obj);
        bool exists(ISerializable* obj);
        size_t getIndex(ISerializable *obj);
        size_t getObjectCount() const;

        Sound *getSound(const std::string &id);

        const static size_t npos = -1;
    private:
        void instantiateDatabase(const QJsonArray &objs);
        void instantiateObject(const QJsonObject &obj);
        void clear();

        template<typename T>
        bool defineSaveableObject();

        template<typename T>
        bool addToMapInternal(     std::unordered_map<std::string, T*> &map,
                                   ISerializable *obj);
        template<typename T>
        bool removeFromMapInternal(std::unordered_map<std::string, T*> &map,
                                   ISerializable *obj);

        std::unordered_map<std::string, ISerializable*> m_saveableObjectTypes;

        std::vector<ISerializable*> m_objects;


        std::unordered_map<std::string, Sound*> m_sounds;

};
