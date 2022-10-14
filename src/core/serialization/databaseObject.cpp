#include "databaseObject.h"
#include "database.h"

DatabaseObject::DatabaseObject(ISerializable *obj,
                               const DatabaseID &id,
                               Database *parent)
{
    m_obj = obj;
    m_id = id;
    m_parent = parent;
    m_obj->m_id = &m_id;
    m_obj->m_database = parent;
    m_obj->m_parent = this;
}

DatabaseObject::~DatabaseObject()
{
    if(!m_obj) return;
    m_obj->m_id = nullptr;
    m_obj->m_database = nullptr;
    m_obj->m_parent = nullptr;
    delete m_obj;
}

ISerializable *DatabaseObject::getObject() const
{
    return m_obj;
}
const DatabaseID &DatabaseObject::getID() const
{
    return m_id;
}

void DatabaseObject::objectGotDeleted()
{
    m_obj = nullptr;
    m_parent->removeObject(this);
}
