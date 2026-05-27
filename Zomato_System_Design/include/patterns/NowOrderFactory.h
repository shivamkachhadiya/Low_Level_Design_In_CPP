//
// Created by shiva on 21-05-2026.
//
#pragma once

#ifndef LOW_LEVEL_DESIGN_CPP_NOWORDERFACTORY_H
#define LOW_LEVEL_DESIGN_CPP_NOWORDERFACTORY_H

#endif //LOW_LEVEL_DESIGN_CPP_NOWORDERFACTORY_H
#include "IOrderFactory.h"
#include "../models/DeliveryOrder.h"
#include "../models/PickupOrder.h"

class NowOrderFactory:public IOrderFactory {
public:
    Order* createOrder(int id, User user, Restaurant *rest) override {
        std::string type;
        std::string address;
        std::cout<<"Enter Order Type (DELIVERY/PICKUP): ";
        std::cin>>type;
        if (type=="DELIVERY") {
            std::cout<<"Enter delivery address";
            std::cin>>address;
            return new DeliveryOrder(id,user,rest,address);
        }
        else if (type=="PICKUP") {
            std::cout<<"Enter pickup address:";
            std::cin>>address;
            return new PickupOrder(id,user,rest,address);
        }
        return nullptr;
    }
};


//
// Key points:
//
// (4) new DeliveryOrder(...) — creates object on heap. Returns pointer to Order but actual object is DeliveryOrder. This is upcasting — works because of inheritance ✅
// (5) nullptr — always handle invalid input! Caller must check if returned pointer is nullptr before using it
