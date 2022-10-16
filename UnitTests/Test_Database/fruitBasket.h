#pragma once

#include <vector>
#include "apple.h"
#include "pineapple.h"
#include "debug.h"

class FruitBasket : public ISerializable
{
    public:
        FruitBasket(){};
        FruitBasket(const std::string &owner,
                    size_t apples, size_t pineapples)
        {
            m_owner = owner;
            for(size_t i=0; i<apples; ++i)
            {
                m_fruits.push_back(new Apple());
            }
            for(size_t i=0; i<pineapples; ++i)
            {
                m_fruits.push_back(new PineApple());
            }
        }
        ~FruitBasket(){}

        IMPLEMENT_ISERIALIZABLE_CONST_FUNC(FruitBasket)

        QJsonObject save() const override
        {
            DEBUGLN("FruitBasket::save()");
            // Add this data to thisData
            QJsonObject thisData = ISerializable::save();

            thisData["owner"] = m_owner.c_str();

            // Get the QJsonObject of the member object
            for(size_t i=0; i<m_fruits.size(); ++i)
            {
                thisData["fruit_"+QString::number(i)] = m_fruits[i]->save();
            }
            return thisData;
        }
        bool read(const QJsonObject &reader) override
        {
            DEBUGLN("FruitBasket::read()");
            bool success = true;
            // Read the value for the base class
            success = ISerializable::read(reader);

            // Read the value for the member object
            // success &= myObject.read(thisData["myObject"]);

            // Read the values for this class
            success &= extract(reader, m_owner, "owner");

            bool finishReading = false;
            int count = 0;

            Apple appleBuilder;
            PineApple pineappleBuilder;

            while(!finishReading)
            {
                QJsonObject fruit = reader["fruit_"+QString::number(count)].toObject();
                if(fruit.isEmpty())
                {
                    finishReading = true;
                    break;
                }
                if(extractClassName(fruit) == appleBuilder.className())
                {
                    Apple *newApple = appleBuilder.clone(fruit);
                    if(!newApple)
                    {
                        WARNING("Can't clone apple");
                    }
                    else
                        m_fruits.push_back(newApple);
                }else if(extractClassName(fruit) == pineappleBuilder.className())
                {
                    PineApple *newPinapple = pineappleBuilder.clone(fruit);
                    if(!newPinapple)
                    {
                        WARNING("Can't clone PineApple");
                    }
                    else
                        m_fruits.push_back(newPinapple);
                }else
                    success = false;
                ++count;
            }
            return success;
        }
        void postLoad() override
        {
            print();
            //getObject<FruitBasket>("d");
        }
        void print() const
        {
            DEBUGLN("Basket from "<<m_owner<<" with: "<<m_fruits.size()<<" fruits:");
            for(size_t i=0; i<m_fruits.size(); ++i)
            {
                DEBUGLN("Fruit ["+std::to_string(i)+"]");
                DEBUG(m_fruits[i]->toString());
            }
            DEBUGLN("--------------------");
        }
        bool operator==(const FruitBasket &other)
        {
            bool equalFruits = m_fruits.size() == other.m_fruits.size();
            if(equalFruits)
            {
                for(size_t i=0; i<m_fruits.size(); ++i)
                {
                    bool match = false;
                    for(size_t j=0; j<other.m_fruits.size(); ++j)
                    {
                        if(m_fruits[i]->operator==(*other.m_fruits[j]))
                        {
                            match = true;
                        }
                    }
                    equalFruits &= match;
                    if(!match)
                    {
                        DEBUGLN(" NOT EQUAL: i="<<i);
                        print();
                        other.print();
                    }
                }
            }

            return m_owner == other.m_owner &&
                   equalFruits;
        }

        std::string m_owner;
        std::vector<Fruit*> m_fruits;
};
