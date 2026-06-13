//
// ATM Machine - State Design Pattern
// Created by shiva on 08-06-2026.
//
// States:
//   1. NoCardState       → Card insert kar sakte ho
//   2. CardInsertedState → PIN enter kar sakte ho
//   3. PINVerifiedState  → Cash withdraw / balance check
//   4. CashDispensingState → Cash dispense hoga
//

#include <iostream>
#include <string>
using namespace std;

//  ATMState — Abstract Base Class (Interface)
//  Har state isko inherit karegi
//  Ye ek CONTRACT hai — 4 operations MUST implement

class ATM; // Forward Declaration — ATM class aage define hogi

class ATMState {
public:
    virtual void insertCard(ATM *atm) = 0; // No Card State mein kaam karega
    virtual void enterPIN(ATM *atm, int pin) = 0; // Card Inserted State mein
    virtual void requestCash(ATM *atm, int amt) = 0; // PIN Verified State mein
    virtual void dispenseCash(ATM *atm) = 0; // Cash Dispensing State mein

    virtual ~ATMState() {
    } // Memory leak rokne ke liye
};

// ============================================
//  ATM — Context Class
//  Ye actual ATM machine hai
//  Iske paas current state ka reference hoga
//  Sab operations current state ko delegate karta hai
// ============================================

class ATM {
private:
    ATMState *currentState; // Jo bhi state abhi active hai
    int cashAvailable; // ATM mein kitna cash hai

public:
    // Constructor — ATM start hoti hai NoCardState mein
    // (NoCardState aage define hogi, abhi nullptr)
    ATM(int cash) {
        cashAvailable = cash;
        currentState = nullptr; // baad mein set karenge
    }

    // ── State Change karna ──────────────────
    void setState(ATMState *newState) {
        currentState = newState;
    }

    // ── Cash Getters / Setters ───────────────
    int getCash() {
        return cashAvailable;
    }

    void setCash(int cash) {
        cashAvailable = cash;
    }

    // ── 4 Operations — Delegate to currentState ─
    void insertCard() {
        currentState->insertCard(this); // state decide karegi kya hoga
    }

    void enterPIN(int pin) {
        currentState->enterPIN(this, pin);
    }

    void requestCash(int amt) {
        currentState->requestCash(this, amt);
    }

    void dispenseCash() {
        currentState->dispenseCash(this);
    }
};
// ============================================
//  NoCardState
//  ATM ka default/starting state
//  Sirf insertCard() allowed hai
// ============================================

class NoCardState : public ATMState {
public:
    void insertCard(ATM* atm) override {
        cout << " Card inserted successfully!\n";
        cout << "   ATM → switching to CardInsertedState...\n";
        atm->setState(new CardInsertedState()); // state change!
    }

    void enterPIN(ATM* atm, int pin) override {
        cout << " [NoCardState]  Please insert card first!\n";
    }

    void requestCash(ATM* atm, int amt) override {
        cout << " [NoCardState]  Insert card before withdrawing!\n";
    }

    void dispenseCash(ATM* atm) override {
        cout << " [NoCardState]  No transaction in progress!\n";
    }
};
// ============================================
//  CardInsertedState
//  Card andar hai — PIN ka wait hai
//  enterPIN() allowed hai
// ============================================

class CardInsertedState : public ATMState {
private:
    int correctPIN = 1234; // hardcoded for simplicity

public:
    void insertCard(ATM* atm) override {
        cout << " [CardInserted]  Card already inserted!\n";
    }

    void enterPIN(ATM* atm, int pin) override {
        if (pin == correctPIN) {
            cout << " PIN correct!\n";
            cout << "   ATM → switching to PINVerifiedState...\n";
            atm->setState(new PINVerifiedState()); // state change!
        } else {
            cout << " Wrong PIN! Try again.\n";
            // state nahi badla — CardInsertedState mein hi rahega
        }
    }

    void requestCash(ATM* atm, int amt) override {
        cout << " [CardInserted]  Please enter PIN first!\n";
    }

    void dispenseCash(ATM* atm) override {
        cout << " [CardInserted]  PIN verify karo pehle!\n";
    }
};

// ============================================
//  PINVerifiedState
//  PIN sahi tha — ab cash request kar sako
//  requestCash() allowed hai
// ============================================

class PINVerifiedState : public ATMState {
public:
    void insertCard(ATM* atm) override {
        cout << " [PINVerified]  Card already inside!\n";
    }

    void enterPIN(ATM* atm, int pin) override {
        cout << " [PINVerified]  PIN already verified!\n";
    }

    void requestCash(ATM* atm, int amt) override {
        if (amt <= 0) {
            cout << " Invalid amount!\n";
            return;
        }
        if (amt > atm->getCash()) {
            cout << " Insufficient cash in ATM!\n";
            return;
        }
        cout << " Cash request of Rs." << amt << " approved!\n";
        cout << "   ATM → switching to CashDispensingState...\n";
        atm->setCash(atm->getCash() - amt); // cash kam karo
        atm->setState(new CashDispensingState()); // state change!
    }

    void dispenseCash(ATM* atm) override {
        cout << " [PINVerified]  Request cash first!\n";
    }
};

// ============================================
//  CashDispensingState
//  Cash nikal raha hai — sirf dispenseCash()
//  Kaam hone ke baad wapas NoCardState
// ============================================

class CashDispensingState : public ATMState {
public:
    void insertCard(ATM* atm) override {
        cout << " [Dispensing]  Please wait, cash is dispensing!\n";
    }

    void enterPIN(ATM* atm, int pin) override {
        cout << " [Dispensing]  Transaction in progress!\n";
    }

    void requestCash(ATM* atm, int amt) override {
        cout << " [Dispensing]  Already dispensing cash!\n";
    }

    void dispenseCash(ATM* atm) override {
        cout << " Cash dispensed! Please collect your money 💵\n";
        cout << "   ATM → switching back to NoCardState...\n";
        cout << "   Remaining cash in ATM: Rs."
             << atm->getCash() << "\n";
        atm->setState(new NoCardState()); // cycle complete! wapas start
    }
};

// ============================================
//  main() — ATM ka Full Flow Test
//  Happy Path + Error Cases dono test karenge
// ============================================

int main() {

    // ── ATM banao — 5000 Rs cash ke saath ──
    ATM atm(5000);
    atm.setState(new NoCardState()); // starting state

    cout << "========================================\n";
    cout << "       🏧 ATM Machine Started           \n";
    cout << "       Cash Available: Rs.5000          \n";
    cout << "========================================\n\n";

    // ── TEST 1: Bina card ke PIN daalna ──────
    cout << "--- TEST 1: PIN without card ---\n";
    atm.enterPIN(1234);              //  should fail
    cout << "\n";

    // ── TEST 2: Card insert karo ─────────────
    cout << "--- TEST 2: Insert Card ---\n";
    atm.insertCard();                //  NoCard → CardInserted
    cout << "\n";

    // ── TEST 3: Dobara card daalna ───────────
    cout << "--- TEST 3: Insert Card Again ---\n";
    atm.insertCard();                //  should fail
    cout << "\n";

    // ── TEST 4: Wrong PIN ────────────────────
    cout << "--- TEST 4: Wrong PIN ---\n";
    atm.enterPIN(9999);              //  wrong pin
    cout << "\n";

    // ── TEST 5: Correct PIN ──────────────────
    cout << "--- TEST 5: Correct PIN ---\n";
    atm.enterPIN(1234);              //  CardInserted → PINVerified
    cout << "\n";

    // ── TEST 6: Bahut zyada cash maango ──────
    cout << "--- TEST 6: Request too much cash ---\n";
    atm.requestCash(99999);          //  insufficient
    cout << "\n";

    // ── TEST 7: Sahi amount request karo ─────
    cout << "--- TEST 7: Request Rs.500 ---\n";
    atm.requestCash(500);            //  PINVerified → Dispensing
    cout << "\n";

    // ── TEST 8: Cash dispense karo ───────────
    cout << "--- TEST 8: Dispense Cash ---\n";
    atm.dispenseCash();              // Dispensing → NoCard
    cout << "\n";

    // ── TEST 9: Full cycle dobara ─────────────
    cout << "--- TEST 9: Full Cycle Again ---\n";
    atm.insertCard();                // NoCard → CardInserted
    atm.enterPIN(1234);              // CardInserted → PINVerified
    atm.requestCash(1000);           // PINVerified → Dispensing
    atm.dispenseCash();              // Dispensing → NoCard
    cout << "\n";

    cout << "========================================\n";
    cout << "       ATM Session Complete           \n";
    cout << "========================================\n";

    return 0;
}