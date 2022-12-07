#include "database.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

#ifdef QT_DEBUG
#define PERFORMANCE_TEST
#endif

#ifdef PERFORMANCE_TEST
#include "performanceTimer.h"
#endif

Database::Database()
{

}
Database::~Database()
{
    clear();
}

bool Database::load(const std::string &jsonFile)
{
    DEBUGLN("Lese Database: \""<<jsonFile.c_str()<<"\"");
    QFile file(jsonFile.c_str());
    if(!file.exists())
    {
        WARNING("  Database konnte nicht geladen werden. Datei: \""<<jsonFile.c_str()<<"\" nicht gefunden\n");
        return false;
    }
    if( file.open(QIODevice::ReadOnly ) )
    {
        QByteArray bytes;
        {
            DEBUG("  Lese Datei: \""<<jsonFile.c_str()<<"\"");
#ifdef PERFORMANCE_TEST
            PerformanceTimer timer(true);
#endif
            bytes = file.readAll();
            file.close();
#ifdef PERFORMANCE_TEST
            DEBUGLN(" fertig " << timer.getRuntimeMsStr().c_str());
#else
            DEBUGLN(" fertig");
#endif
        }

        QJsonParseError jsonError;
        QJsonDocument document;
        {
            DEBUG("  Konvertiere zu QJsonDocument");
#ifdef PERFORMANCE_TEST
            PerformanceTimer timer(true);
#endif
            document = QJsonDocument::fromJson( bytes, &jsonError );
#ifdef PERFORMANCE_TEST
            DEBUGLN(" fertig " << timer.getRuntimeMsStr().c_str());
#else
            DEBUGLN(" fertig");
#endif

            if( jsonError.error != QJsonParseError::NoError )
            {
                WARNING("  Database konnte nicht geladen werden. Datei: \""<<jsonFile.c_str()<<"\"\nJsonError: "<<jsonError.errorString().toStdString().c_str()<<"\n");
                return false;
            }
        }
        if(document.isArray())
        {
            DEBUG("  Instanziere Objekte");
#ifdef PERFORMANCE_TEST
            PerformanceTimer timer(true);
#endif
            QJsonArray objs = document.array();
            instantiateDatabase(objs);
#ifdef PERFORMANCE_TEST
            DEBUGLN(" fertig " << timer.getRuntimeMsStr().c_str());
#else
            DEBUGLN(" fertig");
#endif
            DEBUGLN("  "<<Debug::Color::green.c_str()<<"Database konnte geladen werden. Datei: \""<<jsonFile.c_str()<<"\"");
            return true;
        }
    }
    WARNING("  Database konnte nicht geladen werden. Datei: \""<<jsonFile.c_str()<<"\"\n");
    return false;
}
bool Database::save(const std::string &jsonFile) const
{
    QJsonArray writer;

    for (auto& it: m_objects)
    {
        QJsonObject obj = it.second->getObject()->save();
        obj[DatabaseID::key_id.c_str()] = it.second->getID().getID().c_str();
        writer.push_back(obj);
    }

    QJsonDocument document;
    document.setArray(writer);
    QByteArray bytes = document.toJson( QJsonDocument::Indented );
    QFile file(jsonFile.c_str());
    if( file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) )
    {

        QTextStream iStream( &file );
  #if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
        iStream.setEncoding(QStringConverter::Encoding::Utf8);
  #else
        iStream.setCodec("UTF-8");
  #endif


        iStream << bytes;
        file.close();
        DEBUGLN(Debug::Color::green.c_str() << "Database gespeichert als: \""<<jsonFile.c_str()<<"\"");
        return true;
    }
    WARNING("Database konnte nicht gespeichert werden. Datei: \""<<jsonFile.c_str()<<"\"\n");
    return false;
}
bool Database::addObject(ISerializable* obj)
{
    auto findit = m_saveableObjectTypes.find(obj->className());
    if(findit == m_saveableObjectTypes.end())
    {
        WARNING("Kann Objekt (Name = \""<<obj->className().c_str()<<"\") nicht in aufnehmen,\n"
                "dieser Type wurde nicht in die speicherbaren Objekte liste aufgenommen\n");
        return false;
    }

    if(objectExists(obj))
    {
        WARNING("Objekt (Name = \""<<obj->className().c_str()<<"\", ID = \""<<obj->getID().c_str() <<"\") bereits vorhanden"<<"\n");
        return false;
    }
    DatabaseID id(DatabaseID::generateRandomID());
    while(objectExists(id.getID()))
        id.setID(DatabaseID::generateRandomID());

    addObjectInternal(obj,id);
    return true;
}
void Database::addObjectInternal(ISerializable* obj, const DatabaseID &id)
{
    DatabaseObject *dbObj = new DatabaseObject(obj, id, this);
    m_objects.insert(std::pair<std::string, DatabaseObject*>(dbObj->getID().getID(),dbObj));
}
bool Database::removeObject(ISerializable* obj)
{    
    DatabaseObject *dbObj = nullptr;

    for (auto& it: m_objects)
    {
        if(it.second->getObject() == obj)
        {
            dbObj = it.second;
            break;
        }
    }
    if(dbObj)
    {
        m_objects.erase(dbObj->getID().getID());
        //delete dbObj;
        return true;
    }
    return false;
}
bool Database::removeObject(DatabaseObject *dbObj)
{
  bool found = false;
  for (auto& it: m_objects)
  {
    if(it.second == dbObj)
    {
      found = true;
      break;
    }
  }
  if(found)
  {
    m_objects.erase(dbObj->getID().getID());
   //delete dbObj;
    return true;
  }
  return false;
}
DatabaseObject* Database::removeObject(const std::string &id)
{
    auto findit = m_objects.find(id);
    if(findit == m_objects.end())
        return nullptr;
    DatabaseObject *dbObj = findit->second;
    m_objects.erase(dbObj->getID().getID());
    //delete dbObj;
    return dbObj;
}
bool Database::objectExists(ISerializable* obj) const
{
    for (auto& it: m_objects)
    {
        if(it.second->getObject() == obj)
        {
            return true;
        }
    }
    return false;
}
bool Database::objectExists(const std::string &id) const
{
    auto findit = m_objects.find(id);
    if(findit == m_objects.end())
    {
        return false;
    }
    return true;
}

size_t Database::getObjectCount() const
{
    return m_objects.size();
}
/*const DatabaseID &Database::getID(ISerializable *obj) const
{
    for (auto& it: m_objects)
    {
        if(it.second->getObject() == obj)
            return it.second->getID();
    }
    const static DatabaseID dummy;
    return dummy;
}*/
ISerializable *Database::getObject(const std::string &id) const
{
    auto findit = m_objects.find(id);
    if(findit == m_objects.end())
    {
        return nullptr;
    }
    return findit->second->getObject();
}
std::vector<ISerializable*> Database::getObjects() const
{
    std::vector<ISerializable*> list;
    for (auto& it: m_objects) {
        if(it.second)
            list.push_back(it.second->getObject());
    }
    return list;
}

void Database::instantiateDatabase(const QJsonArray &objs)
{
    clear();
    m_objects.reserve(objs.count());
/*#ifdef QT_DEBUG
    const size_t dbg_loadingBarCount = 20;
    size_t dbg_loadingBarInterval = objs.count()/dbg_loadingBarCount;
    DEBUG(" ");
#endif*/
    for(int i=0; i<objs.count(); ++i)
    {
/*#ifdef QT_DEBUG
        if(i%dbg_loadingBarInterval == 0)
        DEBUG("#");
#endif*/
        QJsonObject obj = objs[i].toObject();
        instantiateObject(obj);
    }
    for (auto& it: m_objects)
    {
        it.second->getObject()->postLoad();
    }
}
void Database::instantiateObject(const QJsonObject &obj)
{
#ifdef PERFORMANCE_TEST
    DEBUGLN("");
#endif
    std::string objType;
    {
#ifdef PERFORMANCE_TEST
        PerformanceTimer timer(true);
        DEBUG("      Finde Objekttype... ");
#endif
        objType = obj[ISerializable::key_objectType.c_str()].toString("none").toStdString();
#ifdef PERFORMANCE_TEST
        DEBUGLN("      fertig "<<timer.getRuntimeMsStr().c_str());
#endif
    }

#ifdef PERFORMANCE_TEST
    PerformanceTimer timer(true);
    DEBUG("      Finde Objekt zum kopieren... ");
#endif
    auto findit = m_saveableObjectTypes.find(objType);
#ifdef PERFORMANCE_TEST
    DEBUGLN("      fertig "<<timer.getRuntimeMsStr().c_str());
#endif

    if(findit == m_saveableObjectTypes.end())
    {
        WARNING("Kann Objekt Type: \""<<objType.c_str()<<"\" keinem definierten speicherbaren Objekt zuordnen\n");
        return;
    }
    else
    {
#ifdef PERFORMANCE_TEST
        PerformanceTimer timer(true);
        DEBUG("      Klone Objekt... ");
#endif
        ISerializable *instance = findit->second->clone(obj);
#ifdef PERFORMANCE_TEST
        DEBUGLN("      fertig "<<timer.getRuntimeMsStr().c_str());
#endif

        if(instance)
        {
            DatabaseID id(obj[DatabaseID::key_id.c_str()].toString().toStdString());

            //addObject(instance);
            if(!objectExists(id.getID()))
            {

#ifdef PERFORMANCE_TEST
                PerformanceTimer timer(true);
                DEBUG("      Objekt in die Datenbank aufnehmen... ");
#endif
                addObjectInternal(instance,id);
#ifdef PERFORMANCE_TEST
                DEBUGLN("      fertig "<<timer.getRuntimeMsStr().c_str());
#endif
            }
            else
            {
                ISerializable *other = m_objects[id.getID()]->getObject();
                WARNING("Kann Objekt Type: \""<<objType.c_str()<<"\" ID: \""<< id.getID().c_str() <<"\" nicht laden. Objekt Type: \""<<other->className().c_str()<<"\" hat die gleiche ID\n");
            }
        }
    }
}
void Database::clear()
{
    for (auto& it: m_objects) {
        delete it.second;
    }
    m_objects.clear();
}
