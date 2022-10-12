#pragma once

#include "ISerializable.h"
#include "debug.h"

class Fruit : public ISerializable
{
    public:
        Fruit()
        {
            m_name = "Fruit";
            m_color = "green";
            m_calories = 20;
        }
        ~Fruit(){}

        IMPLEMENT_ISERIALIZABLE_CONST_FUNC(Fruit)

        QJsonObject save() const override
        {
            DEBUGLN("Fruit::save()");
            // Add this data to thisData
            QJsonObject thisData = combine(ISerializable::save(),
            QJsonObject
            {
                // Add the properties of this object here
                // Do not take the same keyvalues two times,
                // also not the keys of the base class
                {"name" , m_name.c_str()},
                {"color", m_color.c_str()},
                {"calories", m_calories},
            });

            // Get the QJsonObject of the member object
            //thisData["myObject"] = myObject.save();

            return thisData;
        }
        bool read(const QJsonObject &reader) override
        {
            DEBUGLN("Fruit::read()");
            bool success = true;
            // Read the value for the base class
            success = ISerializable::read(reader);

            // Read the value for the member object
            // success &= myObject.read(thisData["myObject"]);

            // Read the values for this class
            success &= extract(reader,m_name, "name");
            success &= extract(reader,m_color,"color");
            success &= extract(reader,m_calories,"calories");
            return success;
        }
        void postLoad() override
        {

        }

        virtual std::string toString()
        {
            return "ID:       "+getID()+"\n"
                   "name:     "+m_name+"\n"
                   "color:    "+m_color+"\n"
                   "calories: "+std::to_string(m_calories)+"\n";
        }
        bool operator==(const Fruit &other)
        {
            return m_name == other.m_name &&
                    m_color == other.m_color &&
                    m_calories == other.m_calories;
        }

        std::string m_name;
        std::string m_color;
        int m_calories;
};
