#include <model.h>

Media::Media(const Media &input)
{
    name = input.name;
    artist = input.artist;
    album = input.album;
    year = input.year;
    duration = input.duration;
}

Playlist::Playlist(const std::string &name)
{
    __name = SRC + name;

    std::ifstream inFile(__name);
    if (!inFile)

    {
        std::cerr << "Failed to open file for reading: " << __name << std::endl;
    }

    std::string line;
    while (std::getline(inFile, line))
    {
        __list.push_back(line);
    }

    inFile.close();
}

std::string Playlist::getName()
{
    return __name;
}

void Playlist::addFile(const std::vector<std::string> &file)
{
    // std::string file_path = SRC + file;
    std::ofstream outFile(__name);
    if (!outFile)
    {
        return;
    }

    for (const auto &str : file)
    {
        outFile << str << '\n';
    }
    __list = file;
    outFile.close();
}

void Playlist::removeFile(int index)
{
    __list.erase(__list.begin() + index);
    addFile(__list);
}

void Playlist::rename(const std::string &name)
{
    std::string new_name = SRC + name;
    std::filesystem::rename(__name, new_name);
    __name = new_name;
}