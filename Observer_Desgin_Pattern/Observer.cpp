//
// Created by shiva on 24-05-2026.
//
#include<iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class IObserver {
public:
    virtual void update(string event)=0;
};

class EmailObserver:public IObserver {
public:
    void update(string event) override{
        cout<<"[EMAIL]: "<<event<<endl;
    }
};

class SMSobserver:public IObserver {
public:
    void update(string event)override {
        cout<<"[SMS]: "<<event<<endl;
    }
};

class Order {
    vector<IObserver*>observers_;
    string status;
public:
    void attach(IObserver* obs) {
        observers_.push_back(obs);
    }

    void detach(IObserver* obs) {
        observers_.erase(
            remove(observers_.begin(), observers_.end(), obs),
            observers_.end()
        );
    }

    void notifyAll() {
        for (auto& obs : observers_) {
            obs->update(status);
        }
    }

    void setStatus(string s) {
        status = s;
        notifyAll();
    }
};

int main() {
    Order order;
    EmailObserver email;
    SMSobserver sms;

    order.attach(&email);
    order.attach(&sms);

    order.setStatus("Order Placed");
    order.setStatus("Out for Delivery");

    order.detach(&sms);

    order.setStatus("Delivered");

    return 0;
}


















