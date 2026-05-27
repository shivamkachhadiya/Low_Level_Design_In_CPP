//
// Created by shiva on 21-05-2026.
//
#pragma once

#ifndef LOW_LEVEL_DESIGN_CPP_IORDERFACTORY_H
#define LOW_LEVEL_DESIGN_CPP_IORDERFACTORY_H

#endif //LOW_LEVEL_DESIGN_CPP_IORDERFACTORY_H

#include "../models/Order.h"

class IOrderFactory {
public:
    virtual Order* createOrder(int id,User user,Restaurant* rest)=0;
    virtual ~IOrderFactory()=default;
};