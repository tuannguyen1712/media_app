#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <dirent.h>
#include <cstring>
#include <string>
#include <vector>

bool pathExists(const char *path);
std::string getUsername();
std::vector<std::string> findUSBs(const std::string &userPath);

std::vector<std::string> checkUSB();