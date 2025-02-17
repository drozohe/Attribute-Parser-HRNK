#include <unordered_map>
#include <iostream>
#include <memory>

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
    Element();
    Element(const std::string &name, const std::string &text);
};

class Builder
{
public:
    unordered_map<string, Attribute> elementsIndex;

    Builder();
    void addElement(std::string const &tagName, std::vector<Attribute> const &attributes);
    void addElementInfoToIndex(shared_ptr<Element> element);
    shared_ptr<Element> getRoot() const;
    shared_ptr<Element> getCurrentParent() const;
    shared_ptr<Element> getPreviousParent() const;
    void closeParent();
    

private:
    shared_ptr<Element> mRoot;
    shared_ptr<Element> mCurrentParent;
    shared_ptr<Element> mPreviousParent;

    void setParent(shared_ptr<Element> element);
};
