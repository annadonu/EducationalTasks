#include "admission.h"
#include <algorithm>
#include <map>
#include <tuple>

bool operator<(const Date& lhs, const Date& rhs)
{
    return std::tie(lhs.year, lhs.month, lhs.day) <
           std::tie(rhs.year, rhs.month, rhs.day);
}

struct ApplicantComparator
{
    bool operator()(const Applicant& lhs, const Applicant& rhs) const
    {
        if(lhs.points != rhs.points)
            return lhs.points > rhs.points;

        if(lhs.student.birthDate < rhs.student.birthDate)
            return true;
        if(rhs.student.birthDate < lhs.student.birthDate)
            return false;

        return lhs.student.name < rhs.student.name;
    }
};

struct StudentNameComparator
{
    bool operator()(const Student* lhs, const Student* rhs) const
    {
        if(lhs->name != rhs->name)
            return lhs->name < rhs->name;
        return lhs->birthDate < rhs->birthDate;
    }
};

struct IndexComparator
{
    const std::vector<Applicant>& applicants;

    bool operator()(size_t i1, size_t i2) const
    {
        const Applicant& lhs = applicants[i1];
        const Applicant& rhs = applicants[i2];
        if(lhs.points != rhs.points)
            return lhs.points > rhs.points;
        if(lhs.student.birthDate < rhs.student.birthDate)
            return true;
        if(rhs.student.birthDate < lhs.student.birthDate)
            return false;
        return lhs.student.name < rhs.student.name;
    }
};

AdmissionTable fillUniversities(const std::vector<University>& universities,
                                const std::vector<Applicant>& applicants)
{
    std::map<std::string, size_t> freePlaces;
    AdmissionTable result;

    for(size_t i = 0; i < universities.size(); i++)
        freePlaces[universities[i].name] = universities[i].maxStudents;

    std::vector<size_t> indices(applicants.size());
    for(size_t i = 0; i < applicants.size(); i++)
        indices[i] = i;

    std::sort(indices.begin(), indices.end(), IndexComparator{applicants});

    for(size_t i = 0; i < indices.size(); i++)
    {
        const Applicant& app = applicants[indices[i]];
        bool admitted = false;

        for(size_t j = 0; j < app.wishList.size() && !admitted; j++)
        {
            const std::string& uniName = app.wishList[j];
            if(freePlaces[uniName] > 0)
            {
                result[uniName].push_back(&app.student);
                freePlaces[uniName] = freePlaces[uniName] - 1;
                admitted = true;
            }
        }
    }

    for(AdmissionTable::iterator it = result.begin(); it != result.end(); it++)
    {
        std::sort(it->second.begin(), it->second.end(),
                  StudentNameComparator());
    }

    return result;
}
