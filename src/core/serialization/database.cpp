#include "database.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

Database::Database()
{
    defineSaveableObject<Sound>();
}
Database::~Database()
{

}

bool Database::load(const std::string &jsonFile)
{
    QFile file(jsonFile.c_str());
    if( file.open(QIODevice::ReadOnly ) )
    {
        QByteArray bytes = file.readAll();
        file.close();

        QJsonParseError jsonError;
        QJsonDocument document = QJsonDocument::fromJson( bytes, &jsonError );
        if( jsonError.error != QJsonParseError::NoError )
        {
            WARNING("Database konnte nicht geladen werden. Datei: \""<<jsonFile.c_str()<<"\"\nJsonError: "<<jsonError.errorString().toStdString()<<"\n");
            return false;
        }
        if(document.isArray())
        {
            QJsonArray objs = document.array();

            instantiateDatabase(objs);
            DEBUGLN(Debug::Color::green.c_str()<<"Database konnte geladen werden. Datei: \""<<jsonFile.c_str()<<"\"");
            return true;
        }
    }
    return false;
}
bool Database::save(const std::string &jsonFile)
{
    QJsonArray writer;

    for(size_t i=0; i<m_objects.size(); ++i)
    {
        QJsonObject obj = m_objects[i]->save();
        obj["ObjectType"] = m_objects[i]->className().c_str();
        writer.push_back(obj);
    }

    QJsonDocument document;
    document.setArray(writer);
    QByteArray bytes = document.toJson( QJsonDocument::Indented );
    QFile file(jsonFile.c_str());
    if( file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) )
    {
        QTextStream iStream( &file );
        iStream.setEncoding(QStringConverter::Encoding::Utf8);
        iStream << bytes;
        file.close();
        DEBUGLN(Debug::Color::green.c_str() << "Database gespeichert als: \""<<jsonFile.c_str()<<"\"");
        return true;
    }
    WARNING("Database konnte nicht gespeichert werden. Datei: \""<<jsonFile.c_str()<<"\"\n");
    return false;
}
bool Database::add(ISerializable* obj)
{
    auto findit = m_saveableObjectTypes.find(obj->className());
    if(findit == m_saveableObjectTypes.end())
    {
        WARNING("Kann Objekt (Name = \""<<obj->className()<<"\", ID = \""<<obj->getID() <<"\") nicht in aufnehmen,\n"
                "dieser Type wurde nicht in die speicherbaren Objekte liste aufgenommen"<<"\n");
        return false;
    }

    if(exists(obj))
    {
        WARNING("Objekt (Name = \""<<obj->className()<<"\", ID = \""<<obj->getID() <<"\") bereits vorhanden"<<"\n");
        return false;
    }
    m_objects.push_back(obj);

    addToMapInternal<Sound>(m_sounds, obj);

    return true;
}
bool Database::remove(ISerializable* obj)
{
    size_t index = getIndex(obj);
    if(index == npos) return false;

    m_objects.erase(m_objects.begin() + index);

    removeFromMapInternal<Sound>(m_sounds, obj);
    return true;
}
bool Database::exists(ISerializable* obj)
{
    return getIndex(obj) == npos ? false : true;
}
size_t Database::getIndex(ISerializable *obj)
{
    for(size_t i=0; i<m_objects.size(); ++i)
    {
        if(m_objects[i] == obj)
            return i;
    }
    return npos;
}
size_t Database::getObjectCount() const
{
    return m_objects.size();
}
Sound *Database::getSound(const std::string &id)
{
    auto findit = m_sounds.find(id);
    if(findit == m_sounds.end())
    {
        return nullptr;
    }
    return m_sounds[id];
}
void Database::instantiateDatabase(const QJsonArray &objs)
{
    clear();
    m_objects.reserve(objs.count());
    for(int i=0; i<objs.count(); ++i)
    {
        QJsonObject obj = objs[i].toObject();
        instantiateObject(obj);
    }
}
void Database::instantiateObject(const QJsonObject &obj)
{
    std::string objType = obj["ObjectType"].toString("none").toStdString();

    auto findit = m_saveableObjectTypes.find(objType);
    if(findit == m_saveableObjectTypes.end())
    {
        WARNING("Kann Objekt Type: \""<<objType<<"\" keinem definierten speicherbaren Objekt zuordnen"<<"\n");
        return;
    }
    else
    {
        ISerializable *instance = findit->second->clone(obj);
        if(instance)
        {
            m_objects.push_back(instance);

            addToMapInternal<Sound>(m_sounds, instance);
        }
    }
}
void Database::clear()
{
    for(size_t i=0; i<m_objects.size(); ++i)
    {
        delete m_objects[i];
    }
    m_objects.clear();

    m_sounds.clear();
}

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
bool Database::addToMapInternal(std::unordered_map<std::string, T*> &map,
                                ISerializable *obj)
{
    if(!obj) return false;
    T *casted = dynamic_cast<T*>(obj);
    if(!casted) return false;

    if(obj->getID().size() == 0)
    {
        FATAL("Objekt: \""<<obj->className()<<"\" hat keine ID"<<"\n");
        return false;
    }
    auto findit = map.find(obj->getID());
    if(findit == map.end())
    {
        map[obj->getID()] = casted;
        return true;
    }
    WARNING("Ein Objekt (Type = \""<<map[obj->getID()]->className()<<"\") mit gleicher ID: \""
            <<obj->getID()<<"\" bereits in der Liste.\n"
            "Kann daher Objekt (Name = \""<<obj->className()<<"\") nicht hinzufuegen."<<"\n");

    return false;
}

template<typename T>
bool Database::removeFromMapInternal(std::unordered_map<std::string, T*> &map,
                                     ISerializable *obj)
{
    if(!obj) return false;
    auto findit = map.find(obj->getID());
    if(findit == map.end())
    {
        return false;
    }
    map.erase(findit);
    return true;
}
