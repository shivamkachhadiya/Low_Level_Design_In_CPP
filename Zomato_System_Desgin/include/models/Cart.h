//
// Created by shiva on 19-05-2026.
//
#pragma once
#ifndef LOW_LEVEL_DESIGN_CPP_CART_H
#define LOW_LEVEL_DESIGN_CPP_CART_H
// From your UML:
// Cart
// - r : Restaurant*
// - items : Vector<MenuItem>
// - addToCart(MenuItem)
// - totalCost()
// - isEmpty()
#endif //LOW_LEVEL_DESIGN_CPP_CART_H

#include<vector>
#include "MenuItem.h"
#include "Restaurant.h"

class Cart {
private:
    Restaurant* r;                      // (1) RAW POINTER — cart belongs to one restaurant
    std::vector<MenuItem>items;         // (2) items user selected
public:
    // (3) Constructor — takes a restaurant pointer
    Cart():r(nullptr){}                 // (4) default — empty cart, no restaurant yet


    // (5) Set which restaurant this cart belongs to
    void setRestaurant(Restaurant* rest) {
        r=rest;
    }

    Restaurant* getRestaurant()const {
        return r;
    }

    // (6) Add item to cart

    void addToCart(const MenuItem& item) {
        items.push_back(item);
    }

    // (7) Calculate total price

    int totalCost()const {
        int total=0;
        for (const auto& item:items) {
            total+=item.getPrice();
        }
        return total;
    }

    bool isEmpty()const {
        return items.empty();
    }

    const std::vector<MenuItem>&getItems()const {
        return items;
    }
};