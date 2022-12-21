#pragma once

#include <QObject>
#include <QSettings>
#include <string>


/**
 * \author Alex Krieg
 * \date   12.10.2022
 *
 * \brief The RegistryParameter class
 * \details The RegistryParameter is used to store a single value in to the
 *          system registry for persistent data storage.
 *
 *          A parameter can be a string, integer or float type.
 *
 */
class RegistryParameter : public QObject
{
        Q_OBJECT
    public:
        enum Type { stringType, intType, floatType };
        RegistryParameter();
        RegistryParameter(const RegistryParameter &other);
        ~RegistryParameter();


        /**
         * \brief setRegistryPath
         * \details Exampe path: "HKEY_CURRENT_USER\\Software\\Qt\\Qt Apps\\Application"
         * \param path in which the setting will be stored
         */
        void setRegistryPath(const std::string &path);

        /**
         * \brief Gets the path of this parameter
         * \return registry path to this parameter
         */
        const std::string &getRegistryPath() const;

        /**
         * \brief Saves the parameter in to the registry
         */
        void saveToRegistry();

        /**
         * \brief Reads the parameter from the registry
         */
        void readFromRegistry();

        /**
         * \brief Defines the type in which form the parameter will be saved as
         * \param type
         */
        void setType(Type type);

        /**
         * \brief Sets the name of this parameter
         * \param name
         */
        void setName(const std::string &name);

        /**
         * \brief Sets a more readable name, this can be a small description
         * \param name string
         */
        void setReadableName(const std::string &name);

        /**
         * \brief Sets a more detailed desctiption
         * \param description string
         */
        void setDescription(const std::string &description);

        /**
         * \brief Sets the value as string
         * \param value string
         */
        void setValueStr(const std::string &value);

        /**
         * \brief Sets the value as int
         * \param value int
         */
        void setValueInt(int value);

        /**
         * \brief Sets the value as float
         * \param value float
         */
        void setValueFloat(float value);


        /**
         * \return type of this parameter
         */
        Type getType() const;

        /**
         * \return name of this parameter
         */
        const std::string &getName() const;

        /**
         * \return readable name of this parameter
         */
        const std::string &getReadableName() const;

        /**
         * \return description of this parameter
         */
        const std::string &getDescription() const;

        /**
         * \return string value
         */
        const std::string &getValueStr() const;

        /**
         * \return int value
         */
        int getValueInt() const;

        /**
         * \return float value
         */
        float getValueFloat() const;

        /**
         * \brief Deletes the parameter in the registry
         */
        void deleteKey();

        /**
         * \brief save a setting using the given values
         * \param path in which the value will be saved
         * \param name for the registry parameter
         * \param value for the parameter
         */
        static void save(std::string path, std::string name, std::string value);
        static void save(std::string path, std::string name, int value);
        static void save(std::string path, std::string name, float value);

        /**
         * \brief Checks if such a value exists in the registry
         * \param path to the registry parameter
         * \param name of the registry parameter
         * \return true if the registry parameter exists
         */
        static bool valueExists(std::string path, std::string name);

        /**
         * \brief Removes the parameter at the given registry path
         * \param path to the parameter
         * \param name of the parameter
         */
        static void removeValue(std::string path, std::string name);

        /**
         * \brief Gets the value of the given registry parameter
         * \param path to the parameter
         * \param name of the parameter
         * \return
         */
        static std::string getValue(std::string path, std::string name);

        /**
         * \brief Defines a min - max range for float types
         * \param min, minimum, including
         * \param max, maximum, including
         */
        void setFloatRange(float min, float max);

        /**
         * \brief Defines a min - max range for int types
         * \param min, minimum, including
         * \param max, maximum, including
         */
        void setIntRange(int min, int max);

        /**
         * \brief Defines the maximal allowed length of a string value
         * \details Strings longer than this value are truncated
         * \param count of characters in the string value
         */
        void setMaxCharCount(unsigned int count);

        /**
         * \return the float minimal range value
         */
        float getFloatRangeMin() const;

        /**
         * \return the float maximal range value
         */
        float getFloatRangeMax() const;

        /**
         * \return the int minimal range value
         */
        int getIntRangeMin() const;

        /**
         * \return the int maximal range value
         */
        int getIntRangeMax() const;

        /**
         * \return the maximal allowed string length
         */
        unsigned int getMaxCharCount() const;

    signals:
        /**
         * \brief Emitted when the type changes
         * \param type which is now set in this parameter
         */
        void typeChanged(Type type);

        /**
         * \brief Emitted when the path changes
         * \param path which is now set in this parameter
         */
        void pathChanged(const std::string &path);

        /**
         * \brief Emitted when the name changes
         * \param name which is now set in this parameter
         */
        void nameChanged(const std::string &name);

        /**
         * \brief Emitted when the description changes
         * \param description which is now set in this parameter
         */
        void descriptionChanged(const std::string &description);

        /**
         * \brief Emitted when the value changes
         * \details This signal will also be emitted for int and float type of parameters
         * \param value which is now set in this parameter
         */
        void valueChanged(const std::string &value);

    protected:


        Type m_type;
        std::string m_path;
        std::string m_name;
        std::string m_readableName;
        std::string m_description;
        std::string m_valueStr;


        float m_fMin, m_fMax;
        int m_iMin, m_iMax;
        unsigned int m_maxCharCount;
};

