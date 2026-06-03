//
// Created by shiva on 03-06-2026.
//
#include <iostream>
#include <string>
using namespace std;

class KYCService {
public:
    bool verifyKYC(string name) {
        cout << "KYC Verified for : " << name << endl;
        return true;
    }
};
class CreditService {
public:
    bool checkCredit(string name) {
        cout << "Credit Score Checked for : " << name << endl;
        return true;
    }
};
class AccountService {
public:
    void createAccount(string name) {
        cout << "Account Created for : " << name << endl;
    }
    void issueDebitCard(string name) {
        cout << "Debit Card Issued for : " << name << endl;
    }
};
class EmailService {
public:
    void sendWelcomeEmail(string name) {
        cout << "Welcome Email Sent to : " << name << endl;
    }
};

class BankFacade {
    KYCService kyc;
    CreditService credit;
    AccountService account;
    EmailService email;
public:
    void openAccount(string name) {
        cout << "--- Account Opening Started for : " << name << " ---" << endl;
        if(!kyc.verifyKYC(name)) {
            cout << "KYC Failed!" << endl;
            return;
        }
        if(!credit.checkCredit(name)) {
            cout << "Credit Check Failed!" << endl;
            return;
        }
        account.createAccount(name);
        account.issueDebitCard(name);
        email.sendWelcomeEmail(name);
        cout << "--- Account Successfully Opened for : " << name << " ---" << endl;

    }
};

int main() {
    BankFacade bank;

    bank.openAccount("Shivam");

    cout << endl;

    bank.openAccount("Rahul");

    return 0;
}