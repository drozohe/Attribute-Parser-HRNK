#pragma once
#include <memory>
#include <vector>
#include "Builder.h"

class Parser
{
private:
    std::unique_ptr<Builder> builder;

public:
    Parser();

    std::vector<Attribute> getAttributes(std::string const &input) const;
    void parse(std::string const &line);
    std::string query(std::string const &query) const;
};