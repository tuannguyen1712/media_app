#pragma once
#include <iostream>
#include <stdio.h>
#include <filesystem>
#include <string>
#include <atomic>
#include <chrono>
#include <iomanip>
#include <vector>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/audioproperties.h>
#include <model.h>

// void Print_Table();
std::string GetName(const std::string &path);
Media GetMedia(const std::string &path);
// void Print_end_Table();
// void Print_Metadata(const std::string &path);
bool Edit_Title(const std::string &path, std::string new_title);
bool Edit_Artist(const std::string &path, std::string new_artist);
bool Edit_Album(const std::string &path, std::string new_album);
bool Edit_Year(const std::string &path, int new_year);