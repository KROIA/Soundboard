#include "registryParameter.h"

//const std::string RegistryParameter::m_relativeRegistryPath_settings = "settings";
//std::string RegistryParameter::m_globalRegistryRootPath = "HKEY_CURRENT_USER\\Software\\Qt\\Qt Apps\\SoundBoard";
RegistryParameter::RegistryParameter()
    : QObject()
{
    m_type = Type::stringType;
}
RegistryParameter::RegistryParameter(const RegistryParameter &other)
    : QObject()
{
    m_type = other.m_type;
    //m_lastValueStr = other.m_lastValueStr;
    m_valueStr = other.m_valueStr;
    m_description = other.m_description;
    m_name = other.m_name;
    m_path = other.m_path;
}
RegistryParameter::~RegistryParameter()
{
   // emit deleting();
}

/*void RegistryParameter::setRegistryRootPath(const std::string &path)
{
    m_globalRegistryRootPath = path;
}
const std::string &RegistryParameter::getRegistryRootPath()
{
    return m_globalRegistryRootPath;
}*/

void RegistryParameter::setRegistryPath(const std::string &path)
{
    m_path = path;
    emit pathChanged(m_path);
}
const std::string &RegistryParameter::getRegistryPath() const
{
    return m_path;
}
void RegistryParameter::saveToRegistry()
{
    //m_lastValueStr = m_valueStr;
    save(m_path,m_name,m_valueStr);
}
void RegistryParameter::readFromRegistry()
{
    std::string value = getValue(m_path, m_name);
    if(value != "")
    {
        m_valueStr = value;
       // m_lastValueStr = m_valueStr;
    }
}
void RegistryParameter::setType(Type type)
{
    m_type = type;
    emit typeChanged(m_type);
}
void RegistryParameter::setReadableName(const std::string &name)
{
    m_readableName = name;
}
void RegistryParameter::setName(const std::string &name)
{
    m_name = name;
    emit nameChanged(m_name);
}
void RegistryParameter::setDescription(const std::string &description)
{
    m_description = description;
    emit descriptionChanged(m_description);
}
void RegistryParameter::setValueStr(const std::string &value)
{
 //   m_lastValueStr = m_valueStr;
    m_valueStr = value;
    emit valueChanged(m_valueStr);
}
void RegistryParameter::setValueInt(int value)
{
    //  m_lastValueStr = m_valueStr;
    m_valueStr = std::to_string(value);
    emit valueChanged(m_valueStr);
}
void RegistryParameter::setValueFloat(float value)
{
    //  m_lastValueStr = m_valueStr;
    m_valueStr = std::to_string(value);
    emit valueChanged(m_valueStr);
}
/*void RegistryParameter::undoValueChange()
{
    m_valueStr = m_lastValueStr;
}*/

RegistryParameter::Type RegistryParameter::getType() const
{
    return m_type;
}
const std::string &RegistryParameter::getName() const
{
    return m_name;
}
const std::string &RegistryParameter::getReadableName() const
{
    return m_readableName;
}
const std::string &RegistryParameter::getDescription() const
{
    return m_description;
}
const std::string &RegistryParameter::getValueStr() const
{
    return m_valueStr;
}
int RegistryParameter::getValueInt() const
{
    return atoi(m_valueStr.c_str());
}
float RegistryParameter::getValueFloat() const
{
    return atof(m_valueStr.c_str());
}

void RegistryParameter::deleteKey()
{
    removeValue(m_path,m_name);
}

void RegistryParameter::save(std::string path, std::string name, std::string value)
{
    QSettings _setting(path.c_str(),QSettings::NativeFormat);
    _setting.setValue(name.c_str(),value.c_str());
}
void RegistryParameter::save(std::string path, std::string name, int value)
{
    save(path, name, std::to_string(value));
}
void RegistryParameter::save(std::string path, std::string name, float value)
{
    save(path, name, std::to_string(value));
}

/*std::string RegistryParameter::getAbsolutePath(std::string path)
{
    return path;
}*/

bool RegistryParameter::valueExists(std::string path, std::string name)
{
    QSettings _setting(path.c_str(),QSettings::NativeFormat);
    bool exists = _setting.contains(name.c_str());
    return exists;
}
void RegistryParameter::removeValue(std::string path, std::string name)
{
    QSettings _setting(path.c_str(),QSettings::NativeFormat);
    _setting.remove(name.c_str());
}
std::string RegistryParameter::getValue(std::string path, std::string name)
{
    std::string value;
    QSettings _setting(path.c_str(),QSettings::NativeFormat);
    value =_setting.value(name.c_str()).toString().toStdString();
    return value;
}
