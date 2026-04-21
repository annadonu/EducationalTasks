#include "provinces.h"

int64_t countPassports(const std::vector<int>& provinces)
{
    if(provinces.empty())
        return 0;

    int64_t sumPassports = 0;
    std::multiset<int64_t> result(provinces.begin(), provinces.end());

    while(result.size() != 1)
    {
        std::multiset<int64_t>::iterator it = result.begin();
        int64_t firstProvince;
        int64_t secondProvince;

        firstProvince = *it;
        result.erase(it);

        it = result.begin();
        secondProvince = *it;
        result.erase(it);

        sumPassports += firstProvince + secondProvince;
        result.insert(firstProvince + secondProvince);
    }

    return sumPassports;
}
