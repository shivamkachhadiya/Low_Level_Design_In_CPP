//
// Created by shiva on 19-05-2026.
//
#pragma once
//""""""""THODA MUSKIL LAG RHA HEI BUT SAMAJANA JARURI HEI""""""""""""""""""""""""
//""""""""THODA MUSKIL LAG RHA HEI BUT SAMAJANA JARURI HEI""""""""""""""""""""""""
#ifndef LOW_LEVEL_DESIGN_CPP_RESTAURANT_H
#define LOW_LEVEL_DESIGN_CPP_RESTAURANT_H

#endif //LOW_LEVEL_DESIGN_CPP_RESTAURANT_H
// From UML:
// Restaurant  <<Model>>
// - restaurantId : int
// - name : String
// - loc : String
// - menu : Vector<MenuItem>

#include<string>
#include<vector>
#include "MenuItem.h"               // (1) relative path include — MenuItem is a dependency

class Restaurant {
private:
    int restaurentId;               // (2) unique ID for each restaurant
    std::string name;
    std::string loc;                // (3) location
    std::vector<MenuItem>menu;      // (4) owns a list of MenuItems — composition

public:
    // (5) Constructor

    Restaurant(int id,std::string name,std::string loc)
    :restaurentId(id),name(name),loc(loc){}

    // (6) Getters

    int getId()const {
        return restaurentId;
    }
    const std::string& getName()const {
        return name;
    }
    const std::string& getLoc()const {
        return loc;
    }
    const std::vector<MenuItem>&getMenu()const {
        return menu;
    }

    // (7) Add item to this restaurant's menu

    void addMenuItem(const MenuItem& item) {
        menu.push_back(item);        // (8) push_back adds to end of vector
    }
};

