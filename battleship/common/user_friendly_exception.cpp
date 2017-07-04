#include "user_friendly_exception.h"

UserFriendlyException::UserFriendlyException(const std::string& s)
    : std::runtime_error{s}
{
    
}
