#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <memory>
#include <unordered_map>
#include <regex>

using namespace std;

struct Attribute
{
    string key;
    string value;
};

struct Element
{
    std::vector<Attribute> attributes;
    string tagName;
    string parentName;
    string fullPath;
    shared_ptr<Element> parent = nullptr;
    std::vector<shared_ptr<Element>> childElement;
    Element()
    {
        // cout << "ctor called" << endl;
    }

    Element(const std::string &name, const std::string &text)
    {
        // cout << "ctor called with name and text" << endl;
    }
};

class Builder
{
public:
    unordered_map<string, Attribute> elementsIndex;

    Builder()
    {
        mRoot = make_shared<Element>();
        mRoot->tagName = "root";
        mRoot->parentName = "";
        mRoot->fullPath = "root";
        mRoot->parent = nullptr;

        mCurrentParent = mRoot;
    }

    void addElement(std::string const &tagName, std::vector<Attribute> const &attributes)
    {
        auto child = make_shared<Element>();
        child->tagName = tagName;
        child->parentName = mCurrentParent->tagName;
        child->parent = mCurrentParent;
        child->fullPath = mCurrentParent->fullPath + "." + tagName;
        for (auto const &attribute : attributes)
        {
            child->attributes.push_back(attribute);
        }

        mCurrentParent->childElement.push_back(child);
        addElementInfoToIndex(child);
        setParent(child);
    }

    void addElementInfoToIndex(shared_ptr<Element> element)
    {
        for (auto const &attribute : element->attributes)
        {
            if (element->fullPath.find("root.") != string::npos)
            {
                elementsIndex.emplace(make_pair(element->fullPath.substr(5) + "~" + attribute.key, attribute));
            }
            else
            {
                elementsIndex.emplace(make_pair(element->fullPath + "~" + attribute.key, attribute));
            }
        }
    }

    shared_ptr<Element> getRoot() const
    {
        return mRoot;
    }

    shared_ptr<Element> getCurrentParent() const
    {
        return mCurrentParent;
    }

    shared_ptr<Element> getPreviousParent() const
    {
        return mPreviousParent;
    }

    void closeParent()
    {
        if (mCurrentParent->tagName == "root")
        {
            return;
        }
        setParent(mPreviousParent);
    }

private:
    shared_ptr<Element> mRoot;
    shared_ptr<Element> mCurrentParent;
    shared_ptr<Element> mPreviousParent;

    void setParent(shared_ptr<Element> element)
    {
        mCurrentParent = element;
        mPreviousParent = element->parent;
    }
};

class Parser
{
private:
    unique_ptr<Builder> builder;

public:
    Parser() : builder(make_unique<Builder>())
    {
    }

    vector<Attribute> getAttributes(std::string const &input) const
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

    void parse(string const &line)
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

    string query(string const &query) const
    {
        auto it = builder->elementsIndex.find(query);
        if (it != builder->elementsIndex.end())
        {
            return it->second.value;
        }
        return "Not Found!";
    }
};

int main()
{
    int n = 0;
    int q = 0;

#ifdef _DEBUG
    vector<string> inputLines{
        R"(<a value = "GoodVal">)",
        R"(<b value = "BadVal" size = "10">)",
        R"(</b>)",
        R"(<c height = "auto">)",
        R"(<d size = "3">)",
        R"(<e strength = "2">)",
        R"(</e>)",
        R"(</d>)",
        R"(</c>)",
        R"(</a>)"};
#else
    vector<string> inputLines{};
    std::cin >> n >> q;
    std::cin.ignore();
    for (int i = 0; i < n; i++)
    {
        std::string line;
        std::getline(std::cin, line);
        inputLines.push_back(line);
    }
#endif // _DEBUG

    auto parser = make_unique<Parser>();

    // Parse HRML
    for (auto const &line : inputLines)
    {
        parser->parse(line);
    }

#ifdef _DEBUG
    vector<string> queries{
        "a~value",
        "b~value",
        "a.b~size",
        "a.b~value",
        "a.b.c~height",
        "a.c~height",
        "a.d.e~strength",
        "a.c.d.e~strength",
        "d~sze{-truncated-}",
        "a.c.d~size"};

    // Process queries
    for (auto const &query : queries)
    {
        std::cout << parser->query(query) << std::endl;
    }
#else
    // Process queries
    for (int i = 0; i < q; i++)
    {
        std::string query;
        std::getline(std::cin, query);
        std::cout << parser->query(query) << std::endl;
    }
#endif // _DEBUG

    return 0;
}