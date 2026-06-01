//
// Created by shiva on 30-05-2026.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class TV {
    int volume=10;
    bool isOn=false;

public:
    void volumeUp() {
        volume++;
        cout<<"Volume up : "<<volume<<endl;
    }

    void volumeDown() {
        volume--;
        cout<<"Volume down : "<<volume<<endl;
    }

    void power() {
        isOn=!isOn;
        if (isOn) {
            cout<<"TV ON...."<<endl;
        }else {
            cout<<"TV OFF...."<<endl;
        }
    }
};

// TV tv;
// tv.volumeUp()   → Volume Up : 11
// tv.volumeUp()   → Volume Up : 12
// tv.volumeDown() → Volume Down : 11
// tv.power()      → TV On
// tv.power()      → TV Off

class ICommand {
public:
    virtual void execute()=0;
    virtual void undo()=0;
    virtual ~ICommand(){}
};

class volumeUpCommand:public ICommand {
    TV* tv;
public:
    volumeUpCommand(TV* t) {
        tv=t;
    }
    void execute() override {
        tv->volumeUp();
    }
    void undo() override {
        tv->volumeDown();
    }
};

class volumeDownCommand:public ICommand {
    TV* tv;
public:
    volumeDownCommand(TV* t) {
        tv=t;
    }
    void execute() override {
        tv->volumeDown();
    }
    void undo() override {
        tv->volumeUp();
    }

};

class PowerCommand:public ICommand {
    TV* tv;
public:
    PowerCommand(TV* t) {
        tv=t;
    }
    void execute() override {
        tv->power();
    }
    void undo() override {
        tv->power();
    }
};
//
// DRY RUN
// VolumeDownCommand cmd(&tv);
// cmd.execute() → Volume Down : 9
// cmd.undo()    → Volume Up : 10
//
// PowerCommand pcmd(&tv);
// pcmd.execute() → TV On
// pcmd.undo()    → TV Off

class Remote {
    vector<ICommand*>history;
public:
    void pressButton(ICommand* cmd) {
        cmd->execute();
        history.push_back(cmd);
    }
    void pressUndo() {
        if (history.empty()) {
            cout<<"Nothing to undo"<<endl;
            return;
        }
        ICommand* last=history.back();
        last->undo();
        history.pop_back();
    }
};

int main() {
    TV tv;
    Remote remote;

    volumeUpCommand volUp(&tv);
    volumeDownCommand volDown(&tv);
    PowerCommand power(&tv);

    remote.pressButton(&power);


}

// TV tv;
// Remote remote;
//
// volumeUpCommand volUp(&tv);
// volumeDownCommand volDown(&tv);
// PowerCommand power(&tv);
//
// cout << "--- Buttons Press ---" << endl;
// remote.pressButton(&power);
// remote.pressButton(&volUp);
// remote.pressButton(&volUp);
// remote.pressButton(&volDown);
//
// cout << "--- Undo Start ---" << endl;
// remote.pressUndo();
// remote.pressUndo();
// remote.pressUndo();
// remote.pressUndo();
// remote.pressUndo();
