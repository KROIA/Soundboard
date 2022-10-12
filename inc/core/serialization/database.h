#pragma once

#include <unordered_map>
#include <vector>
#include "databaseObject.h"
#include "debug.h"


class Database
{
    public:
        Database();
        ~Database();
        template<typename T>
        bool defineSaveableObject();

        bool load(const std::string &jsonFile);
        bool save(const std::string &jsonFile) const;

        bool addObject(ISerializable* obj);
        bool removeObject(ISerializable* obj);
        bool removeObject(const std::string &id);
        bool objectExists(ISerializable* obj) const;
        bool objectExists(const std::string &id) const;
        //size_t getObjectIndex(ISerializable *obj) const;
        size_t getObjectCount() const;
        const DatabaseID &getID(ISerializable *obj) const;

        ISerializable *getObject(const std::string &id) const;
        std::vector<ISerializable*> getObjects() const;
        template<typename T>
        T* getObject(const std::string &id) const;
        template<typename T>
        std::vector<T*> getObjects() const;

        const static size_t npos = -1;
    private:
        void instantiateDatabase(const QJsonArray &objs);
        void instantiateObject(const QJsonObject &obj);
        void clear();

        void addObjectInternal(ISerializable* obj, const DatabaseID &id);

        std::unordered_map<std::string, ISerializable*> m_saveableObjectTypes;
        std::unordered_map<std::string, DatabaseObject*> m_objects;

};


#define DATABASE_USE_OBJECT(objectType) \
template std::vector<objectType*> Database::getObjects() const; \
template objectType* Database::getObject(const std::string &id) const;


template<typename T>
bool Database::defineSaveableObject()
{
    T *t = new T();
    std::string typeName = t->className();

    if (m_saveableObjectTypes.find(typeName) == m_saveableObjectTypes.end())
    {
        m_saveableObjectTypes[typeName] = t;
        return true;
    }
    else
    {
        ISerializable *inList = m_saveableObjectTypes[typeName];

        std::string typeName1 = typeid(t).name();
        std::string typeName2 = typeid(inList).name();

        if(typeName1 == typeName2)
        {
            FATAL("Objekt Type: \""<<typeName<<"\" ist bereits definiert"<<"\n")
        }
        else
        {
            FATAL("Der ObjektName: \""<<typeName<<"\" für "<<typeName1<<
                  " ist bereits definiert für ein anderes Objekt: \""<<typeName2<<
                  "\" definiert worden."<<"\n")
        }
        delete t;
    }
    return false;
}
template<typename T>
T* Database::getObject(const std::string &id) const
{
    return dynamic_cast<T*>(getObject(id));
}
template<typename T>
std::vector<T*> Database::getObjects() const
{
    std::vector<T*> list;
    list.reserve(m_objects.size());
    for (auto& it: m_objects) {
        T *obj = dynamic_cast<T*>(it.second->getObject());
        if(obj)
            list.push_back(obj);
    }
    return list;
}
