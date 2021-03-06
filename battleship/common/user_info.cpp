#include "user_info.h"
#include <QJsonObject>

UserInfo::UserInfo::UserInfo()
    : name{"uninitialized"}, age{-1}
{
}

UserInfo::UserInfo(const std::string& name, int age)
    : name{name}, age{age}
{
}

UserInfo::UserInfo(const QJsonObject& json)
    : name{ json["name"].toString().toStdString() }, age{ json["age"].toInt() }
{
    
}

const std::string & UserInfo::getName() const
{
    return name;
}

int UserInfo::getAge() const
{
    return age;
}


QJsonObject UserInfo::toJson() const
{
    return QJsonObject {
        {"name", QString::fromStdString(name)},
        {"age", age}
    };
}


