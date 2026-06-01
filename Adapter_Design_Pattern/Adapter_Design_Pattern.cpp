//
// Created by shiva on 01-06-2026.
//
#include <iostream>
#include <string>
using namespace std;

class IAdvancedPlayer {
public:
    virtual void playMP4(string filename)=0;
    virtual void playVLC(string filename)=0;
    virtual ~IAdvancedPlayer(){}
};

class AdvancedPlayer:public IAdvancedPlayer {
public:
    void playMP4(string filename) override {
        cout<<"Playing MP4 : "<<filename<<endl;
    }
    void playVLC(string filename) override {
        cout<<"Playing VLC:"<<filename<<endl;
    }
};

class IMediaPlayer  {
public:
    virtual void play(string audioType,string fileName)=0;
    virtual ~IMediaPlayer (){}
};

// IAdvancedPlayer → playMP4(), playVLC()  — alag alag functions
// IMediaPlayer     → play()                — ek hi function, type pass karo


class MediaAdapter :public IMediaPlayer  {
    IAdvancedPlayer* advanced_player_;
public:
    MediaAdapter () {
        advanced_player_=new AdvancedPlayer();
    }
    void play(string audioType, string fileName)override {
        if (audioType=="mp4") {
            advanced_player_->playMP4(fileName);
        }else if (audioType=="vlc") {
            advanced_player_->playVLC(fileName);
        }else {
            cout<<"Format not supported...."<<audioType<<endl;
        }
    }
};
//============= D R Y R U N===================
// MediaAdapter adapter;
//
// adapter.play("mp4", "movie.mp4")
// → advancedPlayer->playMP4("movie.mp4")
// → Playing MP4 : movie.mp4
//
// adapter.play("vlc", "video.vlc")
// → advancedPlayer->playVLC("video.vlc")
// → Playing VLC : video.vlc
//
// adapter.play("avi", "clip.avi")
// → Format not supported : avi



class AudioPlayer : public IMediaPlayer  {
    MediaAdapter* adapter;
public:
    AudioPlayer() {
        adapter = new MediaAdapter();
    }
    void play(string audioType,string fileName)override {
        if (audioType=="mp3") {
            cout<<"Playing mp 3 : "<<fileName<<endl;
        }else if (audioType=="mp4" || audioType=="vlc") {
            adapter->play(audioType,fileName);
        }else {
            cout<<"Format not supported..."<<audioType<<endl;
        }
    }
};

int main() {
    AudioPlayer player;
    player.play("mp3","song1.mp3");
    player.play("mp4","video1.mp4");
    player.play("mp3","song4.mp3");
    player.play("mp4","file2.mp4");
    return 0;
}