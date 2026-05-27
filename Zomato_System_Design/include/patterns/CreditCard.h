//
// Created by shiva on 21-05-2026.
//
#pragma once

#ifndef LOW_LEVEL_DESIGN_CPP_CREDITCARD_H
#define LOW_LEVEL_DESIGN_CPP_CREDITCARD_H

#endif //LOW_LEVEL_DESIGN_CPP_CREDITCARD_H
#include <iostream>
#include "IPaymentStrategy.h"

class CreditCard:public IPaymentStrategy {              // (2) implements the interface
public:

    void pay(int amount)const override {
        std::cout<<"Paying Rs."<<amount<<"Using Credit Card."<<std::endl;
    }
};
//
// Abhi dekho teen files ka relationship:
// IPaymentStrategy        <- Interface (contract)
//        ↑
//    CreditCard           <- Implements contract
//    NetBanking           <- Implements contract
//    UPI                  <- Implements contractplements contract