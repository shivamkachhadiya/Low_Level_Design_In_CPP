//
// Created by shiva on 14-06-2026.
//
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class IPaymentStrategy {
public:
    virtual bool pay(int amount) = 0;
    virtual string getPaymentMethod() = 0;
    virtual ~IPaymentStrategy() {}
};
class UPIPayment : public IPaymentStrategy {
    string upiId;
public:
    UPIPayment(string id) {
        upiId = id;
    }
    bool pay(int amount) override {
        cout << "UPI Payment processing..." << endl;
        cout << "UPI ID : " << upiId << endl;
        cout << " UPI Payment successful : " << amount << endl;
        return true;
    }
    string getPaymentMethod() override {
        return "UPI";
    }
};
// UPIPayment upi("shivam@okaxis");
// upi.pay(500)
// → UPI Payment processing...
// → UPI ID : shivam@okaxis
// → UPI Payment successful : 500
// → return true

class CreditCardPayment : public IPaymentStrategy {
    string cardNumber;
    string cvv;
public:
    CreditCardPayment(string card, string c) {
        cardNumber = card;
        cvv = c;
    }
    bool pay(int amount) override {
        cout << "Credit Card Payment processing..." << endl;
        cout << "Card : XXXX-XXXX-XXXX-" << cardNumber.substr(cardNumber.length()-4) << endl;
        cout << "Credit Card Payment successful : " << amount << endl;
        return true;
    }
    string getPaymentMethod() override {
        return "CreditCard";
    }
};
// CreditCardPayment card("1234567890121234", "123");
// card.pay(1000)
// → Credit Card Payment processing...
// → Card : XXXX-XXXX-XXXX-1234
// → Credit Card Payment successful : 1000

class WalletPayment : public IPaymentStrategy {
    string walletId;
    int balance;
public:
    WalletPayment(string id, int bal) {
        walletId = id;
        balance = bal;
    }
    bool pay(int amount) override {
        if(balance < amount) {
            cout << " Wallet Payment failed : Insufficient balance" << endl;
            return false;
        }
        balance -= amount;
        cout << "Wallet Payment processing..." << endl;
        cout << "Wallet ID : " << walletId << endl;
        cout << " Wallet Payment successful : " << amount << endl;
        cout << "Remaining balance : " << balance << endl;
        return true;
    }
    string getPaymentMethod() override {
        return "Wallet";
    }
};
// WalletPayment wallet("shivam_wallet", 1000);
//
// wallet.pay(500)
// → Wallet Payment processing...
// → Wallet Payment successful : 500
// → Remaining balance : 500
//
// wallet.pay(800)
// →  Wallet Payment failed : Insufficient balance

class PaymentFactory {
public:
    static IPaymentStrategy* createPayment(string type) {
        if(type == "UPI") {
            return new UPIPayment("shivam@okaxis");
        }
        else if(type == "CreditCard") {
            return new CreditCardPayment("1234567890121234", "123");
        }
        else if(type == "Wallet") {
            return new WalletPayment("shivam_wallet", 1000);
        }
        else {
            cout << "Invalid payment method!" << endl;
            return nullptr;
        }
    }
};
// IPaymentStrategy* p = PaymentFactory::createPayment("UPI");
// p->pay(500)
// → UPI Payment processing...
// → UPI Payment successful : 500
//
// IPaymentStrategy* p2 = PaymentFactory::createPayment("Wallet");
// p2->pay(200)
// → Wallet Payment processing...
// → Wallet Payment successful : 200

class PaymentLogger {
    static PaymentLogger* instance;

    PaymentLogger() {}

public:
    static PaymentLogger* getInstance() {
        if(instance == nullptr) {
            instance = new PaymentLogger();
        }
        return instance;
    }

    void log(string message) {
        cout << "[LOG] " << message << endl;
    }
};

PaymentLogger* PaymentLogger::instance = nullptr;
// PaymentLogger* logger = PaymentLogger::getInstance();
// PaymentLogger* logger2 = PaymentLogger::getInstance();
//
// logger == logger2 → true ← same object!
//
// logger->log("Payment initiated : 500 via UPI")
// → [LOG] Payment initiated : 500 via UPI

class IPaymentObserver {
public:
    virtual void update(string status, int amount) = 0;
    virtual ~IPaymentObserver() {}
};

class EmailNotification : public IPaymentObserver {
public:
    void update(string status, int amount) override {
        cout << "[EMAIL] Payment " << status << " : " << amount << endl;
    }
};

class SMSNotification : public IPaymentObserver {
public:
    void update(string status, int amount) override {
        cout << "[SMS] Payment " << status << " : " << amount << endl;
    }
};
// EmailNotification email;
// email.update("successful", 500)
// → [EMAIL] Payment successful : 500
//
// SMSNotification sms;
// sms.update("failed", 800)
// → [SMS] Payment failed : 800

class PaymentProcessor {
    vector<IPaymentObserver*> observers;
    PaymentLogger* logger;

public:
    PaymentProcessor() {
        logger = PaymentLogger::getInstance();
    }

    void addObserver(IPaymentObserver* obs) {
        observers.push_back(obs);
    }

    void notifyAll(string status, int amount) {
        for(auto& obs : observers) {
            obs->update(status, amount);
        }
    }

    void processPayment(string type, int amount) {
        logger->log("Payment initiated : " + to_string(amount) + " via " + type);

        IPaymentStrategy* strategy = PaymentFactory::createPayment(type);

        if(strategy == nullptr) return;

        notifyAll("processing", amount);

        bool success = strategy->pay(amount);

        if(success) {
            notifyAll("successful", amount);
            logger->log("Payment completed : " + to_string(amount) + " via " + type);
        } else {
            notifyAll("failed", amount);
            logger->log("Payment failed : " + to_string(amount) + " via " + type);
        }

        delete strategy;
    }
};

int main() {
    PaymentProcessor processor;

    EmailNotification email;
    SMSNotification sms;

    processor.addObserver(&email);
    processor.addObserver(&sms);

    cout << "--- UPI Payment ---" << endl;
    processor.processPayment("UPI", 500);

    cout << "\n--- Credit Card Payment ---" << endl;
    processor.processPayment("CreditCard", 1000);

    cout << "\n--- Wallet Payment ---" << endl;
    processor.processPayment("Wallet", 200);

    cout << "\n--- Wallet Insufficient ---" << endl;
    processor.processPayment("Wallet", 5000);

    return 0;
}