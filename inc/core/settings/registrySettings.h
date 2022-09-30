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
        RegistrySettings(const string &registryRootPath,
                         const string &groupName);
        ~RegistrySettings();

        const string &getRegistryRootPath() const;
        const string &getGroupName() const;

        //void undoValueChange();
        void save();
        void read();

        RegistryParameter *getParameter(const string &name);
        std::vector<RegistryParameter*> getParameters();

        bool setParameter(const string &name, const string &value);
        bool setParameter(const string &name, int value);
        bool setParameter(const string &name, float value);


    protected:
        bool addParameter(RegistryParameter *param,
                          const string &name,
                          const string &readableName,
                          const string &description,
                          const string &value);
        bool addParameter(RegistryParameter *param,
                          const string &name,
                          const string &readableName,
                          const string &description,
                          int value);
        bool addParameter(RegistryParameter *param,
                          const string &name,
                          const string &readableName,
                          const string &description,
                          float value);
        bool addParameter(RegistryParameter *param);
        bool removeParameter(RegistryParameter *param);
        bool removeParameter(const string &paramName);
        void clear();
        bool exists(const string &name) const;


    private slots:
        void onParameterTypeChanged(RegistryParameter::Type type);
        void onParameterPathChanged(const string &path);
        void onParameterNameChanged(const string &name);
        void onParameterDescriptionChanged(const string &description);
        void onParameterValueChanged(const string &value);
        void onParameterDestroyed(QObject *param);


    private:
        std::map<string,RegistryParameter*> m_params;
        string m_registryRootPath;
        string m_groupName;
};
