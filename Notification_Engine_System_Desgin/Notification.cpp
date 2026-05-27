//
// Created by shiva on 27-05-2026.
//
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class IMessage {
public:                         // Decorator ka base. Har message ke paas getContent() hona chahiye — rule.
    virtual string getContent() = 0;
    virtual ~IMessage() {}
};

class PlainMessage:public IMessage {        // IMessage ka baccha hai. Rule follow karega.
    string message;                         //actual message store hoga yahan. Jaise "Order Placed"
public:
    PlainMessage(string msg) {              //constructor
        message=msg;                        //message store
    }
    string getContent() override {          //rule poora kiya — return karo jo message store hai.
        return message;
    }
};

// //till now dry run
// PlainMessage p("Order Placed");
// p.getContent();  // "Order Placed"


class MessageDecorator:public IMessage {        //ye bhi IMessage ka baccha hai. Isliye isko bhi getContent() banana padega — concrete decorators mein banayenge.
protected:
    IMessage* message_;
public:
    MessageDecorator(IMessage* msg) {           //store the address
        message_=msg;
    }
};

class TimeStampDecorator:public MessageDecorator {
public:
    TimeStampDecorator(IMessage* msg):MessageDecorator(msg) {}

    string getContent() override {
        return message_->getContent()+" -- 10:45 PM";
    }
};


//dry run till now
// PlainMessage plain("Order Placed")
// → getContent() = "Order Placed"
//
// TimestampDecorator ts(&plain)
// → message = &plain
// → getContent() = plain.getContent() + " -- 10:45 PM"
// → getContent() = "Order Placed -- 10:45 PM"

class UrgentDecorator : public MessageDecorator {
public:
    UrgentDecorator(IMessage* msg) : MessageDecorator(msg) {}

    string getContent() override {
        return "[URGENT] " + message_->getContent();
    }
};

// //dry run till now
// PlainMessage plain("Order Placed")
// → "Order Placed"
//
// TimestampDecorator ts(&plain)
// → "Order Placed -- 10:45 PM"
//
// UrgentDecorator urgent(&ts)
// → "[URGENT] " + "Order Placed -- 10:45 PM"
// → "[URGENT] Order Placed -- 10:45 PM"


class IObserver {
public:
    virtual void update(IMessage* msg) = 0;
    virtual ~IObserver() {}
};

class EmailChannel : public IObserver {
public:
    void update(IMessage* msg)override {
        cout<<"[EMAIL] : "<<msg->getContent()<<endl;
    }
};
//
// UrgentDecorator urgent(&ts)
// → getContent() = "[URGENT] Order Placed -- 10:45 PM"
//
// email.update(&urgent)
// → msg->getContent() = "[URGENT] Order Placed -- 10:45 PM"
// → print: [EMAIL] : [URGENT] Order Placed -- 10:45 PM

class SMSChannel : public IObserver {
public:
    void update(IMessage* msg) override {
        cout << "[SMS] : " << msg->getContent() << endl;
    }
};

class PushChannel : public IObserver {
public:
    void update(IMessage* msg) override {
        cout << "[PUSH] : " << msg->getContent() << endl;
    }
};
class NotificationEngine {
    vector<IObserver*> observers;
public:
    void attach(IObserver* obs) {
        observers.push_back(obs);
    }

    void detach(IObserver* obs) {
        observers.erase(
            remove(observers.begin(), observers.end(), obs),
            observers.end()
        );
    }

    void notifyAll(IMessage* msg) {
        for (auto& obs : observers) {
            obs->update(msg);
        }
    }

    void notify(string event) {
        PlainMessage plain(event);
        TimeStampDecorator ts(&plain);
        UrgentDecorator urgent(&ts);
        notifyAll(&urgent);
    }
};
//
// "Order Placed"
// ↓
// PlainMessage plain("Order Placed")
// ↓
// TimestampDecorator ts(&plain)     → "Order Placed -- 10:45 PM"
// ↓
// UrgentDecorator urgent(&ts)       → "[URGENT] Order Placed -- 10:45 PM"
// ↓
// notifyAll(&urgent)                → saare channels ko bhejo

int main() {
    NotificationEngine engine;

    EmailChannel email;
    SMSChannel sms;
    PushChannel push;

    engine.attach(&email);
    engine.attach(&sms);
    engine.attach(&push);

    engine.notify("Order Placed");
    engine.notify("Out for Delivery");

    engine.detach(&sms);

    engine.notify("Delivered");

    return 0;
}
