#ifndef USERINFO_H
#define USERINFO_H

#include <string>

class QJsonObject;

/// A class which stores information about Player
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
