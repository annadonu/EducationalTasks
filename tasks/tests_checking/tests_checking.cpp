#include "tests_checking.h"
#include <deque>

std::vector<std::string>
studentsOrder(const std::vector<StudentAction>& studentActions,
              const std::vector<size_t>& queries)
{
    std::deque<std::string> dequeNames;
    std::vector<std::string> result;

    for(size_t i = 0; i < studentActions.size(); i++)
        if(studentActions[i].side == Side::top)
            dequeNames.push_front(studentActions[i].name);
        else
            dequeNames.push_back(studentActions[i].name);

    for(size_t i = 0; i < queries.size(); i++)
        result.push_back(dequeNames[queries[i] - 1]);

    return result;
}
