#include "Builder.h"

Builder::Builder()
{
    mRoot = make_shared<Element>();
    mRoot->tagName = "root";
    mRoot->parentName = "";
    mRoot->fullPath = "root";
    mRoot->parent = nullptr;

    mCurrentParent = mRoot;
}
void Builder::addElement(std::string const &tagName, std::vector<Attribute> const &attributes)
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
void Builder::addElementInfoToIndex(shared_ptr<Element> element)
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
Element::Element()
{
    // cout << "ctor called" << endl;
}
Element::Element(const std::string &name, const std::string &text)
{
    // cout << "ctor called with name and text" << endl;
}
