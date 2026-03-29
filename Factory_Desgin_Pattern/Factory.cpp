//
// Created by i on 13-04-2026.
//
#include<iostream>
#include<vector>
#include<memory>
using namespace std;

class vehicle {
public:
    virtual void start()=0;
    virtual ~vehicle()=default;
};

class Car:public vehicle {
public:
    void start()override {
        cout<<"CAR STARTED....."<<endl;
    }
};

class Bike:public vehicle {
public:
    void start()override {
        cout<<"BIKE STARTED...."<<endl;
    }
};

class Truck:public vehicle {
public:
    void start()override {
        cout<<"TRUCK STARTED...."<<endl;
    }
};

class VehicalFactory {
public:
        static unique_ptr<vehicle>create_vehicle(string type) {
            if (type=="car") {
                return make_unique<Car>();
            }
            else if (type=="bike") {
                return make_unique<Bike>();
            }else if (type=="truck") {
                return make_unique<Truck>();
            }
            return nullptr;
        }
};
int main() {
    auto v1=VehicalFactory::create_vehicle("car");
    v1->start();
    auto v2=VehicalFactory::create_vehicle("bike");
    v2->start();
}