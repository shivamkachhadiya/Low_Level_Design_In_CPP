//
// Created by shiva on 21-05-2026.
//
#pragma once

#ifndef LOW_LEVEL_DESIGN_CPP_UPI_H
#define LOW_LEVEL_DESIGN_CPP_UPI_H

#endif //LOW_LEVEL_DESIGN_CPP_UPI_H
#include <iostream>
#include "IPaymentStrategy.h"

class UPI : public IPaymentStrategy {
public:
    void pay(int amount) const override {
        std::cout << "Paying Rs." << amount
                  << " using UPI."
                  << std::endl;
    }
};

//
// Strategy Pattern 100% complete!
// IPaymentStrategy   ← Interface
//        ↑
//   ┌────┼────┐
//   │    │    │
// Credit Net  UPI
// Card  Banking