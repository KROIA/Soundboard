#pragma once

#include <QObject>
#include <QSettings>
#include <string>

class RegistryParameter : public QObject
{
        Q_OBJECT
    public:
        enum Type { stringType, intType, floatType };
        RegistryParameter();
        RegistryParameter(const RegistryParameter &other);
        ~RegistryParameter();

        /* static void setRegistryRootPath(const std::string &path);
        static const std::string &getRegistryRootPath();*/

        void setRegistryPath(const std::string &path);
        const std::string &getRegistryPath() const;
        void saveToRegistry();
        void readFromRegistry();

        void setType(Type type);
        void setName(const std::string &name);
        void setReadableName(const std::string &name);
        void setDescription(const std::string &description);
        void setValueStr(const std::string &value);
        void setValueInt(int value);
        void setValueFloat(float value);
       // void undoValueChange();

        Type getType() const;
        const std::string &getName() const;
        const std::string &getReadableName() const;
        const std::string &getDescription() const;
        const std::string &getValueStr() const;
        int getValueInt() const;
        float getValueFloat() const;

        void deleteKey();

        static void save(std::string path, std::string name, std::string value);
        static void save(std::string path, std::string name, int value);
        static void save(std::string path, std::string name, float value);
        //static std::string getAbsolutePath(std::string path);
        static bool valueExists(std::string path, std::string name);
        static void removeValue(std::string path, std::string name);
        static std::string getValue(std::string path, std::string name);

        // static const std::string m_relativeRegistryPath_settings;
    signals:
        void typeChanged(Type type);
        void pathChanged(const std::string &path);
        void nameChanged(const std::string &name);
        void descriptionChanged(const std::string &description);
        void valueChanged(const std::string &value);

    protected:
        // static std::string m_globalRegistryRootPath;

        Type m_type;
        std::string m_path;
        std::string m_name;
        std::string m_readableName;
        std::string m_description;
        std::string m_valueStr;
        //std::string m_lastValueStr;
};

