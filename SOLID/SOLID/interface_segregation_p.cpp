#include <iostream>
using namespace std;

// Segregated interfaces
class Flyable
{
public:
    virtual void fly() = 0;
    virtual ~Flyable() = default;
};

class Swimmable
{
public:
    virtual void swim() = 0;
    virtual ~Swimmable() = default;
};

// Bird can fly
class Bird : public Flyable
{
public:
    void fly() override
    {
        cout << "Bird is flying\n";
    }
};

// Fish can swim
class Fish : public Swimmable
{
public:
    void swim() override
    {
        cout << "Fish is swimming\n";
    }
};

// Client functions
void makeFly(Flyable &f)
{
    f.fly();
}

void makeSwim(Swimmable &s)
{
    s.swim();
}

int main()
{
    Bird bird;
    Fish fish;

    makeFly(bird);  // Works
    makeSwim(fish); // Works

    // makeFly(fish); //  Compile error: Fish cannot fly
    // makeSwim(bird); // Compile error: Bird cannot swim

    return 0;
}