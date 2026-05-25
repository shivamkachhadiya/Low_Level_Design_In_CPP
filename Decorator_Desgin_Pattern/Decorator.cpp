//
// Created by shiva on 25-05-2026.
//
#include<iostream>
#include<string>
using namespace std;

class ICoffee {
public:
    virtual string getDescription()=0;
    virtual int getPrice()=0;
    virtual ~ICoffee(){}
};

class PlainCoffee:public ICoffee {
public:
    string getDescription() override {
        return "Plain Coffee";
    }
    int getPrice()override {
        return 50;
    }
};

class CoffeDecorator:public ICoffee {
protected:
    ICoffee* coffee_;
public:
    CoffeDecorator(ICoffee* c) {
        coffee_=c;
    }
};

class MilkDecorator:public CoffeDecorator {
public:
    MilkDecorator(ICoffee* c):CoffeDecorator(c){}
    string getDescription() override {
        return coffee_->getDescription()+" +Milk";
    }
    int getPrice() override {
        return coffee_->getPrice()+20;
    }
};
class SugarDecorator : public CoffeDecorator {
public:
    SugarDecorator(ICoffee* c) : CoffeDecorator(c) {}

    string getDescription() override {
        return coffee_->getDescription() + " + Sugar";
    }
    int getPrice() override {
        return coffee_->getPrice() + 10;
    }
};

int main() {
    PlainCoffee plain;

    MilkDecorator milk(&plain);

    SugarDecorator sugar(&milk);

    cout << sugar.getDescription() << endl;
    cout << "Price: " << sugar.getPrice() << endl;

    return 0;
}