#include "scorer.h"
#include <set>

bool eventCompare(const Event* lhs, const Event* rhs)
{
    return lhs->time < rhs->time;
}

using StudentTaskSubset = std::set<const Event*, decltype(eventCompare)*>;

StudentTaskSubset createStudentTaskSet(const Events& events,
                                       const StudentName& studentName,
                                       const TaskName& taskName,
                                       time_t scoreTime)
{
    StudentTaskSubset result(eventCompare);
    for(const Event& event: events)
    {
        if(event.studentName == studentName && event.taskName == taskName &&
           event.time <= scoreTime)
        {
            result.insert(&event);
        }
    }
    return result;
}

bool isTaskScored(const StudentTaskSubset& subset)
{
    bool hasSuccess = false;
    bool mergeOpen = false;

    for(const Event* eventPtr: subset)
        if(eventPtr->eventType == EventType::checkSuccess)
            hasSuccess = true;
        else if(eventPtr->eventType == EventType::checkFailed)
            hasSuccess = false;
        else if(eventPtr->eventType == EventType::mergeRequestOpen)
            mergeOpen = true;
        else if(eventPtr->eventType == EventType::mergeRequestClosed)
            mergeOpen = false;
    return hasSuccess && !mergeOpen;
}

ScoreTable getScoredStudents(const Events& events, time_t scoreTime)
{
    ScoreTable result;
    std::set<StudentName> uniqueStudents;
    std::set<TaskName> uniqueTasks;

    for(const Event& event: events)
    {
        uniqueStudents.insert(event.studentName);
        uniqueTasks.insert(event.taskName);
    }

    for(const StudentName& student: uniqueStudents)
    {
        for(const TaskName& task: uniqueTasks)
        {
            StudentTaskSubset taskEvents =
                createStudentTaskSet(events, student, task, scoreTime);
            if(isTaskScored(taskEvents))
                result[student].insert(task);
        }
        if(result.find(student) != result.end() && result[student].empty())
            result.erase(student);
    }

    return result;
}
