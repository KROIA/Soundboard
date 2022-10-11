#pragma once
#include <QJsonObject>
#include <string>

class ISerializable
{
    public:
        virtual ~ISerializable(){};

        //template<typename T>
        //static T* factory(const QJsonObject &data);

        virtual std::string className() const = 0;
        virtual ISerializable* clone(const QJsonObject &reader) const = 0;

        virtual void setID(const std::string &id) = 0;
        virtual const std::string &getID() const = 0;

        virtual QJsonObject save() const = 0;
        virtual bool read(const QJsonObject &reader) = 0;

    protected:
        static bool extract(const QJsonObject &obj, std::string &str, const std::string &key);
        static bool extract(const QJsonObject &obj, int &value, const std::string &key);
        static bool extract(const QJsonObject &obj, float &value, const std::string &key);
        static bool extract(const QJsonObject &obj, double &value, const std::string &key);
        static bool extract(const QJsonObject &obj, bool &value, const std::string &key);

    private:

};


