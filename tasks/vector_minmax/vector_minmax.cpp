#include "vector_minmax.h"

std::pair<IntVectorCIt, IntVectorCIt> iVectorMinMax(IntVectorCIt first,
                                                    IntVectorCIt last)
{
    if(first == last)
        return {first, first};

    IntVectorCIt min = first;
    IntVectorCIt max = first;

    for(IntVectorCIt it = first + 1; it != last; ++it)
    {
        if(*min > *it)
            min = it;
        if(*max < *it)
            max = it;
    }

    return {min, max};
}
