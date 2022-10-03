#pragma once

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>

class XmlSaveable
{
    public:
        virtual void save(QXmlStreamWriter *writer) = 0;
        virtual void load(QXmlStreamReader *reader) = 0;

        static bool toBool(const QString &str);
        static QString fromBool(bool value);

    private:

};
