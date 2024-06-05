#include "utility.h"

bool pathExists(const char *path)
{
    struct stat info;
    return (stat(path, &info) == 0);
}

// get user name
std::string getUsername()
{
    struct passwd *pw = getpwuid(getuid());
    return std::string(pw->pw_name);
}

// find usb which has mounted
std::string findUSB(const std::string &userPath)
{
    DIR *dir = opendir(userPath.c_str());
    if (dir == nullptr)
    {
        return "";
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr)
    {
        if (entry->d_type == DT_DIR)
        {
            std::string usbPath = userPath + "/" + entry->d_name;

            // Bo qua "." va ".."
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 && pathExists(usbPath.c_str()))
            {
                closedir(dir);
                return usbPath;
            }
        }
    }

    closedir(dir);
    return "";
}

std::vector<std::string> findUSBs(const std::string &userPath)
{
    std::vector<std::string> USB_Paths;
    DIR *dir = opendir(userPath.c_str());
    if (dir == nullptr)
    {
        return USB_Paths;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr)
    {
        if (entry->d_type == DT_DIR)
        {
            std::string usbPath = userPath + "/" + entry->d_name;

            // Bo qua "." va ".."
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 && pathExists(usbPath.c_str()))
            {
                USB_Paths.push_back(usbPath);
            }
        }
    }

    closedir(dir);
    return USB_Paths;
}

std::vector<std::string> checkUSB()
{
    std::string username = getUsername();
    std::string userPath = "/media/" + username;
    return findUSBs(userPath);
}