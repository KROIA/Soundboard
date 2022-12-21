#pragma once

#include <QObject>
#include <map>
#include <vector>
#include "debug.h"
#include "registryParameter.h"

#define REGISTRY_SETTINGS_DEBUG

/**
 * \author Alex Krieg
 * \date   12.10.2022
 *
 * \brief The RegistrySettings class
 * \details The RegistrySettings class is used to group several RegistryParameters together
 *          to form a group or category of settings.
 *
 *          This class contains helperfunctions to create a specific settings group
 *          1) Just inherit from this class and create private members of type: RegistryParameter for each setting
 *          2) In the constructor of the derived class,
 *             call \see addParameter(...) with the pointer to the RegistryParameter
 *             also fill the rest of the informations needed for that functioncall
 *
 */
class RegistrySettings  : public QObject
{
        Q_OBJECT
    public:
        /**
         * \brief RegistrySettings constructor
         * \param registryRootPath is the path in which all the parameters of this will be saved in
         * \param groupName stores the name of the settings group
         */
        RegistrySettings(const std::string &registryRootPath, const std::string &groupName);
        virtual ~RegistrySettings();

        /**
         * \return the registry path
         */
        const std::string &getRegistryRootPath() const;

        /**
         * \return the name
         */
        const std::string &getGroupName() const;

        /**
         * \brief Saves all parameters
         */
        virtual void save();

        /**
         * \brief Reads all parameters
         */
        virtual void read();

        /**
         * \brief Gets a parameter with the given name
         * \param name of the parameter
         * \return pointer to the found parameter
         *         nullptr if the no parameter was found with the given name
         */
        RegistryParameter *getParameter(const std::string &name);

        /**
         * \return a vector of all parameters
         */
        std::vector<RegistryParameter*> getParameters();

        /**
         * \brief Sets a setting by calling it with it's name
         * \param name of the setting parameter
         * \param value which will be set
         * \return
         */
        bool setParameter(const std::string &name, const std::string &value);
        bool setParameter(const std::string &name, int value);
        bool setParameter(const std::string &name, float value);

    protected:
        /**
         * \brief Creates a parameter in a derived class
         * \param param pointer to the RegistryParameter which is a member of the derived class
         * \param name of the parameter
         * \param readableName of the parameter
         * \param description of the parameter
         * \param value of the parameter for initialization
         * \return true if the parameter could be added
         *         false if the parameter could not be added -> see console
         */
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

        /**
         * \brief Creates a parameter in a derived class
         * \param param which shuld be added
         * \return
         */
        bool addParameter(RegistryParameter *param);

        /**
         * \brief Removes a added parameter
         * \details This will not delete the parameter
         * \param param which shuld be removed
         * \return true if the parameter was removed successfully
         */
        bool removeParameter(RegistryParameter *param);

        /**
         * \brief Removes a added parameter
         * \details This will not delete the parameter
         * \param paramName which shuld be removed
         * \return true if the parameter was removed successfully
         *         false if no parameter with such a name was found
         */
        bool removeParameter(const std::string &paramName);

        /**
         * \brief Removes all parameters
         */
        void clear();

        /**
         * \brief Checks if a parameter with the given name exists
         * \param name to search
         * \return
         */
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
