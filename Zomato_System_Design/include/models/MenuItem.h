//
// Created by shiva on 19-05-2026.
//
#pragma once
#ifndef LOW_LEVEL_DESIGN_CPP_MENUITEM_H
#define LOW_LEVEL_DESIGN_CPP_MENUITEM_H

#endif //LOW_LEVEL_DESIGN_CPP_MENUITEM_H
//idea of uml
// MenuItem
// - code  : String
// - name  : String
// - price : int

#include<string>
using namespace std;

class MenuItem {
private:
    string code;
    string name;
    int price;
public:
    //constructor initialize all member list

    MenuItem(string code,string name,int price):code(code),name(name),price(price){}

    //Getters — return const reference to avoid copying strings
    const string& getCode()const {
        return code;
    }
    const string& getName()const {
        return name;
    }
    int getPrice()const {
        return price;
    }

    //Setters allow modification after creation
    void setCode(const string& c) {
        code=c;
    }
    void setName(const string& n) {
        name=n;
    }
    void setPrice(int p) {
        price=p;
    }
};

// const string& — returns a reference (no copy) and const means caller can't modify it.
// The "const" at the end of the function means "this function does not modify the object".
// This is important for correct const-correctness in C++.