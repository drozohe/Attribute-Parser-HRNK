#include "Parser.h"
#include <regex>
using namespace std;

Parser::Parser() : builder(make_unique<Builder>())
{
}

vector<Attribute> Parser::getAttributes(std::string const &input) const
{
    std::vector<Attribute> attributes;

    std::regex pattern(R"(\b([\w-]+)\s*=\s*\"([^\"]*)\")");
    std::sregex_iterator it(input.begin(), input.end(), pattern);
    std::sregex_iterator end;

    while (it != end)
    {
        attributes.push_back({(*it)[1].str(), (*it)[2].str()});
        ++it;
    }

    return attributes;
}
void Parser::parse(string const &line)
{
    if (line.empty())
    {
        return;
    }

    std::string tagName;
    std::regex closingTagPattern(R"(<\/(\w+)\s*>)");
    std::smatch closingMatch;

    if (std::regex_match(line, closingMatch, closingTagPattern))
    {
        tagName = closingMatch[1].str();
        builder->closeParent();
        return;
    }

    std::regex openingPattern(R"(<(\w+)([^>]*)>)");
    std::smatch openingMatch;

    if (std::regex_search(line, openingMatch, openingPattern))
    {
        tagName = openingMatch[1];
    }

    builder->addElement(tagName, getAttributes(line));
}

string Parser::query(string const &query) const
{
    auto it = builder->elementsIndex.find(query);
    if (it != builder->elementsIndex.end())
    {
        return it->second.value;
    }
    return "Not Found!";
}
