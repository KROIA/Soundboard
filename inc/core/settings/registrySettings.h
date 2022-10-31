#pragma once

#include <QObject>
#include <map>
#include <vector>
#include "debug.h"
#include "registryParameter.h"

#define REGISTRY_SETTINGS_DEBUG

class RegistrySettings  : public QObject
{
        Q_OBJECT
    public:
        RegistrySettings(const std::string &registryRootPath, const std::string &groupName);
        ~RegistrySettings();

        const std::string &getRegistryRootPath() const;
        const std::string &getGroupName() const;

        //void undoValueChange();
        void save();
        void read();

        RegistryParameter *getParameter(const std::string &name);
        std::vector<RegistryParameter*> getParameters();

        bool setParameter(const std::string &name, const std::string &value);
        bool setParameter(const std::string &name, int value);
        bool setParameter(const std::string &name, float value);

    protected:
        bool addParameter(RegistryParameter *param,
                          const std::string &name,
                          const std::string &readableName,
                          const std::string &description,
                          const std::string &value);
        bool addParameter(RegistryParameter *param,
                          const std::string &name,
                          const std::string &readableName,
                          const std::string &description,
                          int value);
        bool addParameter(RegistryParameter *param,
                          const std::string &name,
                          const std::string &readableName,
                          const std::string &description,
                          float value);
        bool addParameter(RegistryParameter *param);
        bool removeParameter(RegistryParameter *param);
        bool removeParameter(const std::string &paramName);
        void clear();
        bool exists(const std::string &name) const;

    private slots:
        void onParameterTypeChanged(RegistryParameter::Type type);
        void onParameterPathChanged(const std::string &path);
        void onParameterNameChanged(const std::string &name);
        void onParameterDescriptionChanged(const std::string &description);
        void onParameterValueChanged(const std::string &value);
        void onParameterDestroyed(QObject *param);


    private:
        std::map<std::string, RegistryParameter *> m_params;
        std::string m_registryRootPath;
        std::string m_groupName;
};
