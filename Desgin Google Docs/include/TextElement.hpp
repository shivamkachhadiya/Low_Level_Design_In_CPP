#pragma once
#include "DocumentElement.hpp"
#include <string>
#include <string_view>

class TextElement : public DocumentElement
{
private:
    std::string text;

public:
    explicit TextElement(std::string_view t)
        : text(std::string(t)) {} // Convert string_view to string safely

    std::string render() const override
    {
        return text;
    }
};