#include "fibonacci.h"

int64_t calculateNthFibonacci(int64_t n)
{
    int64_t prev1 = 0;
    int64_t prev2 = 1;
    int64_t ans = 0;

    if(n == 0)
    {
        return prev1;
    }
    if(n == 1)
    {
        return prev2;
    }
    for(int64_t i = 2; i <= n; i++)
    {
        ans = prev1 + prev2;
        prev1 = prev2;
        prev2 = ans;
    }
    return ans;
}
