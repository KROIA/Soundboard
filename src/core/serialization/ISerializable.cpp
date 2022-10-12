#include "ISerializable.h"
#include "databaseID.h"

const std::string ISerializable::key_objectType = "objectType";


ISerializable::ISerializable()
{

}
ISerializable::ISerializable(const ISerializable &other)
{

}

const std::string &ISerializable::getID() const
{
    static const std::string dummy;
    if(!m_id) return dummy;
    return m_id->getID();
}


QJsonObject ISerializable::save() const
{
    return QJsonObject
    {
        {key_objectType.c_str(), className().c_str()},
    };
}
bool ISerializable::read(const QJsonObject &reader)
{
    return true;
}
void ISerializable::postLoad()
{

}
bool ISerializable::extract(const QJsonObject &obj, std::string &value, const std::string &key)
{
    QJsonValue val = obj[key.c_str()];
    if(val.isUndefined())
        return false;
    value = val.toString(value.c_str()).toStdString();
    return true;
}
bool ISerializable::extract(const QJsonObject &obj, int &value, const std::string &key)
{
    QJsonValue val = obj[key.c_str()];
    if(val.isUndefined())
        return false;
    value = val.toInt(value);
    return true;
}
bool ISerializable::extract(const QJsonObject &obj, float &value, const std::string &key)
{
    QJsonValue val = obj[key.c_str()];
    if(val.isUndefined())
        return false;
    value = val.toDouble(value);
    return true;
}
bool ISerializable::extract(const QJsonObject &obj, double &value, const std::string &key)
{
    QJsonValue val = obj[key.c_str()];
    if(val.isUndefined())
        return false;
    value = val.toDouble(value);
    return true;
}
bool ISerializable::extract(const QJsonObject &obj, bool &value, const std::string &key)
{
    QJsonValue val = obj[key.c_str()];
    if(val.isUndefined())
        return false;
    value = val.toBool(value);
    return true;
}

QJsonObject  ISerializable::combine(const QJsonObject &a, const QJsonObject &b)
{
    QJsonObject obj3(a);
    for (auto it = b.constBegin(); it != b.constEnd(); it++) {
        obj3.insert(it.key(), it.value());
    }
    return obj3;
}
