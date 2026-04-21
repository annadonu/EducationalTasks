#include "sort_students.h"
#include <algorithm>
#include <tuple>

bool operator<(const Date& lhs, const Date& rhs)
{
    return std::tie(lhs.year, lhs.month, lhs.day) <
           std::tie(rhs.year, rhs.month, rhs.day);
}

bool compareByDate(const Student& lhs, const Student& rhs)
{
    return std::tie(lhs.birthDate, lhs.lastName, lhs.name) <
           std::tie(rhs.birthDate, rhs.lastName, rhs.name);
}

bool compareByName(const Student& lhs, const Student& rhs)
{
    return std::tie(lhs.lastName, lhs.name, lhs.birthDate) <
           std::tie(rhs.lastName, rhs.name, rhs.birthDate);
}

void sortStudents(std::vector<Student>& students, SortKind sortKind)
{
    if(sortKind == SortKind::date)
        std::sort(students.begin(), students.end(), compareByDate);
    else
        std::sort(students.begin(), students.end(), compareByName);
}
