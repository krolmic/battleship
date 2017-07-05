#ifndef USERINFO_H
#define USERINFO_H

#include <string>

class QJsonObject;

class UserInfo
{
public:
    UserInfo();
    UserInfo(const std::string& name, int age);
    UserInfo(const QJsonObject& json);
    QJsonObject toJson() const;
    
    const std::string& getName() const;
    int getAge() const;
    
private:
    std::string name;
    int age;
};

#endif // USERINFO_H
