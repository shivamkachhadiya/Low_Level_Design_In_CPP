//
// Created by shiva on 06-06-2026.
//
#include <iostream>
#include <string>
using namespace std;

class Burger {
public:
    string bun;
    string patty;
    bool cheese;
    string sauce;
    bool lettuce;
    string size;

    void display() {
        cout << "--- Burger Order ---" << endl;
        cout << "Bun     : " << bun << endl;
        cout << "Patty   : " << patty << endl;
        cout << "Cheese  : " << (cheese ? "Yes" : "No") << endl;
        cout << "Sauce   : " << sauce << endl;
        cout << "Lettuce : " << (lettuce ? "Yes" : "No") << endl;
        cout << "Size    : " << size << endl;
    }
};

class BurgerBuilder {
    Burger burger;
public:
    BurgerBuilder& setBun(string bun) {
        burger.bun = bun;
        return *this;
    }
    BurgerBuilder& setPatty(string patty) {
        burger.patty = patty;
        return *this;
    }
    BurgerBuilder& setCheese(bool cheese) {
        burger.cheese = cheese;
        return *this;
    }
    BurgerBuilder& setSauce(string sauce) {
        burger.sauce = sauce;
        return *this;
    }
    BurgerBuilder& setLettuce(bool lettuce) {
        burger.lettuce = lettuce;
        return *this;
    }
    BurgerBuilder& setSize(string size) {
        burger.size = size;
        return *this;
    }
    Burger build() {
        return burger;
    }
};

// Burger b = BurgerBuilder()
//     .setBun("sesame")
//     .setPatty("chicken")
//     .setCheese(true)
//     .setSauce("mayo")
//     .setLettuce(true)
//     .setSize("large")
//     .build();
//
// b.display();
// --- Burger Order ---
// Bun     : sesame
// Patty   : chicken
// Cheese  : Yes
// Sauce   : mayo
// Lettuce : Yes
// Size    : large

int main() {
    Burger b1 = BurgerBuilder()
        .setBun("sesame")
        .setPatty("chicken")
        .setCheese(true)
        .setSauce("mayo")
        .setLettuce(true)
        .setSize("large")
        .build();
    b1.display();

    cout << endl;

    Burger b2 = BurgerBuilder()
        .setBun("whole wheat")
        .setPatty("paneer")
        .setCheese(false)
        .setSauce("ketchup")
        .setLettuce(false)
        .setSize("medium")
        .build();
    b2.display();

    return 0;
}