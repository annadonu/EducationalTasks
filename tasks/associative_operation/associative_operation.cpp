#include "associative_operation.h"

bool isAssociative(const std::vector<std::vector<size_t>>& table)
{
    size_t size = table.size();

    for(size_t i = 0; i < size; i++)
    {
        for(size_t j = 0; j < size; j++)
        {
            for(size_t k = 0; k < size; k++)
            {
                size_t leftResult = table[table[i][j]][k];
                size_t rightResult = table[i][table[j][k]];
                if(leftResult != rightResult)
                {
                    return false;
                }
            }
        }
    }

    return true;
}
