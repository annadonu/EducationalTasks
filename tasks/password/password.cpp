#include "password.h"
#include <cctype>

bool validatePassword(const std::string& password)
{
    size_t len = password.length();
    int flUpper = 0;
    int flLower = 0;
    int flNum = 0;
    int flSymb = 0;

    if(len < 8 || len > 14)
    {
        return false;
    }

    for(size_t i = 0; i < len; i++)
    {
        if(password[i] < '!' || password[i] > '~')
        {
            return false;
        }
        if(std::isdigit(password[i]))
        {
            flNum = 1;
        }
        else if(std::islower(password[i]))
        {
            flLower = 1;
        }
        else if(std::isupper(password[i]))
        {
            flUpper = 1;
        }
        else
        {
            flSymb = 1;
        }
    }
    if(flLower + flNum + flSymb + flUpper < 3)
    {
        return false;
    }
    return true;
}
