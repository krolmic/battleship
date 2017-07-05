#ifndef USERFRIENDLYEXCEPTION_H
#define USERFRIENDLYEXCEPTION_H

#include <stdexcept>


/// this kind of exception is intended to inform user with message in GUI form, like QMessageBox
class UserFriendlyException : public std::runtime_error
{
public:
    UserFriendlyException(const std::string& s);
};

#endif // USERFRIENDLYEXCEPTION_H
