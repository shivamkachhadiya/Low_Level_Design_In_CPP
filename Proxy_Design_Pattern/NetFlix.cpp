//
// Created by shiva on 06-06-2026.
//
// User content access karna chahta hai
// ↓
// NetFlixProxyy check karta hai:
//   → User kaun hai? Free ya Premium?
//   → Content kaun sa hai? Free ya Premium?
// ↓
// Free user + Free content    → allow
// Free user + Premium content → "Subscribe to Premium!"
// Premium user + any content  → allow
// ↓
// RealNetflix ka watch() call hota hai
//
// classes jo banegi
// INetflix         → Interface — watch() rule
// RealNetflix      → actual content chalata hai
// NetFlixProxyy     → beech mein — user check karta hai
// User             → FREE ya PREMIUM

#include <complex>
#include <iostream>
#include <string>
using namespace std;

class INetFlix {
public:
    virtual void watch(string content) =0;

    virtual ~INetFlix()=default;
};

class RealNetFlix : public INetFlix {
public:
    void watch(string content) override {
        cout << "PlayING.....: " << content << endl;
    }
};

class NetFlixProxy : public INetFlix {
    RealNetFlix *realNetFlix;           //andar actual Netflix ka pointer — proxy ke peeche real cheez hai.
    string userType;

    bool isPremiumContent(string content) {
        if (content == "Money Heist")return true;
        if (content == "Stranger Things")return true;
        if (content == "Dark")return true;
        return false;
    }

public:
    NetFlixProxy(string type) {
        userType = type;
        realNetFlix = new RealNetFlix;
    }

    void watch(string content)override {
        if (isPremiumContent(content)&&userType=="FREE") {
            cout<<"Access Denied Subscribe To Premium: "<<endl;
        }else {
            realNetFlix->watch(content);
        }
    }
};
// NetflixProxy proxy("FREE");
//
// proxy.watch("Money Heist")
// → isPremiumContent("Money Heist") = true
// → userType == "FREE" = true
// → Access Denied! Subscribe to Premium!
//
// proxy.watch("Friends")
// → isPremiumContent("Friends") = false
// → realNetflix->watch("Friends")
// →  Playing : Friends

int main() {
    cout << "--- Free User ---" << endl;
    NetFlixProxy freeUser("FREE");
    freeUser.watch("Money Heist");
    freeUser.watch("Stranger Things");
    freeUser.watch("Friends");

    cout << "\n--- Premium User ---" << endl;
    NetFlixProxy premiumUser("PREMIUM");
    premiumUser.watch("Money Heist");
    premiumUser.watch("Stranger Things");
    premiumUser.watch("Friends");

    return 0;
}