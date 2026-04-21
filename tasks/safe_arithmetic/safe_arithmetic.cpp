#include "safe_arithmetic.h"

#include <limits>

bool safeAdd(int64_t a, int64_t b, int64_t& result)
{
    if(b > 0)
    {
        if(a > std::numeric_limits<int64_t>::max() - b)
            return false;
    }
    else if(b < 0)
    {
        if(a < std::numeric_limits<int64_t>::min() - b)
            return false;
    }

    result = a + b;
    return true;
}

bool safeSubtract(int64_t a, int64_t b, int64_t& result)
{
    if(b > 0)
    {
        if(a < std::numeric_limits<int64_t>::min() + b)
            return false;
    }
    else if(b < 0)
    {
        if(a > std::numeric_limits<int64_t>::max() + b)
            return false;
    }

    result = a - b;
    return true;
}

bool safeMultiply(int64_t a, int64_t b, int64_t& result)
{
    if(a == 0 || b == 0)
    {
        result = 0;
        return true;
    }

    if(a == std::numeric_limits<int64_t>::min() && b == -1)
        return false;
    if(b == std::numeric_limits<int64_t>::min() && a == -1)
        return false;

    if(b > 0)
    {
        if(a > std::numeric_limits<int64_t>::max() / b)
            return false;
        if(a < std::numeric_limits<int64_t>::min() / b)
            return false;
    }
    else if(a > 0)
    {
        if(b < std::numeric_limits<int64_t>::min() / a)
            return false;
    }
    else
    {
        if(a < std::numeric_limits<int64_t>::max() / b)
            return false;
    }

    result = a * b;
    return true;
}

bool safeDivide(int64_t a, int64_t b, int64_t& result)
{
    if(b == 0)
        return false;

    if(a == std::numeric_limits<int64_t>::min() && b == -1)
        return false;

    result = a / b;
    return true;
}
