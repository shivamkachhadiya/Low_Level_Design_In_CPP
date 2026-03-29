#include <iostream>
#include "TextElement.hpp"
#include "ImageElement.hpp"
#include "../include/Document.hpp"
using namespace std;

int main()
{
    // TextElement t("Hello, FAANG!");
    // std::cout << t.render() << std::endl;
    // ImageElement img("aaa.jpg");
    // std::cout << img.render() << std::endl;

    // make Document Object
    Document doc;
    // add text element
    doc.addElement(make_unique<TextElement>("Hello, FAANG:\n"));
    // add image element
    doc.addElement(make_unique<ImageElement>("pic.jpg\n"));
    // render full document
    cout << doc.getDocument() << endl;
}