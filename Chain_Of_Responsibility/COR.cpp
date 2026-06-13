//
// Created by shiva on 08-06-2026.
//
#include <iostream>
using namespace std;
// Tu ne 2500 maange
// ↓
// 2000Handler → "mera note de sakta hoon?"
//             → 2500 / 2000 = 1 note
//             → 2500 - 2000 = 500 remaining
//             → next ko bhejo 500
// ↓
// 500Handler  → "mera note de sakta hoon?"
//             → 500 / 500 = 1 note
//             → 500 - 500 = 0 remaining
//             → khatam!
// ↓
// 100Handler  → kuch nahi karna — amount 0 hai


// IHandler          → base class
// TwoThousandHandler → 2000 ke notes deta hai
// FiveHundredHandler → 500 ke notes deta hai
// OneHundredHandler  → 100 ke notes deta hai
//
// amount            → kitne paise chahiye
// notes             → kitne notes diye
// remaining         → kitna bacha

class IHandler {
protected:
    IHandler *next;

public:
    IHandler() {
        next = nullptr;
    }

    void setNext(IHandler *nextHandler) {
        next = nextHandler;
    }

    virtual void handle(int amount) = 0;

    virtual ~IHandler() {
    }
};

// IHandler* next — agle handler ka pointer. Chain mein next kaun hai.
// next = nullptr — default mein koi next nahi.
// setNext() — next handler set karo — chain banane ke liye.
// virtual void handle(int amount) = 0 — har handler ko handle() banana mandatory hai.

class TwoThousandHandler : public IHandler {
public:
    void handle(int amount) override {
        int notes = amount / 2000;
        int remaining = amount % 2000;
        if (notes > 0) {
            cout << "2000 ke notes...:" << notes << endl;
        }
        if (remaining > 0 && next != nullptr) {
            next->handle(remaining);
        }
    }
};

// notes     = 2500 / 2000 = 1
// remaining = 2500 % 2000 = 500
//
// notes > 0 → print: "2000 ke notes : 1"
// remaining > 0 → next->handle(500)


class FiveHundredHandler : public IHandler {
public:
    void handle(int amount) override {
        int notes = amount / 500;
        int remaining = amount % 500;

        if(notes > 0) {
            cout << "500 ke notes : " << notes << endl;
        }

        if(remaining > 0 && next != nullptr) {
            next->handle(remaining);
        }
    }
};
// notes     = 500 / 500 = 1
// remaining = 500 % 500 = 0
//
// notes > 0     → print: "500 ke notes : 1"
// remaining = 0 → next ko nahi bheja — khatam!

class OneHundredHandler : public IHandler {
public:
    void handle(int amount) override {
        int notes = amount / 100;
        int remaining = amount % 100;

        if(notes > 0) {
            cout << "100 ke notes : " << notes << endl;
        }

        if(remaining > 0) {
            cout << " Cannot dispense : " << remaining << " remaining" << endl;
        }
    }
};

int main() {
    TwoThousandHandler two_thousand_handler;
    FiveHundredHandler five_hundred_handler;
    OneHundredHandler one_hundred_handler;

    two_thousand_handler.setNext(&five_hundred_handler);
    five_hundred_handler.setNext(&one_hundred_handler);

    cout << "--- ATM : 2500 ---" << endl;
    two_thousand_handler.handle(2500);

    cout << "\n--- ATM : 3700 ---" << endl;
    two_thousand_handler.handle(3700);

    cout << "\n--- ATM : 600 ---" << endl;
    two_thousand_handler.handle(600);

    cout << "\n--- ATM : 150 ---" << endl;
    two_thousand_handler.handle(150);

    return 0;

}