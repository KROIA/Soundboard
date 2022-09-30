#include "registryParameter.h"




//const string RegistryParameter::m_relativeRegistryPath_settings = "settings";
//string RegistryParameter::m_globalRegistryRootPath = "HKEY_CURRENT_USER\\Software\\Qt\\Qt Apps\\SoundBoard";
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

/*void RegistryParameter::setRegistryRootPath(const string &path)
{
    m_globalRegistryRootPath = path;
}
const string &RegistryParameter::getRegistryRootPath()
{
    return m_globalRegistryRootPath;
}*/

void RegistryParameter::setRegistryPath(const string &path)
{
    m_path = path;
    emit pathChanged(m_path);
}
const string &RegistryParameter::getRegistryPath() const
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
    string value = getValue(m_path,m_name);
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
void RegistryParameter::setReadableName(const string &name)
{
    m_readableName = name;
}
void RegistryParameter::setName(const string &name)
{
    m_name = name;
    emit nameChanged(m_name);
}
void RegistryParameter::setDescription(const string &description)
{
    m_description = description;
    emit descriptionChanged(m_description);
}
void RegistryParameter::setValueStr(const string &value)
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
const string &RegistryParameter::getName() const
{
    return m_name;
}
const string &RegistryParameter::getReadableName() const
{
    return m_readableName;
}
const string &RegistryParameter::getDescription() const
{
    return m_description;
}
const string &RegistryParameter::getValueStr() const
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



void RegistryParameter::save(string path,string name,string value)
{
    QSettings _setting(path.c_str(),QSettings::NativeFormat);
    _setting.setValue(name.c_str(),value.c_str());
}
void RegistryParameter::save(string path,string name,int value)
{
    save(path,name,std::to_string(value));
}
void RegistryParameter::save(string path,string name,float value)
{
    save(path,name,std::to_string(value));
}

/*string RegistryParameter::getAbsolutePath(string path)
{
    return path;
}*/

bool RegistryParameter::valueExists(string path,string name)
{
    QSettings _setting(path.c_str(),QSettings::NativeFormat);
    bool exists = _setting.contains(name.c_str());
    return exists;
}
void RegistryParameter::removeValue(string path,string name)
{
    QSettings _setting(path.c_str(),QSettings::NativeFormat);
    _setting.remove(name.c_str());
}
string RegistryParameter::getValue(string path,string name)
{
    string value;
    QSettings _setting(path.c_str(),QSettings::NativeFormat);
    value =_setting.value(name.c_str()).toString().toStdString();
    return value;
}
