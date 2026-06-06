//
// Created by shiva on 04-06-2026.
//
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Song {
public:
    string title;
    string artist;
    int duration;

    Song(string t, string a, int d) {
        title = t;
        artist = a;
        duration = d;
    }

    void display() {
        cout << title << " - " << artist << " [" << duration << " sec]" << endl;
    }
};

class IUser {
public:
    virtual string getUsername() = 0;

    virtual string getUserType() = 0;

    virtual bool canDownload() = 0;

    virtual bool hasAds() = 0;

    virtual ~IUser() {
    }
};

class FreeUser : public IUser {
    string username;

public:
    FreeUser(string name) {
        username = name;
    }

    string getUsername() override {
        return username;
    }

    string getUserType() override {
        return "FREE";
    }

    bool canDownload() override {
        return false;
    }

    bool hasAds() override {
        return true;
    }
};

// FreeUser u("Shivam");
// u.getUsername()  → "Shivam"
// u.getUserType()  → "FREE"
// u.canDownload()  → false
// u.hasAds()       → true

class PremiumUser : public IUser {
    string userName;

public:
    PremiumUser(string name) {
        userName = name;
    }

    string getUsername() override {
        return userName;
    }

    string getUserType() override {
        return "PREMIUM";
    }

    bool canDownload() override {
        return true;
    }

    bool hasAds() override {
        return false;
    }
};

// PremiumUser p("Rahul")
// p.getUserType()  → "PREMIUM"
// p.canDownload()  → true
// p.hasAds()       → false

class UserFactory {
public:
    static IUser *createUser(string type, string name) {
        // static IUser* createUser(string type, string name) — static matlab object banaye bina call kar sakte hain. IUser* return karta hai — FreeUser ya PremiumUser dono pakad sakta hai.
        if (type == "free") {
            return new FreeUser(name);
        } else if (type == "premium") {
            return new PremiumUser(name);
        } else {
            cout << "Invalid User Type....!!!" << endl;
            return NULL;
        }
    }
};

// IUser* u1 = UserFactory::createUser("free", "Shivam");
// u1->getUsername()  → "Shivam"
// u1->getUserType()  → "FREE"
// u1->hasAds()       → true
//
// IUser* u2 = UserFactory::createUser("premium", "Rahul");
// u2->getUsername()  → "Rahul"
// u2->getUserType()  → "PREMIUM"
// u2->canDownload()  → true

class PlayList {
    string name;
    vector<Song *> songs;

public:
    PlayList(string n) {
        name = n;
    }

    void addSong(Song *song) {
        songs.push_back(song);
        cout << "Added : " << song->title << " -> " << name << endl;
    }

    void removeSong(Song *song) {
        songs.erase(
            remove(songs.begin(), songs.end(), song),
            songs.end()
        );
        cout << "Removed : " << song->title << " from " << name << endl;
    }

    void display() {
        cout << " PLAY LIST : " << name << endl;
        for (auto *s: songs) {
            s->display();
        }
    }
};

// string name — playlist ka naam. Jaise "Chill Vibes"
// vector<Song*> songs — songs ki list.
// addSong() — song add karo list mein.
// removeSong() — song hatao — bilkul Observer ke detach jaisa.
// display() — poori playlist print karo.

class IObserver {
public:
    virtual void update(Song *song) = 0;

    virtual ~IObserver() {
    }
};

// MusicPlayer ko observe kar rahe hain.
// Jab bhi MusicPlayer mein song change hoga — saare observers ko notify hoga.
// Song change hua — "Kesariya" se "Tum Hi Ho"
//               ↓
// History mein add ho gaya        ← HistoryObserver
// Screen pe "Now Playing" badla   ← UIObserver
// New recommendations aaye        ← RecommendationObserver
// Tu manually kuch nahi kiya — song change hua, sab automatically update ho gaya.
//===========================================================
//                                  MusicPlayer = Subject
// MusicPlayer
//   → currentSong badla
//   → notifyAll() chala
//   → saare observers ko bataya
// Observers = Jo sun rahe hain
// HistoryObserver       → history mein add karo
// UIObserver            → screen update karo
// RecommendationObserver → naye songs suggest karo

class MusicPlayer {
    static MusicPlayer *instance;
    vector<IObserver *> observers;
    Song *currentSong;

    MusicPlayer() {
        currentSong = nullptr;
    }

public:
    static MusicPlayer *getInstance() {
        if (instance == nullptr) {
            instance = new MusicPlayer();
        }
        return instance;
    }

    void attach(IObserver *obs) {
        observers.push_back(obs);
    }

    void detach(IObserver *obs) {
        observers.erase(
            remove(observers.begin(), observers.end(), obs),
            observers.end()
        );
    }

    void notifyAll() {
        for (auto &obs: observers) {
            obs->update(currentSong);
        }
    }

    void play(Song *song) {
        currentSong = song;
        cout << "Now Playing : ";
        currentSong->display();
        notifyAll();
    }

    Song *getCurrentSong() {
        return currentSong;
    }
};

MusicPlayer *MusicPlayer::instance = nullptr;
// MusicPlayer* p1 = MusicPlayer::getInstance();
// MusicPlayer* p2 = MusicPlayer::getInstance();
//
// p1 == p2 → true  ← dono same object hain!
//
// p1->play(&song1)
// → Now Playing : Kesariya - Arijit Singh [240 sec]
// → notifyAll() chala

class HistoryObserver : public IObserver {
    vector<Song *> history;

public:
    void update(Song *song) override {
        history.push_back(song);
        cout << "[HISTORY] : " << song->title << " added to history..." << endl;
    }

    void showHistory() {
        cout << "---------- P L A Y - H I S T O R Y ------------" << endl;
        for (auto *s: history) {
            s->display();
        }
    }
};

class UIObserver : public IObserver {
public:
    void update(Song *song) override {
        cout << " [UI] : Now Playing - " << song->title << " By " << song->artist << endl;
    }
};

// song1 = Kesariya play hua
// → historyObs.update(&song1)
// → [HISTORY] : Kesariya added to history
// → uiObs.update(&song1)
// → [UI] : Now Playing - Kesariya by Arijit Singh
//
// song2 = Tum Hi Ho play hua
// → [HISTORY] : Tum Hi Ho added to history
// → [UI] : Now Playing - Tum Hi Ho by Arijit Singh
//
// historyObs.showHistory()
// → --- Play History ---
// → Kesariya - Arijit Singh [240 sec]
// → Tum Hi Ho - Arijit Singh [260 sec]

class ICommand {
public:
    virtual void
    execute() =0;

    virtual void undo() =0;

    virtual ~ICommand() {
    }
};

// execute() — command chalao — play, pause, next.
// undo() — command wapas karo — previous song pe jao.

class PlayCommand : public ICommand {
    MusicPlayer *player;
    Song *song;

public:
    PlayCommand(MusicPlayer *p, Song *s) {
        player = p;
        song = s;
    }

    void execute() override {
        player->play(song);
    }

    void undo() override {
        cout << "[UNDO] : Stopped - " << song->title << endl;
    }
};

// MusicPlayer* player = MusicPlayer::getInstance();
// Song s("Kesariya", "Arijit Singh", 240);
//
// PlayCommand cmd(player, &s);
// cmd.execute()
// → player->play(&s)
// → Now Playing : Kesariya - Arijit Singh [240 sec]
// → notifyAll() chala
// → [HISTORY] : Kesariya added to history
// → [UI] : Now Playing - Kesariya by Arijit Singh
//
// cmd.undo()
// → [UNDO] : Stopped - Kesariya

class NextCommand : public ICommand {
    MusicPlayer *player;
    vector<Song *> &playlist; // reference member
    int &currentIndex;

public:
    NextCommand(MusicPlayer *p, vector<Song *> &pl, int &idx)
        : player(p), playlist(pl), currentIndex(idx) {
    }

    void execute() override {
        if (currentIndex < playlist.size() - 1) {
            currentIndex++;
            player->play(playlist[currentIndex]);
        } else {
            cout << "Last song hai — aage kuch nahi!" << endl;
        }
    }

    void undo() override {
        if (currentIndex > 0) {
            currentIndex--;
            player->play(playlist[currentIndex]);
        } else {
            cout << "Pehla song hai — peeche kuch nahi!" << endl;
        }
    }
};

class MusicController {
    vector<ICommand *> history;

public:
    void pressButton(ICommand *cmd) {
        cmd->execute();
        history.push_back(cmd);
    }

    void pressUndo() {
        if (history.empty()) {
            cout << "Nothing to undo!" << endl;
            return;
        }
        ICommand *last = history.back();
        last->undo();
        history.pop_back();
        delete last;
    }

    ~MusicController() {
        for (auto *cmd: history) delete cmd; // cleanup remaining
    }
};

class SpotifyFacade {
    MusicPlayer *player;
    MusicController controller;
    HistoryObserver historyObs;
    UIObserver uiObs;
    vector<Song *> songs;
    int currentIndex;

public:
    SpotifyFacade() {
        currentIndex = 0;
        player = MusicPlayer::getInstance();
        player->attach(&historyObs);
        player->attach(&uiObs);
    }

    void addSong(Song *song) {
        songs.push_back(song);
        cout << "Song Added : " << song->title << endl;
    }

    IUser *login(string type, string name) {
        IUser *user = UserFactory::createUser(type, name);
        cout << "--- Welcome to Spotify ---" << endl;
        cout << "User : " << user->getUsername() << " [" << user->getUserType() << "]" << endl;
        if (user->hasAds())
            cout << "Ads : ON" << endl;
        else
            cout << "Ads : OFF" << endl;
        if (user->canDownload())
            cout << "Download : Enabled" << endl;
        else
            cout << "Download : Disabled" << endl;
        return user;
    }

    void play(int index) {
        if (index >= songs.size()) {
            cout << "Song nahi hai!" << endl;
            return;
        }
        currentIndex = index;
        PlayCommand *cmd = new PlayCommand(player, songs[index]);
        controller.pressButton(cmd);
    }

    void next() {
        NextCommand *cmd = new NextCommand(player, songs, currentIndex);
        controller.pressButton(cmd);
    }

    void undo() {
        controller.pressUndo();
    }

    void showHistory() {
        historyObs.showHistory();
    }
};


int main() {
    SpotifyFacade spotify;

    // Songs add karo
    Song s1("Kesariya", "Arijit Singh", 240);
    Song s2("Tum Hi Ho", "Arijit Singh", 260);
    Song s3("Channa Mereya", "Arijit Singh", 280);

    spotify.addSong(&s1);
    spotify.addSong(&s2);
    spotify.addSong(&s3);

    // Login karo
    IUser *user = spotify.login("premium", "Shivam");

    cout << "\n--- Playing Songs ---" << endl;
    spotify.play(0);
    spotify.play(1);
    spotify.next();

    cout << "\n--- Undo ---" << endl;
    spotify.undo();
    spotify.undo();

    cout << "\n--- History ---" << endl;
    spotify.showHistory();

    return 0;
}
