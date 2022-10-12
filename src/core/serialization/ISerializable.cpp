#include "ISerializable.h"
#include <chrono>
#include <ctime>

const std::string ISerializable::key_objectType = "objectType";
const std::string ISerializable::key_id = "id";

ISerializable::ISerializable()
{
    setID(generateRandomID());
}
ISerializable::ISerializable(const ISerializable &other)
{
    setID(other.getID());
}

std::string ISerializable::generateRandomID(size_t length)
{
    const std::string chars             = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    size_t charsCount                   = chars.size();
    const static std::time_t randTime   = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    std::string str(length+1,'\0');
    for(size_t i=0; i<length; ++i)
        str[i] = chars[(rand()+randTime)%charsCount];
    return str;
}

void ISerializable::setID(const std::string &id)
{
    m_id = id;
}
const std::string &ISerializable::getID() const
{
    return m_id;
}


QJsonObject ISerializable::save() const
{
    return QJsonObject
    {
        {key_objectType.c_str(), className().c_str()},
        {key_id.c_str(), m_id.c_str()},
    };
}
bool ISerializable::read(const QJsonObject &reader)
{
    return extract(reader, m_id, key_id);
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
