#pragma once
#include <unordered_map>
#include <iostream>
#include <memory>
#include <vector>
struct Attribute
{
    std::string key;
    std::string value;
};

struct Element
{
    std::vector<Attribute> attributes;
    std::string tagName;
    std::string parentName;
    std::string fullPath;
    std::shared_ptr<Element> parent = nullptr;
    std::vector<std::shared_ptr<Element>> childElement;
    Element() = default;
};

class Builder
{
public:
    std::unordered_map<std::string, Attribute> elementsIndex;

    Builder();
    void addElement(std::string const &tagName, std::vector<Attribute> const &attributes);
    void addElementInfoToIndex(std::shared_ptr<Element> element);
    std::shared_ptr<Element> getRoot() const;
    std::shared_ptr<Element> getCurrentParent() const;
    std::shared_ptr<Element> getPreviousParent() const;
    void closeParent();

private:
    std::shared_ptr<Element> mRoot;
    std::shared_ptr<Element> mCurrentParent;
    std::shared_ptr<Element> mPreviousParent;

    void setParent(std::shared_ptr<Element> element);
};
