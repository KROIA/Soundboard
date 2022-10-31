#include "fruit.h"

class Apple: public Fruit
{
    public:
        Apple() : Fruit()
        {
            m_name = "Apple";
            m_color = "red";
            m_calories = 25;
            m_radius = 2;
        }
        IMPLEMENT_ISERIALIZABLE_CONST_FUNC(Apple)

        QJsonObject save() const override
        {
            DEBUGLN("Apple::save()");
            // Add this data to thisData
            QJsonObject thisData = combine(Fruit::save(),
            QJsonObject
            {
                // Add the properties of this object here
                // Do not take the same keyvalues two times,
                // also not the keys of the base class
                {"radius", m_radius},
            });

            // Get the QJsonObject of the member object
            //thisData["myObject"] = myObject.save();

            return thisData;
        }
        bool read(const QJsonObject &reader) override
        {
            DEBUGLN("Apple::read()");
            bool success = true;
            // Read the value for the base class
            success = Fruit::read(reader);

            // Read the value for the member object
            // success &= myObject.read(thisData["myObject"]);

            // Read the values for this class
            success &= extract(reader,m_radius, "radius");
            return success;
        }
        void postLoad() override
        {

        }

        std::string toString() override
        {
            std::string str = Fruit::toString();
            str += "radius:   "+std::to_string(m_radius)+"\n";
            return str;
        }
        bool operator==(const Apple &other)
        {
            return m_radius == other.m_radius &&
                   Fruit::operator==(other);
        }

        int m_radius;
};
