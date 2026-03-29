//
// Created by i on 03-04-2026.
//
#include<iostream>
#include<memory>
using namespace std;
class PaymentStrategy {
public:
    virtual void pay(int amount)=0;
    virtual ~PaymentStrategy()=default;
};

class CredtCardPayment:public PaymentStrategy {
public:
    void pay(int amount)override {
        cout<<"Credit Card Payment: "<<amount<<endl;
    }
};

class UpiPaymenet:public PaymentStrategy {
public:
    void pay(int amount)override {
        cout<<"UPI Payment: "<<amount<<endl;
    }
};

class PaymentProcessor {
private:
    unique_ptr<PaymentStrategy>strategy_;
public:
    PaymentProcessor(unique_ptr<PaymentStrategy>s)
        :strategy_(move(s)){}
    void process(int amount) {
        strategy_->pay(amount);
    }
};

int main() {
    auto payment=PaymentProcessor(make_unique<CredtCardPayment>());
    payment.process(1000);
}