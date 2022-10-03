#include "registrySettings.h"


RegistrySettings::RegistrySettings(const string &registryRootPath,
                                   const string &groupName)
    : QObject()
{
    m_registryRootPath = registryRootPath;
    m_groupName = groupName;
}
RegistrySettings::~RegistrySettings()
{
    clear();
}
const string &RegistrySettings::getRegistryRootPath() const
{
    return m_registryRootPath;
}
const string &RegistrySettings::getGroupName() const
{
    return m_groupName;
}/*
void RegistrySettings::undoValueChange()
{
    for (auto& pair: m_params) {
        pair.second->undoValueChange();
    }
}*/
void RegistrySettings::save()
{
    for (auto& pair: m_params) {
        pair.second->saveToRegistry();
    }
}

void RegistrySettings::read()
{
    for (auto& pair: m_params) {
        pair.second->readFromRegistry();
    }
}
RegistryParameter *RegistrySettings::getParameter(const string &name)
{
    if(!exists(name)) return nullptr;
    return m_params[name];
}
std::vector<RegistryParameter*> RegistrySettings::getParameters()
{
    std::vector<RegistryParameter*> list;
    list.reserve(m_params.size());
    for (auto& pair: m_params) {
        list.push_back(pair.second);
    }
    return list;
}

bool RegistrySettings::setParameter(const string &name, const string &value)
{
    if(!exists(name)) return false;
    m_params[name]->setValueStr(value);
    return true;
}

bool RegistrySettings::setParameter(const string &name, int value)
{
    if(!exists(name)) return false;
    m_params[name]->setValueInt(value);
    return true;
}

bool RegistrySettings::setParameter(const string &name, float value)
{
    if(!exists(name)) return false;
    m_params[name]->setValueFloat(value);
    return true;
}
bool RegistrySettings::addParameter(RegistryParameter *param,
                                    const string &name,
                                    const string &readableName,
                                    const string &description,
                                    const string &value)
{
    if(!param)
    {
#ifdef REGISTRY_SETTINGS_DEBUG
        CRITICAL("param is nullptr");
#endif
        return false;
    }
    param->setType(RegistryParameter::Type::stringType);
    param->setRegistryPath(m_registryRootPath);
    param->setName(name);
    param->setReadableName(readableName);
    param->setDescription(description);
    param->setValueStr(value);
    return addParameter(param);
}
bool RegistrySettings::addParameter(RegistryParameter *param,
                                    const string &name,
                                    const string &readableName,
                                    const string &description,
                                    int value)
{
    if(!param)
    {
#ifdef REGISTRY_SETTINGS_DEBUG
        CRITICAL("param is nullptr");
#endif
        return false;
    }
    param->setType(RegistryParameter::Type::intType);
    param->setRegistryPath(m_registryRootPath);
    param->setName(name);
    param->setReadableName(readableName);
    param->setDescription(description);
    param->setValueInt(value);
    return addParameter(param);
}
bool RegistrySettings::addParameter(RegistryParameter *param,
                                    const string &name,
                                    const string &readableName,
                                    const string &description,
                                    float value)
{
    if(!param)
    {
#ifdef REGISTRY_SETTINGS_DEBUG
        CRITICAL("param is nullptr");
#endif
        return false;
    }
    param->setType(RegistryParameter::Type::floatType);
    param->setRegistryPath(m_registryRootPath);
    param->setName(name);
    param->setReadableName(readableName);
    param->setDescription(description);
    param->setValueFloat(value);
    return addParameter(param);
}
bool RegistrySettings::addParameter(RegistryParameter *param)
{
    if(!param)
    {
#ifdef REGISTRY_SETTINGS_DEBUG
        CRITICAL("param is nullptr");
#endif
        return false;
    }
    if(exists(param->getName()))
    {
#ifdef REGISTRY_SETTINGS_DEBUG
        CRITICAL("param with name \""+param->getName()+"\" already exists");
#endif
        return false;
    }
    m_params.insert(std::pair<string,RegistryParameter*>(param->getName(),param));

    connect(param,&RegistryParameter::typeChanged,this,&RegistrySettings::onParameterTypeChanged);
    connect(param,&RegistryParameter::pathChanged,this,&RegistrySettings::onParameterPathChanged);
    connect(param,&RegistryParameter::nameChanged,this,&RegistrySettings::onParameterNameChanged);
    connect(param,&RegistryParameter::descriptionChanged,this,&RegistrySettings::onParameterDescriptionChanged);
    connect(param,&RegistryParameter::valueChanged,this,&RegistrySettings::onParameterValueChanged);
    connect(param,&RegistryParameter::destroyed,this,&RegistrySettings::onParameterDestroyed);

    return true;
}
bool RegistrySettings::removeParameter(RegistryParameter *param)
{
    if(!param)
    {
#ifdef REGISTRY_SETTINGS_DEBUG
        WARNING("param is nullptr");
#endif
        return false;
    }
    return removeParameter(param->getName());
}
bool RegistrySettings::removeParameter(const string &paramName)
{
    if(!exists(paramName))
    {
#ifdef REGISTRY_SETTINGS_DEBUG
        WARNING("param with name \""+paramName+"\" does not exists");
#endif
        return false;
    }
    RegistryParameter *param = m_params[paramName];
    disconnect(param,&RegistryParameter::typeChanged,this,&RegistrySettings::onParameterTypeChanged);
    disconnect(param,&RegistryParameter::pathChanged,this,&RegistrySettings::onParameterPathChanged);
    disconnect(param,&RegistryParameter::nameChanged,this,&RegistrySettings::onParameterNameChanged);
    disconnect(param,&RegistryParameter::descriptionChanged,this,&RegistrySettings::onParameterDescriptionChanged);
    disconnect(param,&RegistryParameter::valueChanged,this,&RegistrySettings::onParameterValueChanged);
    disconnect(param,&RegistryParameter::destroyed,this,&RegistrySettings::onParameterDestroyed);

    m_params.erase(paramName);
    return true;
}
void RegistrySettings::clear()
{
    for (auto& pair: m_params) {
        disconnect(pair.second,&RegistryParameter::typeChanged,this,&RegistrySettings::onParameterTypeChanged);
        disconnect(pair.second,&RegistryParameter::pathChanged,this,&RegistrySettings::onParameterPathChanged);
        disconnect(pair.second,&RegistryParameter::nameChanged,this,&RegistrySettings::onParameterNameChanged);
        disconnect(pair.second,&RegistryParameter::descriptionChanged,this,&RegistrySettings::onParameterDescriptionChanged);
        disconnect(pair.second,&RegistryParameter::valueChanged,this,&RegistrySettings::onParameterValueChanged);
        disconnect(pair.second,&RegistryParameter::destroyed,this,&RegistrySettings::onParameterDestroyed);
    }
    m_params.clear();
}
bool RegistrySettings::exists(const string &name) const
{
    return !(m_params.find(name) == m_params.end());
}

void RegistrySettings::onParameterTypeChanged(RegistryParameter::Type type)
{

}
void RegistrySettings::onParameterPathChanged(const string &path)
{

}

void RegistrySettings::onParameterNameChanged(const string &name)
{
    RegistryParameter *sender = qobject_cast<RegistryParameter*>(QObject::sender());
    string oldName;
    bool actionValid = true;
    for (auto& pair: m_params) {
        if(sender == pair.second)
        {
            oldName = pair.first;
        }
        else if(pair.first == name)
        {
            actionValid = false;
            sender->setName(oldName);
        }
    }
    if(actionValid)
    {
        m_params.erase(oldName);
        m_params.insert(std::pair<string,RegistryParameter*>(sender->getName(),sender));
    }
}

void RegistrySettings::onParameterDescriptionChanged(const string &description)
{

}

void RegistrySettings::onParameterValueChanged(const string &value)
{

}

void RegistrySettings::onParameterDestroyed(QObject *param)
{
    removeParameter((RegistryParameter*)param);
}
