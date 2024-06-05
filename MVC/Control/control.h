#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <stack>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "view.h"
#include "model.h"
#include "taglib.h"
#include "utility.h"

#define FILES_PER_PAGE 25
#define PLAYLIST_NUM 25

class Application
{
private:
    std::stack<Screen *> Screen_stack;
    std::vector<Playlist> List_playlist;    
    std::thread thread_play;

    void thread_play_media();
public:
    Application();
    ~Application();

    void run_app();

    void Screen_start_act();
    void Screen_find_act();
    void Screen_find_result_act();
    void Screen_playlist_act();
    void Screen_playlist_element_act();
    void Screen_playlist_element_add_act();
    void Screen_playlist_element_delete_act();
    void Screen_media_detail_act();
    void Screen_playlist_element_add_list_act();
    void Screen_playlist_add_act();
    void Screen_playlist_delete_act();
    void Screen_playlist_rename_act();
    void Screen_media_rename_act();
    void Screen_play_media_act();
    void Screen_usb_act();

    bool createPlaylist(const std::string &fileName);
    bool deletePlaylist(const std::string &fileName);
    void print_files_in_pages(std::vector<std::string> files, const int &page, const int &size, const int &total_page);
};

// void print_files_in_pages(std::vector<std::string> files, const int &page, const int &size, const int &total_page);
void find_files(const char *directory, std::vector<std::string> &files, int &file_count);

void writeToFile(const std::vector<std::string> &vec, const std::string &filename);
void readFromFile(std::vector<std::string> &vec, const std::string &filename);
std::string getPlaylistName(const std::string &filePath);
std::vector<std::string> findPlaylist();