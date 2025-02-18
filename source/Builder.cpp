#include "Builder.h"

using namespace std;
Builder::Builder() : mRoot(std::make_shared<Element>()), mCurrentParent(mRoot)
{
    mRoot->tagName = "root";
    mRoot->parentName = "";
    mRoot->fullPath = "root";
    mRoot->parent = nullptr;
}
void Builder::addElement(std::string const &tagName, std::vector<Attribute> const &attributes)
{
    auto child = make_shared<Element>();
    child->tagName = tagName;
    child->parentName = mCurrentParent->tagName;
    child->parent = mCurrentParent;
    child->fullPath = mCurrentParent->fullPath + "." + tagName;
    child->attributes = attributes;

    mCurrentParent->childElement.push_back(child);
    addElementInfoToIndex(child);
    setParent(child);
}
void Builder::addElementInfoToIndex(shared_ptr<Element> element)
{
    for (const auto &attribute : element->attributes)
    {
        std::string key = element->fullPath.substr(5) + "~" + attribute.key;
        elementsIndex.emplace(key, attribute);
    }
}
shared_ptr<Element> Builder::getRoot() const
{
    return mRoot;
}
shared_ptr<Element> Builder::getCurrentParent() const
{
    return mCurrentParent;
}
shared_ptr<Element> Builder::getPreviousParent() const
{
    return mPreviousParent;
}
void Builder::closeParent() 
{
    if (mCurrentParent->tagName == "root")
    {
        return;
    }
    setParent(mPreviousParent);
}
void Builder::setParent(shared_ptr<Element> element)
{
    mCurrentParent = element;
    mPreviousParent = element->parent;
}