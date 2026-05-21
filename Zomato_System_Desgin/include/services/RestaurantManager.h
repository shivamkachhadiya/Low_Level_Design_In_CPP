//
// Created by shiva on 21-05-2026.
//
#pragma once
#include <vector>
#include <string>
#include "../models/Restaurant.h"
#ifndef LOW_LEVEL_DESIGN_CPP_RESTAURANTMANAGER_H
#define LOW_LEVEL_DESIGN_CPP_RESTAURANTMANAGER_H

#endif //LOW_LEVEL_DESIGN_CPP_RESTAURANTMANAGER_H

class RestaurantManager {
private:
    // (1) Singleton — private constructor
    RestaurantManager() {}

    // (2) deleted copy constructor and assignment operator
    RestaurantManager(const RestaurantManager&) = delete;
    RestaurantManager& operator=(const RestaurantManager&) = delete;

    // (3) static instance — lives entire program lifetime
    static RestaurantManager* instance;

    // (4) data
    std::vector<Restaurant> restaurants;

public:
    // (5) Global access point
    static RestaurantManager* getInstance() {
        if (instance == nullptr) {          // (6) create only if not exists
            instance = new RestaurantManager();
        }
        return instance;
    }

    // (7) Add restaurant
    void addRestaurant(const Restaurant& r) {
        restaurants.push_back(r);
    }

    // (8) Search by location
    std::vector<Restaurant> searchByLoc(const std::string& loc) {
        std::vector<Restaurant> result;
        for (const auto& r : restaurants) {
            if (r.getLoc() == loc) {        // (9) match location
                result.push_back(r);
            }
        }
        return result;
    }

    const std::vector<Restaurant>& getRestaurants() const { return restaurants; }
};

// (10) static member must be defined outside class
RestaurantManager* RestaurantManager::instance = nullptr;