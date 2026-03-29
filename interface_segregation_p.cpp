#include <iostream>
using namespace std;

// =======================
//  BAD DESIGN (ISP VIOLATION)
// =======================

class Worker {
public:
    virtual void work() = 0;
    virtual void eat() = 0;   // not applicable to all
    virtual void sleep() = 0; //  not applicable to all
    virtual ~Worker() = default;
};

class Human : public Worker {
public:
    void work() override {
        cout << "Human working\n";
    }

    void eat() override {
        cout << "Human eating\n";
    }

    void sleep() override {
        cout << "Human sleeping\n";
    }
};

class Robot : public Worker {
public:
    void work() override {
        cout << "Robot working\n";
    }

    void eat() override {
        // ❌ forced implementation
        cout << "Robot cannot eat!\n";
    }

    void sleep() override {
        // ❌ forced implementation
        cout << "Robot does not sleep!\n";
    }
};

// =======================
// ✅ GOOD DESIGN (ISP APPLIED)
// =======================

// Small, focused interfaces
class Workable {
public:
    virtual void work() = 0;
    virtual ~Workable() = default;
};

class Eatable {
public:
    virtual void eat() = 0;
    virtual ~Eatable() = default;
};

class Sleepable {
public:
    virtual void sleep() = 0;
    virtual ~Sleepable() = default;
};

// Human supports all behaviors
class BetterHuman : public Workable, public Eatable, public Sleepable {
public:
    void work() override {
        cout << "BetterHuman working\n";
    }

    void eat() override {
        cout << "BetterHuman eating\n";
    }

    void sleep() override {
        cout << "BetterHuman sleeping\n";
    }
};

// Robot supports only what it needs
class BetterRobot : public Workable {
public:
    void work() override {
        cout << "BetterRobot working\n";
    }
};

// =======================
// Usage functions
// =======================

void manageWork(Workable& w) {
    w.work();
}

void lunchBreak(Eatable& e) {
    e.eat();
}

void nightRest(Sleepable& s) {
    s.sleep();
}

// =======================
// MAIN
// =======================

int main() {
    cout << "===== BAD DESIGN =====\n";
    Human h;
    Robot r;

    h.work();
    h.eat();
    h.sleep();

    r.work();
    r.eat();   //  meaningless
    r.sleep(); //  meaningless

    cout << "\n===== GOOD DESIGN =====\n";

    BetterHuman bh;
    BetterRobot br;

    manageWork(bh); // 
    manageWork(br); // 

    lunchBreak(bh); // 
    // lunchBreak(br);  compile-time error (GOOD)

    nightRest(bh); // 
    // nightRest(br);  compile-time error (GOOD)

    return 0;
}