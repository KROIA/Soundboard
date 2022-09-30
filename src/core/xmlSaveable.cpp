#include "xmlSaveable.h"


bool XmlSaveable::toBool(const QString &str)
{
    if(str.size() == 0)
        return false;
    if(str.toLower().indexOf("true") != -1) return true;
    if(str.toLower().indexOf("1") != -1) return true;
    return false;
}
QString XmlSaveable::fromBool(bool value)
{
    return value ? "true" : "false";
}
