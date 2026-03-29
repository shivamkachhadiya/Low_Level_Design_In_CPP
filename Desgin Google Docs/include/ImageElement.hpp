#pragma once
#include "DocumentElement.hpp"
#include <string>
#include <string_view>
#include <stdexcept>

class ImageElement : public DocumentElement
{
private:
    std::string imagePath;

public:
    explicit ImageElement(std::string_view path)
        : imagePath(std::string(path))
    {
        if (imagePath.empty())
        {
            throw std::invalid_argument("iamge path can not be empty");
        }
    }
    std::string render() const override
    {
        return "[Image: " + imagePath + "]";
    }
};