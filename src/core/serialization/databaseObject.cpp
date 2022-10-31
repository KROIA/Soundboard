#include "databaseObject.h"

DatabaseObject::DatabaseObject(ISerializable *obj,
                               const DatabaseID &id,
                               Database *parent)
{
    m_obj = obj;
    m_id = id;
    m_parent = parent;
    m_obj->m_id = &m_id;
    m_obj->m_database = parent;
}

DatabaseObject::~DatabaseObject()
{
    m_obj->m_id = nullptr;
    m_obj->m_database = nullptr;
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
