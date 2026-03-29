#include <iostream>
#include "TextElement.hpp"
#include "ImageElement.hpp"

int main()
{
    // TextElement t("Hello, FAANG!");
    // std::cout << t.render() << std::endl;
    ImageElement img("aaa.jpg");
    std::cout << img.render() << std::endl;
}