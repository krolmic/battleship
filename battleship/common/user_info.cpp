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
    QJsonObject json{};
    json["name"] = QString::fromStdString(name);
    json["age"] = age;
    return json;
}


