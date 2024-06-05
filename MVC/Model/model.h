#pragma once
#include <string>
#include <vector>
#include <cstring>
#include <fstream>
#include <filesystem>
#include <iostream>

#define SRC "/data/fpt_fresher/playlist/" // edit this

class Media
{
public:
    std::string name;
    std::string artist;
    std::string album;
    unsigned int year;
    int duration;
    Media() {}
    Media(std::string &n, std::string &art, std::string &alb, unsigned int &y, int dur)
        : name(n), artist(art), album(alb), year(y), duration(dur)
    {
    }
    Media(const Media &input);
};

class Playlist
{
private:
    std::string __name; // path to playlist file

public:
    std::vector<std::string> __list; // vector contain path of media file in playlist file

    Playlist() {}
    Playlist(const std::string &name);
    std::string getName();
    void addFile(const std::vector<std::string> &file);
    void removeFile(int index);
    void rename(const std::string &name);
};