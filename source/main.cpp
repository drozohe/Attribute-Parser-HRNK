#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Builder.h"
#include "Parser.h"

using namespace std;

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