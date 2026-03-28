/*
Interface Segregation Principle (ISP) - Definition:
The Interface Segregation Principle states that "no client should be forced to depend on methods it does not use."
In simpler words, rather than having a large, bloated interface, it's better to have several small, specific interfaces so that clients only need to know about the methods that are of interest to them.

---
// Example: An appliance system where different devices support different operations.

#include <iostream>
using namespace std;

// Segregated interfaces
class Switchable {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual ~Switchable() = default;
};

class Dimmable {
public:
    virtual void setBrightness(int percent) = 0;
    virtual ~Dimmable() = default;
};

// Light supports switching and dimming
class Light : public Switchable, public Dimmable {
public:
    void turnOn() override { cout << "Light: ON\n"; }
    void turnOff() override { cout << "Light: OFF\n"; }
    void setBrightness(int percent) override {
        cout << "Light brightness set to " << percent << "%\n";
    }
};

// Fan supports only switching
class Fan : public Switchable {
public:
    void turnOn() override { cout << "Fan: ON\n"; }
    void turnOff() override { cout << "Fan: OFF\n"; }
};

// Client uses only the required interface
void operateSwitch(Switchable& device) {
    device.turnOn();
    device.turnOff();
}

void dimDevice(Dimmable& device) {
    device.setBrightness(70);
}

/*
 * Main demonstrates separation of interface
 */
int main() {
    Light light;
    Fan fan;

    operateSwitch(light); // Uses Switchable interface
    operateSwitch(fan);   // Uses Switchable interface

    dimDevice(light);     // Only Light supports Dimmable
    // dimDevice(fan);    // Compile error: Fan does not support Dimmable

    return 0;
}

/*
Detail for interviews:
- Light and Fan may have some common operations (turnOn, turnOff), so both implement Switchable.
- Only Light implements Dimmable, because only some devices can be dimmed.
- By splitting interfaces, we prevent Fan from being forced to implement setBrightness (which would not make sense).
- This separation keeps interfaces clean and ensures that implementing classes do not need to write empty or meaningless code for functions that don't make sense for them.
- Clients use only the interfaces they need.
This is the Interface Segregation Principle in action!
*/