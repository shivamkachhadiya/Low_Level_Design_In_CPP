//
// Created by shiva on 21-05-2026.
//
#pragma once

#ifndef LOW_LEVEL_DESIGN_CPP_NETBANKING_H
#define LOW_LEVEL_DESIGN_CPP_NETBANKING_H

#endif //LOW_LEVEL_DESIGN_CPP_NETBANKING_H
#include<iostream>
#include "IPaymentStrategy.h"

class NetBanking : public IPaymentStrategy {
public:
    void pay(int amount)const override {
        std::cout<<"Paying Rs."<<amount<<"using Net Banking."<<std::endl;
    }
};