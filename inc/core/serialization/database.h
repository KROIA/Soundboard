#pragma once

#include <unordered_map>
#include <vector>
#include "databaseObject.h"
#include "debug.h"

/**
 * \author Alex Krieg
 * \date   12.10.2022
 *
 * \brief The Database class
 * \details The database is used to serialize and deserialize objects.
 *          Objects must inherit the ISerializable interface for that.<br>
 *
 *          Each ISerializable object will be packed in an SatabaseObject.
 *          The DatabaseObject will not be accessible outside the database and is used
 *          to hold the unique ID string for each object.
 *
 */
class Database
{
    public:
        Database();
        ~Database();

        /**
         * \brief Specifies the object type to be reloaded
         * \return true if the type was added successfully
         *         false if the type could not be added -> see console
         */
        template<typename T>
        bool defineSaveableObject();

        /**
         * \brief Loading of a saved json file
         * \param jsonFile path to the file
         * \return true if the file was read successfully
         *         false if the file could not be read or is corrupted -> see console
         */
        bool load(const std::string &jsonFile);

        /**
         * \brief Saves the current added objects to a json file
         * \param jsonFile path to the file which will be created
         * \return true if the file was saved successfully
         *         false if the file could not be saved -> see console
         */
        bool save(const std::string &jsonFile) const;

        /**
         * \brief Adds a ISerializable object to this database
         * \param obj which shuld be added
         * \return true if the object was added successfully
         *         false if the object could not be added -> see console
         */
        bool addObject(ISerializable* obj);

        /**
         * \brief Removes a object from the Database.
         * \details Removing does not delete the object
         * \param obj which shuld be removed
         * \return true if the object was successfully removed
         *         false if the object was not found in the database
         */
        bool removeObject(ISerializable* obj);

        /**
         * \brief Removes a object from the Database.
         * \details Removing does not delete the object
         * \param obj which shuld be removed
         * \return true if the object was successfully removed
         *         false if the object was not found in the database
         */
        bool removeObject(DatabaseObject *dbObj);

        /**
         * \brief Removes a object from the Database.
         * \details Removing does not delete the object
         * \param id to the object which shuld be removed
         * \return ptr io the removed object
         *         nullptr if the object was not found in the database
         */
        DatabaseObject* removeObject(const std::string &id);

        /**
         * \brief Checks if the given object exists in this database
         * \param obj to search for
         * \return true if the obj was found in this database
         *         false if the obj was not found in this database
         */
        bool objectExists(ISerializable* obj) const;

        /**
         * \brief Checks if a object with given id exists in this database
         * \param id to the searched object
         * \return true if the obj was found in this database
         *         false if the obj was not found in this database
         */
        bool objectExists(const std::string &id) const;

        /**
         * \brief Gets the object count in the database
         * \return amount of objects contained in this database
         */
        size_t getObjectCount() const;

        /**
         * \brief Gets the object count of a specific type in the database
         * \return amount of objects, with type T, contained in this database
         */
        template<typename T>
        size_t getObjectCount() const;

        /**
         * \brief Gets the object with the given id
         * \param id to the searched object
         * \return ptr to the object with the given id
         *         nullptr if no object was found with that id
         */
        ISerializable *getObject(const std::string &id) const;

        /**
         * \brief Gets all objects in this database
         * \return vector of objects contained in this database
         */
        std::vector<ISerializable*> getObjects() const;

        /**
         * \brief Gets the object, with type T, with the given id
         * \param id to the searched object
         * \return ptr to the object, of type T, with the given id
         *         nullptr if no object was found with that id
         */
        template<typename T>
        T* getObject(const std::string &id) const;

        /**
         * \brief Gets all objects, with type T, in this database
         * \return vector of objects, of type T, contained in this database
         */
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


/**
 * \macro Create a template variant for the class objectType
 *        Call this macro once for each ISerializable object type in the main
 *        outside of a function
 */
#define DATABASE_USE_OBJECT(objectType) \
template std::vector<objectType*> Database::getObjects() const; \
template objectType* Database::getObject(const std::string &id) const; \
ISERIALIZABLE_DATABASE_USE_OBJECT(objectType)


#define ISERIALIZABLE_DATABASE_USE_OBJECT(objectType) \
template size_t ISerializable::databaseGetObjectCount<objectType>() const; \
template objectType* ISerializable::databaseGetObject(const std::string &id) const; \
template std::vector<objectType*> ISerializable::databaseGetObjects() const;



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
            FATAL("Objekt Type: \""<<typeName.c_str()<<"\" ist bereits definiert"<<"\n")
        }
        else
        {
            FATAL("Der ObjektName: \""<<typeName.c_str()<<"\" für "<<typeName1.c_str()<<
                  " ist bereits definiert für ein anderes Objekt: \""<<typeName2.c_str()<<
                  "\" definiert worden.\n")
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
template<typename T>
size_t Database::getObjectCount() const
{
    size_t count = 0;
    for (auto& it: m_objects) {
        T *obj = dynamic_cast<T*>(it.second->getObject());
        if(obj)
            ++count;
    }
    return count;
}


// The implementation of the template func's are here
// because the database must be known to define the functions
template<typename T>
size_t ISerializable::databaseGetObjectCount() const
{
    if(!m_database) return 0;
    return m_database->getObjectCount<T>();
}
template<typename T>
T* ISerializable::databaseGetObject(const std::string &id) const
{
    if(!m_database) return nullptr;
    return m_database->getObject<T>(id);
}
template<typename T>
std::vector<T*> ISerializable::databaseGetObjects() const
{
    if(!m_database) return std::vector<T*>();
    return m_database->getObjects<T>();
}
