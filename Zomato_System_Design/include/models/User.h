//
// Created by shiva on 19-05-2026.
//
#pragma once

#ifndef LOW_LEVEL_DESIGN_CPP_USER_H
#define LOW_LEVEL_DESIGN_CPP_USER_H

#endif //LOW_LEVEL_DESIGN_CPP_USER_H
// User  <<Model>>
// - userId  : int
// - name    : String
// - address : String
// - cart    : Cart

#include<string>
#include "Cart.h"                   // (1) Cart is included — User OWNS a Cart

class User {
private:
    int userId;
    std::string name;
    std::string address;
    Cart cart;                      // (2) Cart by VALUE — not a pointer!
public:
    // (3) Constructor

    User(int id,std::string name,std::string address):
            userId(id),name(name),address(address){}


    // (4) Getters

    int getId()const {
        return userId;
    }
    const std::string& getName()const {
        return name;
    }
    const std::string& getAddress()const {
        return address;
    }

    // (5) Cart access — return reference so caller can modify it

    Cart& getCart() {
        return cart;
    }

    // (6) Setters

    void setName(const std::string& n) {
        name=n;
    }
    void setAddress(const std::string& a) {
        address=a;
    }

};