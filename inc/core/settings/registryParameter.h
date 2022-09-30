#pragma once

#include <QObject>
#include <QSettings>
#include <string>

using std::string;


class RegistryParameter :   public QObject
{
        Q_OBJECT
    public:
        enum Type
        {
            stringType,
            intType,
            floatType
        };
        RegistryParameter();
        RegistryParameter(const RegistryParameter &other);
        ~RegistryParameter();

       /* static void setRegistryRootPath(const string &path);
        static const string &getRegistryRootPath();*/

        void setRegistryPath(const string &path);
        const string &getRegistryPath() const;
        void saveToRegistry();
        void readFromRegistry();

        void setType(Type type);
        void setName(const string &name);
        void setReadableName(const string &name);
        void setDescription(const string &description);
        void setValueStr(const string &value);
        void setValueInt(int value);
        void setValueFloat(float value);
       // void undoValueChange();

        Type getType() const;
        const string &getName() const;
        const string &getReadableName() const;
        const string &getDescription() const;
        const string &getValueStr() const;
        int getValueInt() const;
        float getValueFloat() const;

        void deleteKey();

        static void save(string path,string name,string value);
        static void save(string path,string name,int value);
        static void save(string path,string name,float value);
        //static string getAbsolutePath(string path);
        static bool valueExists(string path,string name);
        static void removeValue(string path,string name);
        static string getValue(string path,string name);

       // static const string m_relativeRegistryPath_settings;
    signals:
        void typeChanged(Type type);
        void pathChanged(const string &path);
        void nameChanged(const string &name);
        void descriptionChanged(const string &description);
        void valueChanged(const string &value);

    protected:
       // static string m_globalRegistryRootPath;

        Type m_type;
        string m_path;
        string m_name;
        string m_readableName;
        string m_description;
        string m_valueStr;
        //string m_lastValueStr;
};

