#include "unixpath.h"
#include <deque>

void addComponents(std::string_view path, std::deque<std::string>& components)
{
    size_t start = 0;
    size_t end = path.find('/');

    while(end != std::string_view::npos)
    {
        if(end > start)
            components.push_back(std::string(path.substr(start, end - start)));
        start = end + 1;
        end = path.find('/', start);
    }

    if(start < path.size())
        components.push_back(std::string(path.substr(start)));
}

std::string normalizePath(std::string_view currentWorkingDir,
                          std::string_view path)
{
    std::deque<std::string> components;
    std::deque<std::string> normalized;
    std::string result;

    if(!currentWorkingDir.empty() && currentWorkingDir[0] == '/')
        addComponents(currentWorkingDir.substr(1), components);

    if(!path.empty())
    {
        if(path[0] == '/')
        {
            components.clear();
            addComponents(path.substr(1), components);
        }
        else
        {
            addComponents(path, components);
        }
    }

    for(const std::string& comp: components)
    {
        if(comp == "..")
        {
            if(!normalized.empty())
                normalized.pop_back();
        }
        else if(comp != "." && !comp.empty())
        {
            normalized.push_back(comp);
        }
    }

    if(normalized.empty())
        return "/";

    for(const std::string& comp: normalized)
        result += "/" + comp;

    return result;
}
