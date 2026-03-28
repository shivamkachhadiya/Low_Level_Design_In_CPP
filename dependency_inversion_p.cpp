```cpp
/*
Dependency Inversion Principle (DIP):

DIP says:
- High-level modules should not depend on low-level modules. Both should depend on abstractions (e.g., interfaces).
- Abstractions should not depend on details. Details (concrete implementations) should depend on abstractions.

Here's a simple C++23 example with a light bulb and a switch.
*/

// Abstraction for any Switchable device
class Switchable {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual ~Switchable() = default;
};

// A concrete low-level module: LightBulb
#include <iostream>
using namespace std;

class LightBulb : public Switchable {
public:
    void turnOn() override {
        cout << "LightBulb: ON\n";
    }
    void turnOff() override {
        cout << "LightBulb: OFF\n";
    }
};

// High-level module: Switch
class Switch {
    // Depend on the abstraction, not on LightBulb directly
    Switchable& device;
public:
    Switch(Switchable& d) : device(d) {}

    void operate(bool on) {
        if (on)
            device.turnOn();
        else
            device.turnOff();
    }
};

// Client code
int main() {
    LightBulb bulb;
    Switch mySwitch(bulb); // Injecting dependency through constructor

    mySwitch.operate(true);  // Turns on the bulb
    mySwitch.operate(false); // Turns off the bulb

    return 0;
}

/*
Explanation:
- 'Switch' does not know *what* device it's operating; it works with anything that implements Switchable.
- You can add new devices (e.g., Fan, Heater) by implementing Switchable, without modifying Switch.
- High-level code (Switch) and low-level code (LightBulb) both depend on the abstraction (Switchable).

This is the Dependency Inversion Principle, simplified for beginners!
*/
```
