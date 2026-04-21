#include "chocolate.h"

bool canBreakSlices(int height, int width, int slicesAmount)
{
    if ((slicesAmount % height == 0 || slicesAmount % width == 0) &&
        (height * width > slicesAmount))
    {
        return true;
    }
    return false;
}
