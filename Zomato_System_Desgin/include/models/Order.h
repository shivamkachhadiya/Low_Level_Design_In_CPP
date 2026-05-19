//
// Created by shiva on 19-05-2026.
//
#pragma once

#ifndef LOW_LEVEL_DESIGN_CPP_ORDER_H
#define LOW_LEVEL_DESIGN_CPP_ORDER_H

#endif //LOW_LEVEL_DESIGN_CPP_ORDER_H

// Order
// - id : int
// - user : User
// - restaurant : Restaurant*
// - items : Vector<MenuItem>
// - strategy : PaymentStrategy
// - getType()

#include <string>
#include <vector>
#include "User.h"
#include "MenuItem.h"
#include "Restaurant.h"

// (1) Forward declaration — we will create IPaymentStrategy later
// This avoids circular includes
class IPaymentStrategy;

class Order {
protected:                                       // (2) protected — child classes can access
    int id;
    User user;                                   // (3) User by VALUE — order owns user info
    Restaurant* restaurant;                      // (4) POINTER — restaurant exists independently
    std::vector<MenuItem>items;                  // (5) copy of items ordered
    IPaymentStrategy* strategy;                  // (6) POINTER — strategy pattern
public:
    // (7) Constructor

    Order(int id,User user,Restaurant* rest):id(id),user(user),restaurant(rest),strategy(nullptr){}

    // (8) Getters

    int getId()const {
        return id;
    }
    const User& getUser()const {
        return user;
    }
    Restaurant* getRestaurant()const {
        return restaurant;
    }
    const std::vector<MenuItem>&getItems()const {
        return items;
    }

    // (9) Set payment strategy — Strategy Pattern

    void setPaymentStrategy(IPaymentStrategy* s) {
        strategy=s;
    }

    // (10) Add item to order

    void addItem(const MenuItem& item) {
        items.push_back(item);
    }

    // (11) Execute payment

    void pay();                             // (12) defined in Order.cpp — needs full IPaymentStrategy

    // (13) Pure virtual — child classes MUST override this

    virtual std::string getType()const=0;

    // (14) Virtual destructor — MUST have when class has virtual functions

    virtual ~Order()=default;

};