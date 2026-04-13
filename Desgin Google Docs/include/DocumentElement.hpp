#pragma once
#include <string>
using namespace std;
class DocumentElement
{
public:
    virtual ~DocumentElement() = default;
    virtual string render() const = 0;
};
