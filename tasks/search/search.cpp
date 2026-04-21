#include "search.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <sstream>

struct String
{
    std::string_view string;
    double frequencyTFIDF = 0.0;
    int counterWords = 0;
};

size_t countChar(std::string_view sv, char ch)
{
    size_t count = 0;
    for(char c: sv)
        if(c == ch)
            ++count;
    return count;
}

size_t countSubstring(std::string_view sv, std::string_view sub)
{
    if(sub.empty())
        return 0;

    size_t count = 0;
    size_t pos = 0;

    while((pos = sv.find(sub, pos)) != std::string_view::npos)
    {
        ++count;
        pos += sub.size();
    }

    return count;
}

bool stringComparator(String& lhv, String& rhv)
{
    if(lhv.frequencyTFIDF != rhv.frequencyTFIDF)
        return lhv.frequencyTFIDF > rhv.frequencyTFIDF;
    return false;
}

std::string toLowercase(std::string_view sv)
{
    std::string result;
    result.reserve(sv.size());
    for(size_t i = 0; i < sv.size(); ++i)
        result.push_back(std::tolower(sv[i]));
    return result;
}

std::vector<std::string> extractWords(std::string_view text)
{
    std::vector<std::string> words;
    size_t i = 0;
    while(i < text.size())
    {
        if(std::isalpha(text[i]))
        {
            size_t start = i;
            while(i < text.size() && std::isalpha(text[i]))
                ++i;
            std::string word(text.substr(start, i - start));
            for(size_t j = 0; j < word.size(); ++j)
                word[j] = std::tolower(word[j]);
            words.push_back(word);
        }
        else
        {
            ++i;
        }
    }
    return words;
}

std::vector<std::string_view> searchQryInText(std::string_view text,
                                              std::string_view query,
                                              size_t resultsCount)
{
    std::vector<String> textStrings;
    std::vector<std::pair<std::string, double>> queryStrings;
    std::vector<std::string_view> result;

    std::vector<std::string> queryWords = extractWords(query);

    for(size_t i = 0; i < queryWords.size(); ++i)
    {
        bool found = false;
        for(size_t j = 0; j < queryStrings.size(); ++j)
        {
            if(queryStrings[j].first == queryWords[i])
            {
                found = true;
                break;
            }
        }
        if(!found)
            queryStrings.push_back({queryWords[i], 0.0});
    }

    size_t counter = 0;
    size_t size = text.size();
    while(counter < size)
    {
        size_t indexEndOfString = text.find('\n', counter);
        if(indexEndOfString == std::string_view::npos)
            indexEndOfString = size;
        size_t length = indexEndOfString - counter;
        std::string_view newString = text.substr(counter, length);

        std::vector<std::string> lineWords = extractWords(newString);
        if(!lineWords.empty())
        {
            String newStringToPush;
            newStringToPush.string = newString;
            newStringToPush.counterWords = lineWords.size();
            textStrings.push_back(newStringToPush);
        }

        counter = indexEndOfString;
        if(counter < size && text[counter] == '\n')
            ++counter;
    }

    size_t countDocs = textStrings.size();
    for(size_t i = 0; i < queryStrings.size(); ++i)
    {
        double docCount = 0.0;
        for(size_t j = 0; j < textStrings.size(); ++j)
        {
            std::vector<std::string> lineWords =
                extractWords(textStrings[j].string);
            for(size_t k = 0; k < lineWords.size(); ++k)
            {
                if(lineWords[k] == queryStrings[i].first)
                {
                    docCount++;
                    break;
                }
            }
        }
        queryStrings[i].second = docCount;
    }

    for(size_t i = 0; i < textStrings.size(); ++i)
    {
        std::vector<std::string> lineWords =
            extractWords(textStrings[i].string);
        double totalTFIDF = 0.0;

        for(size_t j = 0; j < queryStrings.size(); ++j)
        {
            double termCount = 0.0;
            for(size_t k = 0; k < lineWords.size(); ++k)
                if(lineWords[k] == queryStrings[j].first)
                    termCount++;

            if(termCount > 0.0 && queryStrings[j].second > 0.0)
            {
                double TF = termCount / textStrings[i].counterWords;
                double IDF = std::log(countDocs / queryStrings[j].second);
                totalTFIDF += TF * IDF;
            }
        }

        textStrings[i].frequencyTFIDF = totalTFIDF;
    }

    std::vector<String> relevantStrings;
    for(size_t i = 0; i < textStrings.size(); ++i)
        if(textStrings[i].frequencyTFIDF > 0.0)
            relevantStrings.push_back(textStrings[i]);

    std::sort(relevantStrings.begin(), relevantStrings.end(), stringComparator);

    size_t numResults = resultsCount;
    if(numResults > relevantStrings.size())
        numResults = relevantStrings.size();

    for(size_t i = 0; i < numResults; ++i)
        result.push_back(relevantStrings[i].string);

    return result;
}
