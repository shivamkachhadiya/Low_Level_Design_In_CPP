//
// Created by shiva on 21-05-2026.
//
#pragma once

#ifndef LOW_LEVEL_DESIGN_CPP_IPAYMENTSTRATEGY_H
#define LOW_LEVEL_DESIGN_CPP_IPAYMENTSTRATEGY_H

#endif //LOW_LEVEL_DESIGN_CPP_IPAYMENTSTRATEGY_H
class IPaymentStrategy {
public:
    // (1) Pure virtual function — every payment method MUST implement this

    virtual void pay(int amount)const=0;

    // (2) Virtual destructor — must have in every interface/abstract class

    virtual ~IPaymentStrategy()=default;
};