#include "palindrome.h"

bool isPalindrome(const std::string& str)
{
    int start = 0;
    int end = str.length() - 1;
    while(start < end)
    {
        while(start < end && str[start] == ' ')
        {
            start++;
        }
        while(start < end && str[end] == ' ')
        {
            end--;
        }
        if(str[start] != str[end])
        {
            return false;
        }
        start++;
        end--;
    }
    return true;
}
