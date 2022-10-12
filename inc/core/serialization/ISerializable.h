#pragma once
#include <QJsonObject>
#include <string>
#include "databaseDeclaration.h"


/**
 * \brief The ISerializable class is used for objects,
 *        which can be saved to a Jason file.
 */
class ISerializable
{
    public:
        /**
         * \brief ISerializable
         * \details Creats a object with default values
         */
        ISerializable();

        /**
         * \brief ISerializable
         * \details Creats a object and copies the parameters of other
         * \param other object which will be copied from
         */
        ISerializable(const ISerializable &other);
        virtual ~ISerializable(){};

        /**
         * \brief className
         * \details Used to save the object type (class name) to know
         *          from which object this must be instantiated from when the
         *          saved file will be loaded
         * \return  Class unique type identifier
         */
        virtual std::string className() const = 0;

        /**
         * \brief clone
         * \details creates a copy of the object
         * \param reader with de json data to load parameters from.
         *        The data will not be copied from the cloning object, it is only used
         *        to recreate the same object structure.
         * \return Instantiated pointer to the same object type like the cloning object.
         */
        virtual ISerializable* clone(const QJsonObject &reader) const = 0;

        /**
         * \brief clone
         * \details creates a copy of the object
         * \param reader with de json data to load parameters from.
         *        The data will be copied from the cloning object.
         * \return Instantiated pointer to the same object type like the cloning object.
         */
        virtual ISerializable* clone() const = 0;

        /**
         * \brief getID
         * \return the unique id string of this object
         */
        const std::string &getID() const;

        /**
         * \brief save
         * \return the Json object with all stored data for a later reinstantiation of this object
         */
        virtual QJsonObject save() const;

        /**
         * \brief read
         * \param reader to load the saved parameters back
         * \return true if the loading was a success, otherwise false
         */
        virtual bool read(const QJsonObject &reader);

        /**
         * \brief postLoad
         * \details This function will be called after the database has loaded all objects<br>
         *          If you connect to other objects, this will be the place for that.
         */
        virtual void postLoad();


        const static std::string key_objectType;

        friend DatabaseObject;
    protected:

        /**
         * \brief extract a parameter out of the Json object
         * \param obj is the jeson object which holds the data
         * \param value in which the parameter value will be saved in
         * \param key name to find the right parameter
         * \return true, if the parameter was found in the json object
         */
        static bool extract(const QJsonObject &obj, std::string &value, const std::string &key);
        static bool extract(const QJsonObject &obj, int &value, const std::string &key);
        static bool extract(const QJsonObject &obj, float &value, const std::string &key);
        static bool extract(const QJsonObject &obj, double &value, const std::string &key);
        static bool extract(const QJsonObject &obj, bool &value, const std::string &key);

        static QJsonObject  combine(const QJsonObject &a, const QJsonObject &b);

    private:
        DatabaseID *m_id;
        Database *m_database;

};

/**
 * \macro IMPLEMENT_ISERIALIZABLE_CLONE(className)
 *        Implements the virtual clone() function of the ISerializable
 */
#define IMPLEMENT_ISERIALIZABLE_CLONE(className) \
className* clone(const QJsonObject &reader) const override\
{ \
    className *obj = new className(); \
    obj->read(reader); \
    return obj; \
} \
className* clone() const override \
{ \
    return new className(*this); \
}
