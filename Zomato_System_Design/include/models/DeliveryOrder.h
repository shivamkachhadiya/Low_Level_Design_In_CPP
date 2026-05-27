//
// Created by shiva on 21-05-2026.
//

#ifndef LOW_LEVEL_DESIGN_CPP_DELIVERYORDER_H
#define LOW_LEVEL_DESIGN_CPP_DELIVERYORDER_H
#include "Order.h"
#endif //LOW_LEVEL_DESIGN_CPP_DELIVERYORDER_H
#pragma once
#include <string>
#pragma once
class DeliveryOrder:public Order {
private:
    std::string deliveryAddress;
public:
    DeliveryOrder(int id,User user,Restaurant* rest,std::string address):
            Order(id,user,rest),deliveryAddress(address){}

    const std::string& getDeliveryAddress()const {return deliveryAddress;}

    std::string getType() const override {
        return "DELIVERY";
    }

};