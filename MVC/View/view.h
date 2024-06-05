#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <model.h>
// #include "control.h"

#define TITLE_WIDTH 30
#define ARTIRST_WIDTH 25
#define ALBUM_WIDTH 20
#define YEAR_WIDTH 10

class Screen
{
    int id = 0;

public:
    static Media media;
    static std::string playlist;
    static std::string name;
    static std::vector<std::string> usb_path;
    static int volume;
    Screen(){};
    void set_metedata(const Media &input);
    void print_metadata(const int &index);
    void print_metadata_invalid(const int &index);
    void print_table();
    void print_end_table(const int &page, const int &total_page);
    void set_playlist_name(const std::string &pl_name);
    void print_playlist_name(const int &index);
    void print_media_name();
    virtual ~Screen(){};
    virtual void display(int input = 0) = 0;
    virtual std::string getChoice() = 0;
    virtual int getID();
};

class Screen_start : public Screen
{
    int id = 1;

public:
    Screen_start() {}
    void display(int input = 0);
    std::string getChoice();
    int getID();
};

class Screen_find : public Screen
{
    int id = 2;

public:
    Screen_find() {}
    void display(int input = 0);
    std::string getChoice();
    int getID();
};

class Screen_find_result : public Screen
{
    int id = 3;

public:
    Screen_find_result(){};
    void display(int input = 0);
    std::string getChoice();
    int getID();
};

class Screen_playlist : public Screen
{
    int id = 4;

public:
    void display(int input = 0);
    std::string getChoice();
    int getID();
};

class Screen_playlist_element : public Screen
{
    int id = 5;

public:
    void display(int input = 0);
    std::string getChoice();
    int getID();
};

class Screen_playlist_element_add : public Screen
{
    int id = 6;

public:
    void display(int input = 0);
    std::string getChoice();
    int getID();
};

class Screen_media_detail : public Screen
{
    int id = 7;

public:
    void display(int input = 0);
    std::string getChoice();
    int getID();
};

class Screen_playlist_element_add_list : public Screen
{
    int id = 8;

public:
    void display(int input = 0);
    std::string getChoice();
    int getID();
};

class Screen_playlist_add : public Screen
{
    int id = 9;

public:
    void display(int input = 0);
    std::string getChoice();
    int getID();
};

class Screen_playlist_delete : public Screen
{
    int id = 10;

public:
    void display(int input = 0);
    std::string getChoice();
    int getID();
};

class Screen_playlist_element_delete : public Screen
{
    int id = 11;

public:
    void display(int input = 0);
    std::string getChoice();
    int getID();
};

class Screen_playlist_rename : public Screen
{
    int id = 12;

public:
    void display(int input = 0);
    std::string getChoice();
    int getID();
};

class Screen_media_rename : public Screen
{
    int id = 13;

public:
    void display(int input = 0);
    std::string getChoice();
    int getID();
};

class Screen_play_media: public Screen 
{
    int id = 14;

public:
    void display(int input = 0);
    std::string getChoice();
    int getID();
};

class Screen_usb : public Screen 
{
    int id = 15;

public:
    void display(int input = 0);
    std::string getChoice();
    int getID();
};

void clean_stdin();
// class Screen_playlist_edit : public Screen
// {
// public:
//     void display(int input = 0);
//     std::string getChoice();
// };

// class Screen_playlist_delete : public Screen
// {
// public:
//     void display(int input = 0);
//     std::string getChoice();
// };

// class Screen_playlist_delete : public Screen
// {
// public:
//     void display(int input = 0);
//     std::string getChoice();
// };

// void clean_stdin();
// void clear_terminal();