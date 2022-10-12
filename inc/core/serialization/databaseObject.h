#pragma once

#include "databaseDeclaration.h"
#include "ISerializable.h"
#include "databaseID.h"


class DatabaseObject
{
public:
    DatabaseObject(ISerializable *obj,
                   const DatabaseID &id,
                   Database *parent);
    ~DatabaseObject();

    ISerializable *getObject() const;
    const DatabaseID &getID() const;

private:
    ISerializable *m_obj;
    DatabaseID m_id;

    Database *m_parent;
};
