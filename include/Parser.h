#pragma once
#include <memory>
#include <vector>
#include "Builder.h"

class Parser
{
private:
    unique_ptr<Builder> builder;

public:
    Parser();

    vector<Attribute> getAttributes(std::string const &input) const;
    void parse(string const &line);
    string query(string const &query) const;
};