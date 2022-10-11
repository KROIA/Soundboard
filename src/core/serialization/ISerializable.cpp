#include "ISerializable.h"
/*
template<typename T>
T* ISerializable::factory(const QJsonObject &data)
{
    T* instance = new T();
    instance->read(data);
}*/


bool ISerializable::extract(const QJsonObject &obj, std::string &str, const std::string &key)
{
    QJsonValue val = obj[key.c_str()];
    if(val.isUndefined())
        return false;
    str = val.toString(str.c_str()).toStdString();
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
