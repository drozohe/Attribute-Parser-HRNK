# Attribute Parser

This project implements a parser for a simplified version of XML called HRML (Hackerrank Markup Language). The parser reads HRML lines, extracts attributes, and answers queries about these attributes.

## Problem Description

The goal is to parse a series of HRML lines and then answer queries about the attributes of the tags. HRML consists of nested tags with attributes, similar to XML. The parser should be able to handle opening and closing tags, extract attributes, and respond to queries about these attributes.

You can find the full problem description on HackerRank: [Attribute Parser](https://www.hackerrank.com/challenges/attribute-parser/problem?isFullScreen=true)

## Input Format

1. The first line contains two integers, `n` and `q`, separated by a space.
   - `n`: The number of HRML lines.
   - `q`: The number of queries.

2. The next `n` lines contain the HRML code.
3. The next `q` lines contain the queries.

## Output Format

For each query, print the value of the attribute if it exists, or "Not Found!" if it does not.

## Example
`4 3`
`<a value = "GoodVal">`
`<b value = "BadVal" size = "10">`
`</b>`
`</a>`
`a~value`
`a.b~size`
`a.b~value`

### Output
`GoodVal`
`10`
`BadVal`

## Project Structure

- `main.cpp`: The main entry point of the application. It handles input and output, and uses the `Parser` class to parse HRML lines and answer queries.
- `Builder.h` and `Builder.cpp`: Defines the `Builder` class, which manages the hierarchy of HRML elements and stores attributes.
- `Parser.h` and `Parser.cpp`: Defines the `Parser` class, which parses HRML lines, extracts attributes, and answers queries.

## Classes and Methods

### `Attribute` Struct
Represents an attribute with a key and a value.

### `Element` Struct
Represents an HRML element with:
- A list of attributes.
- A tag name.
- A parent element.
- A list of child elements.
- A full path representing the hierarchy.

### `Builder` Class
Manages the hierarchy of HRML elements and stores attributes.
- `Builder()`: Constructor to initialize the root element.
- `void addElement(const std::string &tagName, const std::vector<Attribute> &attributes)`: Adds a new element to the hierarchy.
- `void addElementInfoToIndex(std::shared_ptr<Element> element)`: Adds element attributes to the index.
- `std::shared_ptr<Element> getRoot() const`: Returns the root element.
- `std::shared_ptr<Element> getCurrentParent() const`: Returns the current parent element.
- `std::shared_ptr<Element> getPreviousParent() const`: Returns the previous parent element.
- `void closeParent()`: Closes the current parent element.

### `Parser` Class
Parses HRML lines, extracts attributes, and answers queries.
- `Parser()`: Constructor to initialize the builder.
- `std::vector<Attribute> getAttributes(const std::string &input) const`: Extracts attributes from a line.
- `void parse(const std::string &line)`: Parses an HRML line.
- `std::string query(const std::string &query) const`: Answers a query about an attribute.

## How the Program Works

### Approach

The program uses a `Parser` class to read HRML lines and extract attributes. The `Parser` class uses a `Builder` class to manage the hierarchy of elements and store attributes. The `Builder` class maintains a tree structure of elements, where each element can have multiple child elements and a single parent element.

### Handling Parents and Paths

1. **Root Element**: The `Builder` class initializes a root element with the tag name "root". This root element serves as the starting point for the hierarchy.

2. **Adding Elements**: When a new element is encountered, the `Builder` class creates a new `Element` object and sets its parent to the current parent element. The new element is then added to the list of child elements of the current parent.

3. **Full Path**: Each element has a `fullPath` attribute that represents its position in the hierarchy. The `fullPath` is constructed by concatenating the `fullPath` of the parent element with the tag name of the new element.

4. **Closing Elements**: When a closing tag is encountered, the `Builder` class updates the current parent to the previous parent element, effectively moving up one level in the hierarchy.

5. **Indexing Attributes**: The `Builder` class maintains an index of attributes using a map. The key for each attribute is constructed by concatenating the `fullPath` of the element with the attribute key, separated by a tilde (`~`). This allows for efficient querying of attributes.

### Querying Attributes

The `Parser` class provides a `query` method that takes a query string and returns the value of the corresponding attribute. The query string is used to look up the attribute in the index maintained by the `Builder` class. If the attribute is found, its value is returned; otherwise, "Not Found!" is returned.

## How to Run

1. Compile the project using a C++ compiler.
2. Run the executable and provide input as described in the input format.

## Example Usage

```sh
g++ -o attribute_parser main.cpp Builder.cpp Parser.cpp
./attribute_parser
```

Provide the input as specified, and the program will output the results for the queries.

License
This project is licensed under the MIT License.