#pragma once
#include "DocumentElement.hpp"
#include <vector>
#include <memory>
#include <string>

using namespace std;

class Document
{
private:
    vector<unique_ptr<DocumentElement>> elements;

public:
    Document() = default;

    // add an element take ownership
    void addElement(unique_ptr<DocumentElement> element)
    {
        elements.push_back(move(element));
    }

    // render entire document
    string getDocument() const
    {
        string result;
        for (const auto &elem : elements)
        {
            result += elem->render();
        }
        return result;
    }
};