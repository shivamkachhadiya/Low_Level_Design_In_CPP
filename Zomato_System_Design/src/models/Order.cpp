//
// Created by shiva on 21-05-2026.
//
// src/models/Order.cpp
#include "../include/models/Order.h"

#include <iostream>

#include "../include/patterns/IPaymentStrategy.h"

void Order::pay() {
    if (strategy == nullptr) {
        std::cout << "No payment strategy set!" << std::endl;
        return;
    }
    // (1) Calculate total from items
    int total = 0;
    for (const auto& item : items) {
        total += item.getPrice();
    }
    // (2) Delegate to strategy
    strategy->pay(total);
}