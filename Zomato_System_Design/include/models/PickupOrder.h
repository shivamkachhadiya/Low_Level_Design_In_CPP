//
// Created by shiva on 21-05-2026.
//
#pragma once

#ifndef LOW_LEVEL_DESIGN_CPP_PICKUPORDER_H
#define LOW_LEVEL_DESIGN_CPP_PICKUPORDER_H

#endif //LOW_LEVEL_DESIGN_CPP_PICKUPORDER_H
#include<string>
#include "Order.h"

class PickupOrder :public Order {
private:
    std::string resAddress;
public:
    PickupOrder(int id,User user,Restaurant* rest,std::string address):
        Order(id,user,rest),resAddress(address){}

    const std::string& getResAddress()const {return resAddress;}
    std::string getType() const override {
        return "PICKUP";
    }
};