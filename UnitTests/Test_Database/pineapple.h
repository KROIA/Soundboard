#include "fruit.h"

class PineApple: public Fruit
{
    public:
        PineApple() : Fruit()
        {
            m_name = "PineApple";
            m_color = "yellow";
            m_calories = 31;
            m_radius = 3;
            m_height = 5;
        }
        IMPLEMENT_ISERIALIZABLE_CONST_FUNC(PineApple)

        QJsonObject save() const override
        {
            DEBUGLN("PineApple::save()");
            // Add this data to thisData
            QJsonObject thisData = combine(Fruit::save(),
            QJsonObject
            {
                // Add the properties of this object here
                // Do not take the same keyvalues two times,
                // also not the keys of the base class
                {"radius", m_radius},
                {"height", m_height},
            });

            // Get the QJsonObject of the member object
            //thisData["myObject"] = myObject.save();

            return thisData;
        }
        bool read(const QJsonObject &reader) override
        {
            DEBUGLN("PineApple::read()");
            bool success = true;
            // Read the value for the base class
            success = Fruit::read(reader);

            // Read the value for the member object
            // success &= myObject.read(thisData["myObject"]);

            // Read the values for this class
            success &= extract(reader,m_radius, "radius");
            success &= extract(reader,m_height, "height");
            return success;
        }
        void postLoad() override
        {

        }

        std::string toString() override
        {
            std::string str = Fruit::toString();
            str += "radius:   "+std::to_string(m_radius)+"\n";
            str += "height:   "+std::to_string(m_height)+"\n";
            return str;
        }
        bool operator==(const PineApple &other)
        {
            return m_radius == other.m_radius &&
                   m_height == other.m_height &&
                   Fruit::operator==(other);
        }

        int m_radius;
        int m_height;

};
