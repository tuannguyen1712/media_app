#include "control.h"
#include <string>
#include <cstring>

// const char *ext1 = ".c";
// const char *ext2 = ".cpp";

const char *ext1 = ".mp3";
const char *ext2 = ".mp4";

std::string opt;

std::vector<std::string> list_files;
int cnt = 0;
int page = 0;
int pli = 0;

int page_playlist_element = 0;

int media_file_index = 0;

Mix_Music *music = NULL;
volatile int is_play = 0;
volatile int is_pause = 0;
volatile int is_fst = 0;
volatile time_t last = 0;
volatile time_t current = 0;
volatile time_t diff = 0;
int size = 0;
std::atomic<int> volume(MIX_MAX_VOLUME / 2);

std::vector<std::string> playlists;

Application::Application()
{
    Screen_stack.push(new Screen_start());
    playlists = findPlaylist();
    for (int i = 0; i < (int)playlists.size(); i++)
    {
        List_playlist.push_back(Playlist(playlists[i]));
    }
}

Application::~Application()
{
    while (!Screen_stack.empty())
    {
        delete Screen_stack.top();
        Screen_stack.pop();
    }
}

void Application::run_app()
{
    while (!Screen_stack.empty())
    {
        int cur_id = Screen_stack.top()->getID();
        switch (cur_id)
        {
        case 1:
            Screen_start_act();
            break;
        case 2:
            Screen_find_act();
            break;
        case 3:
            Screen_find_result_act();
            break;
        case 4:
            Screen_playlist_act();
            break;
        case 5:
            Screen_playlist_element_act();
            break;
        case 6:
            Screen_playlist_element_add_act();
            break;
        case 7:
            Screen_media_detail_act();
            break;
        case 8:
            Screen_playlist_element_add_list_act();
            break;
        case 9:
            Screen_playlist_add_act();
            break;
        case 10:
            Screen_playlist_delete_act();
            break;
        case 11:
            Screen_playlist_element_delete_act();
            break;
        case 12:
            Screen_playlist_rename_act();
            break;
        case 13:
            Screen_media_rename_act();
            break;
        case 14:
            Screen_play_media_act();
            break;
        case 15:
            Screen_usb_act();
            break;
        default:
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Application::Screen_start_act()
{
    Screen_stack.top()->display();
    opt = Screen_stack.top()->getChoice();
    if (opt == "1")
    {
        Screen_stack.push(new Screen_find());
    }
    else if (opt == "2")
    {
        Screen_stack.push(new Screen_playlist());
    }
    else if (opt == "3")
    {
        //USB
        std::vector<std::string> result = checkUSB();
        if (!result.empty()) {
            Screen_stack.top()->usb_path = result;
            Screen_stack.push(new Screen_usb());
        }
    }
    else if (opt == "4")
    {
        delete Screen_stack.top();
        Screen_stack.pop();
    }

    // switch (opt)
    // {
    // case "1":
    //     Screen_stack.push(new Screen_find());
    //     break;
    // case "2":
    //     Screen_stack.push(new Screen_playlist());
    //     break;
    //     // case "3":
    //     //     Screen_stack.push(new Screen_find());
    //     // case "4":
    //     //     Screen_stack.push(new Screen_find());
    //     // case "5":
    //     //     Screen_stack.push(new Screen_find());
    // case 6:
    //     return;
    // default:
    //     break;
    // }
}

void Application::Screen_find_act()
{
    Screen_stack.top()->display();
    opt = Screen_stack.top()->getChoice();
    if (opt == "B" || opt == "b")
    {
        delete Screen_stack.top();
        Screen_stack.pop();
    }
    else if (std::filesystem::exists(opt))
    {
        Screen_stack.push(new Screen_find_result);
        find_files(const_cast<char *>(opt.c_str()), list_files, cnt);
    }
}

void Application::Screen_find_result_act()
{
    Screen_stack.top()->display();
    size = list_files.size();
    int total_page = (size % 25 == 0) ? (size / 25) : (size / 25) + 1;
    print_files_in_pages(list_files, page, size, total_page);
    opt = Screen_stack.top()->getChoice();
    try {
        media_file_index = std::stoi(opt) - 1;
        if (media_file_index + 1 <= size && pathExists(const_cast<char *>(list_files[media_file_index].c_str())))
        {
            Screen_stack.push(new Screen_media_detail);
        }
    }
    catch(const std::invalid_argument& e) {
        if (opt == "B" || opt == "b")
        {
            delete Screen_stack.top();
            list_files.clear();
            page = 0;
            cnt = 0;
            Screen_stack.pop();
        }
        else if (opt == "N" || opt == "n")
        {
            if (page < total_page - 1)
            {
                page++;
            }
        }
        else if (opt == "P" || opt == "p")
        {
            if (page > 0)
            {
                page--;
            }
        }
    }
}

void Application::Screen_usb_act()
{
    Screen_stack.top()->display();
    opt = Screen_stack.top()->getChoice();
    
    try {
        int i = std::stoi(opt) - 1;
        if (i  < (int)Screen_stack.top()->usb_path.size()) {
            Screen_stack.push(new Screen_find_result);
            find_files(const_cast<char *>(Screen_stack.top()->usb_path[i].c_str()), list_files, cnt);
        }
    }
    catch (const std::invalid_argument &e)
    {
        if (opt == "B" || opt == "b")
        {
            delete Screen_stack.top();
            Screen_stack.pop();
        }
    }

}

void Application::Screen_playlist_act()
{
    Screen_stack.top()->display();

    for (int i = 0; i < PLAYLIST_NUM; i++)
    {
        if (i < (int)List_playlist.size())
        {
            Screen_stack.top()->set_playlist_name(getPlaylistName(List_playlist[i].getName()));
            Screen_stack.top()->print_playlist_name(i);
        }
    }
    opt = Screen_stack.top()->getChoice();
    try {
        pli = std::stoi(opt) - 1;
        if (pli + 1 <= (int)List_playlist.size() ) {
            Screen_stack.push(new Screen_playlist_element); 
        }
    }
    catch (const std::invalid_argument& e) {
        if (opt == "B" || opt == "b")
        {
            delete Screen_stack.top();
            Screen_stack.pop();
        }
        else if (opt == "A" || opt == "a")
        {
            Screen_stack.push(new Screen_playlist_add);
        }
        else if (opt == "D" || opt == "d")
        {
            Screen_stack.push(new Screen_playlist_delete);
        }
    }
    // else if (std::stoi(opt) <= (int)List_playlist.size() && opt.length())
    // {
    //     pli = std::stoi(opt) - 1;
    //     Screen_stack.push(new Screen_playlist_element);
    // }
}

void Application::Screen_playlist_add_act()
{
    Screen_stack.top()->display();
    opt = Screen_stack.top()->getChoice();
    if (opt == "B" || opt == "b")
    {
        delete Screen_stack.top();
        Screen_stack.pop();
    }
    else
    {
        createPlaylist(opt);
        delete Screen_stack.top();
        Screen_stack.pop();
    }
}

void Application::Screen_playlist_delete_act()
{
    Screen_stack.top()->display();
    opt = Screen_stack.top()->getChoice();
    if (opt == "B" || opt == "b")
    {
        delete Screen_stack.top();
        Screen_stack.pop();
    }
    try {
        int i = std::stoi(opt);
        if (i > 0 && i <= (int)List_playlist.size())
        {
            deletePlaylist(List_playlist[i - 1].getName());
            List_playlist.erase(List_playlist.begin() + i - 1);
            delete Screen_stack.top();
            Screen_stack.pop();
        }
    }
    catch (const std::invalid_argument& e) {}
    // else if (std::stoi(opt) <= (int)List_playlist.size() && opt.length())
    // {
    //     int i = std::stoi(opt);
    //     if (i > 0 && i <= (int)List_playlist.size())
    //     {
    //         deletePlaylist(List_playlist[i - 1].getName());
    //         List_playlist.erase(List_playlist.begin() + i - 1);
    //     }
    //     delete Screen_stack.top();
    //     Screen_stack.pop();
    // }
}

void Application::Screen_playlist_element_act()
{
    Screen_stack.top()->display();
    Screen_stack.top()->set_playlist_name(getPlaylistName(List_playlist[pli].getName()));
    Screen_stack.top()->print_playlist_name(pli);
    size = List_playlist[pli].__list.size();
    int total_page = (size % 25 == 0) ? (size / 25) : (size / 25) + 1;
    print_files_in_pages(List_playlist[pli].__list, page_playlist_element, size, total_page);
    opt = Screen_stack.top()->getChoice();
    try {
        media_file_index = std::stoi(opt) - 1;
        if (media_file_index +1 <= size && (const_cast<char *>(List_playlist[pli].__list[media_file_index].c_str())))
        {
            Screen_stack.push(new Screen_media_detail);
        }
    }
    catch (const std::invalid_argument& e) {
        if (opt == "B" || opt == "b")
        {
            page_playlist_element = 0;
            delete Screen_stack.top();
            Screen_stack.pop();
        }
        else if (opt == "A" || opt == "a")
        {
            Screen_stack.push(new Screen_playlist_element_add);
        }
        else if (opt == "D" || opt == "d")
        {
            page_playlist_element = 0;
            Screen_stack.push(new Screen_playlist_element_delete);
        }
        else if (opt == "R" || opt == "r")
        {
            Screen_stack.push(new Screen_playlist_rename);
        }
        else if (opt == "N" || opt == "n")
        {
            if (page_playlist_element < total_page - 1)
            {
                page_playlist_element++;
            }
        }
        else if (opt == "P" || opt == "p")
        {
            if (page_playlist_element > 0)
            {
                page_playlist_element--;
            }
        }
    }
    // else if (std::stoi(opt) <= size && opt.length())
    // {
    //     media_file_index = std::stoi(opt) - 1;
    //     if (pathExists(const_cast<char *>(List_playlist[pli].__list[media_file_index].c_str()))) {
    //         Screen_stack.push(new Screen_media_detail);
    //     }
    // }
}

void Application::Screen_playlist_element_add_act()
{
    Screen_stack.top()->display();
    Screen_stack.top()->set_playlist_name(getPlaylistName(List_playlist[pli].getName()));
    Screen_stack.top()->print_playlist_name(pli);
    opt = Screen_stack.top()->getChoice();
    if (opt == "B" || opt == "b")
    {
        delete Screen_stack.top();
        Screen_stack.pop();
    }
    else if (std::filesystem::exists(opt))
    {
        find_files(const_cast<char *>(opt.c_str()), list_files, cnt);
        Screen_stack.push(new Screen_playlist_element_add_list);
    }
}

void Application::Screen_playlist_element_add_list_act()
{
    Screen_stack.top()->display();
    Screen_stack.top()->set_playlist_name(getPlaylistName(List_playlist[pli].getName()));
    Screen_stack.top()->print_playlist_name(pli);
    size = list_files.size();
    int total_page = (size % 25 == 0) ? (size / 25) : (size / 25) + 1;
    print_files_in_pages(list_files, page, size, total_page);
    opt = Screen_stack.top()->getChoice();
    try {
        int i = std::stoi(opt) - 1;
        if (i + 1 <= size) {
            List_playlist[pli].__list.push_back(list_files[i]);
            List_playlist[pli].addFile(List_playlist[pli].__list);
        }
    }
    catch (const std::invalid_argument& e) {
        if (opt == "B" || opt == "b")
        {
            delete Screen_stack.top();
            list_files.clear();
            page = 0;
            cnt = 0;
            Screen_stack.pop();
        }
        else if (opt == "N" || opt == "n")
        {
            if (page < total_page - 1)
            {
                page++;
            }
        }
        else if (opt == "P" || opt == "p")
        {
            if (page > 0)
            {
                page--;
            }
        }
        else if (opt == "D" || opt == "d")
        {
            list_files.clear();
            page = 0;
            cnt = 0;
            delete Screen_stack.top();
            Screen_stack.pop();
            delete Screen_stack.top();
            Screen_stack.pop();
        }
    }
    // else if (std::stoi(opt) <= size && opt.length())
    // {
    //     int i = std::stoi(opt) - 1;
    //     List_playlist[pli].__list.push_back(list_files[i]);
    //     List_playlist[pli].addFile(List_playlist[pli].__list);
    // }
}

void Application::Screen_playlist_element_delete_act()
{
    Screen_stack.top()->display();
    Screen_stack.top()->set_playlist_name(getPlaylistName(List_playlist[pli].getName()));
    Screen_stack.top()->print_playlist_name(pli);
    size = List_playlist[pli].__list.size();
    int total_page = (size % 25 == 0) ? (size / 25) : (size / 25) + 1;
    print_files_in_pages(List_playlist[pli].__list, page_playlist_element, size, total_page);
    opt = Screen_stack.top()->getChoice();
    try {
        int i = std::stoi(opt) - 1;
        if (i + 1 <= size) {
            List_playlist[pli].removeFile(i);
        }
    }
    catch (const std::invalid_argument& e) {
        if (opt == "B" || opt == "b")
        {
            page_playlist_element = 0;
            delete Screen_stack.top();
            Screen_stack.pop();
        }
        else if (opt == "N" || opt == "n")
        {
            if (page_playlist_element < total_page - 1)
            {
                page_playlist_element++;
            }
        }
        else if (opt == "P" || opt == "p")
        {
            if (page_playlist_element > 0)
            {
                page_playlist_element--;
            }
        }
    }
    // else if (std::stoi(opt) <= size && opt.length())
    // {
    //     int i = std::stoi(opt) - 1;
    //     List_playlist[pli].removeFile(i);
    // }
}

void Application::Screen_playlist_rename_act()
{
    Screen_stack.top()->display();
    Screen_stack.top()->set_playlist_name(getPlaylistName(List_playlist[pli].getName()));
    Screen_stack.top()->print_playlist_name(pli);
    opt = Screen_stack.top()->getChoice();
    if (opt == "B" || opt == "b")
    {
        delete Screen_stack.top();
        Screen_stack.pop();
    }
    else
    {

        List_playlist[pli].rename(opt);
        delete Screen_stack.top();
        Screen_stack.pop();
    }
}

void Application::Screen_media_detail_act()
{
    
    if (list_files.empty())
    {
        Screen_stack.top()->set_metedata(GetMedia(List_playlist[pli].__list[media_file_index]));
    }
    else
    {
        Screen_stack.top()->set_metedata(GetMedia(list_files[media_file_index]));
    }
    Screen_stack.top()->display();
    opt = Screen_stack.top()->getChoice();
    if (opt == "B" || opt == "b")
    {
        delete Screen_stack.top();
        Screen_stack.pop();
    }
    else if (opt == "P" || opt == "p")
    {
        //multithread
        is_play = 1;
        is_fst = 1;
        last = time(NULL);
        if (SDL_Init(SDL_INIT_AUDIO) < 0)
        {
            std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
            is_play = 0;
        }
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
            SDL_Quit();
            is_play = 0;
        }
        if (list_files.empty())
        {
            // find_files(const_cast<char *>(opt.c_str()), list_files, cnt);
            music = Mix_LoadMUS(const_cast<char *>(List_playlist[pli].__list[media_file_index].c_str()));
        }
        else
        {
            music = Mix_LoadMUS(const_cast<char *>(list_files[media_file_index].c_str()));
        }
        if (!music)
        {
            std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
            Mix_CloseAudio();
            SDL_Quit();
            is_play = 0;
        }
        Screen_stack.top()->volume = volume;
        Mix_VolumeMusic(volume);
        if (Mix_PlayMusic(music, -1) == -1)
        {
            std::cerr << "Failed to play music: " << Mix_GetError() << std::endl;
            Mix_FreeMusic(music);
            Mix_CloseAudio();
            SDL_Quit();
            is_play = 0;
        }
        thread_play = std::thread(&Application::thread_play_media, this);
        Screen_stack.push(new Screen_play_media);
    }
    else if (opt == "R" || opt == "r")
    {
        Screen_stack.push(new Screen_media_rename);
    }
}

void Application::Screen_media_rename_act()
{
    // if (list_files.empty())
    // {
    //     Screen_stack.top()->set_metedata(GetMedia(List_playlist[pli].__list[media_file_index]));
    //     // Screen_stack.top()->name = GetName(List_playlist[pli].__list[media_file_index]);
    //     // Screen_stack.top()->print_media_name();
    // }
    // else
    // {
    //     Screen_stack.top()->set_metedata(GetMedia(list_files[media_file_index]));
    //     // Screen_stack.top()->name = GetName(list_files[media_file_index]);
    //     // Screen_stack.top()->print_media_name();
    // }
    Screen_stack.top()->display();
    opt = Screen_stack.top()->getChoice();
    if (opt == "B" || opt == "b")
    {
        delete Screen_stack.top();
        Screen_stack.pop();
    }
    else
    {
        if (list_files.empty())
        {
            Edit_Title(List_playlist[pli].__list[media_file_index], opt);
        }
        else
        {
            Edit_Title(list_files[media_file_index], opt);
        }
        delete Screen_stack.top();
        Screen_stack.pop();
    }
}

void Application::Screen_play_media_act()
{
    opt = Screen_stack.top()->getChoice();
    //std::cout << opt << std::endl;  get string from last line of screen(from thread). Fix?
    if (opt == "+") {
        volume = std::min(volume.load() + 16, MIX_MAX_VOLUME);
        Mix_VolumeMusic(volume);
        Screen_stack.top()->volume = volume;
    }
    else if (opt == "-") {
        volume = std::max(volume.load() - 16, 0);
        Mix_VolumeMusic(volume);
        Screen_stack.top()->volume = volume;
    }
    else if (opt == "P" || opt == "p") {
        if (is_pause)
        {
            Mix_ResumeMusic();
            is_pause = false;
        }
        else 
        {
            Mix_PauseMusic();
            is_pause = true;
            is_fst = 0;
        }
    }
    else if (opt == "S" || opt == "s") 
    {
    out1:
        is_fst = 1;
        media_file_index++;
        last = time(NULL);
        if (list_files.empty())
        {
            if (media_file_index >= (int) List_playlist[pli].__list.size())
            {
                media_file_index = 0;
            }
            if (!pathExists(const_cast<char *>(List_playlist[pli].__list[media_file_index].c_str()))) {
                goto out1;
            }
            Screen_stack.top()->set_metedata(GetMedia(List_playlist[pli].__list[media_file_index]));
        }
        else
        {
            if (media_file_index >= (int) list_files.size())
            {
                media_file_index = 0;
            }
            if (!pathExists(const_cast<char *>(list_files[media_file_index].c_str())))
            {
                goto out1;
            }
            Screen_stack.top()->set_metedata(GetMedia(list_files[media_file_index]));
        }
        //
        if (music != NULL) {
            Mix_FreeMusic(music);
            music = NULL;
        }
        if (list_files.empty())
        {

            music = Mix_LoadMUS(const_cast<char *>(List_playlist[pli].__list[media_file_index].c_str()));
        }
        else
        {
            music = Mix_LoadMUS(const_cast<char *>(list_files[media_file_index].c_str()));
        }
        if (!music)
        {
            std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
            Mix_CloseAudio();
            SDL_Quit();
            is_play = 0;
        }
        if (Mix_PlayMusic(music, -1) == -1)
        {
            std::cerr << "Failed to play music: " << Mix_GetError() << std::endl;
            Mix_FreeMusic(music);
            Mix_CloseAudio();
            SDL_Quit();
            is_play = 0;
        }
    }
    else if (opt == "B" || opt == "b")
    {
    out2:
        is_fst = 1;
        media_file_index--;
        last = time(NULL);
        if (list_files.empty())
        {
            if (media_file_index < 0)
            {
                media_file_index = List_playlist[pli].__list.size() - 1;
            }
            if (!pathExists(const_cast<char *>(List_playlist[pli].__list[media_file_index].c_str())))
            {
                goto out2;
            }
            Screen_stack.top()->set_metedata(GetMedia(List_playlist[pli].__list[media_file_index]));
        }
        else
        {
            if (media_file_index < 0)
            {
                media_file_index = list_files.size() - 1;
            }
            if (!pathExists(const_cast<char *>(list_files[media_file_index].c_str())))
            {
                goto out2;
            }
            Screen_stack.top()->set_metedata(GetMedia(list_files[media_file_index]));
        }
        //
        if (music != NULL)
        {
            Mix_FreeMusic(music);
            music = NULL;
        }
        if (list_files.empty())
        {

            music = Mix_LoadMUS(const_cast<char *>(List_playlist[pli].__list[media_file_index].c_str()));
        }
        else
        {
            music = Mix_LoadMUS(const_cast<char *>(list_files[media_file_index].c_str()));
        }
        if (!music)
        {
            std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
            Mix_CloseAudio();
            SDL_Quit();
            is_play = 0;
        }
        if (Mix_PlayMusic(music, -1) == -1)
        {
            std::cerr << "Failed to play music: " << Mix_GetError() << std::endl;
            Mix_FreeMusic(music);
            Mix_CloseAudio();
            SDL_Quit();
            is_play = 0;
        }
    }
    else if (opt == "R" || opt == "r")
    {
        is_play = 0;
        thread_play.join();
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        SDL_Quit();
        delete Screen_stack.top();
        Screen_stack.pop();
        delete Screen_stack.top();
        Screen_stack.pop();
        clean_stdin();
    }

}

void find_files(const char *directory, std::vector<std::string> &files, int &file_count)
{
    struct dirent *entry;
    DIR *dp = opendir(directory);
    if (dp == NULL)
    {
        perror("opendir");
        return;
    }

    char path[PATH_MAX];
    struct stat statbuf;

    while ((entry = readdir(dp)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s", directory, entry->d_name);
        if (stat(path, &statbuf) == -1)
        {
            perror("stat");
            continue;
        }

        if (S_ISDIR(statbuf.st_mode))
        {
            // Recursively search in the subdirectory
            find_files(path, files, file_count);
        }
        else if (S_ISREG(statbuf.st_mode))
        {
            // Check the file extension
            const char *ext = strrchr(entry->d_name, '.');
            if (ext != NULL && (strcmp(ext, ext1) == 0 || strcmp(ext, ext2) == 0))
            {
                // strncpy(files[*file_count], path, PATH_MAX);
                files.push_back(path);
                // files[*file_count] = path;
                // (*file_count)++;
            }
        }
    }
    file_count = files.size();
    closedir(dp);
}

void Application::print_files_in_pages(std::vector<std::string> files, const int &page, const int &size, const int &total_page)
{
    Screen_stack.top()->print_table();
    for (int i = page * 25 + 1; i <= (page + 1) * 25 && i <= size; i++)
    {
        if (pathExists(const_cast<char *>(files[i - 1].c_str())))
        {
            Screen_stack.top()->set_metedata(GetMedia(files[i - 1]));
            Screen_stack.top()->print_metadata(i);
        }
        else {
            Screen_stack.top()->print_metadata_invalid(i);
        }
    }
    Screen_stack.top()->print_end_table(page, total_page);
}

void writeToFile(const std::vector<std::string> &vec, const std::string &filename)
{
    std::ofstream outFile(filename);
    if (!outFile)
    {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    for (const auto &str : vec)
    {
        outFile << str << '\n';
    }

    outFile.close();
}

void readFromFile(std::vector<std::string> &vec, const std::string &filename)
{
    vec.clear();
    std::ifstream inFile(filename);
    if (!inFile)
    {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
    }

    std::string line;
    while (std::getline(inFile, line))
    {
        vec.push_back(line);
    }

    inFile.close();
}

std::string getPlaylistName(const std::string &filePath)
{
    // find position of /
    size_t lastSlashPos = filePath.find_last_of("/\\");
    // set start position = 0 if not found /
    size_t start = (lastSlashPos == std::string::npos) ? 0 : lastSlashPos + 1;
    // find position of .
    size_t lastDotPos = filePath.find_last_of('.');
    size_t end = (lastDotPos == std::string::npos || lastDotPos < start) ? filePath.length() : lastDotPos;
    return filePath.substr(start, end - start);
}

std::vector<std::string> findPlaylist()
{
    std::string folderPath = SRC;
    std::vector<std::string> findPlaylist;

    for (const auto &entry : std::filesystem::directory_iterator(folderPath))
    {
        if (entry.is_regular_file())
        {
            std::string fileName = entry.path().filename().string();
            if (fileName.find('.') == std::string::npos)
            {
                findPlaylist.push_back(fileName);
            }
        }
    }

    return findPlaylist;
}

bool Application::createPlaylist(const std::string &fileName)
{
    std::string folderPath = SRC;

    std::string filePath = folderPath + "/" + fileName;

    std::ofstream outFile(filePath);
    if (outFile)
    {
        outFile.close();
        List_playlist.push_back(Playlist(fileName));
        return true;
    }
    else
    {
        return false;
    }
}

bool Application::deletePlaylist(const std::string &fileName)
{
    // std::string folderPath = SRC;
    // std::filesystem::path filePath = std::filesystem::path(folderPath) / fileName;

    if (std::filesystem::exists(fileName) && std::filesystem::is_regular_file(fileName))
    {
        try
        {
            std::filesystem::remove(fileName);
            return true;
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void Application::thread_play_media() 
{
    while (is_play) {
        if (!is_pause && is_fst) {
            current = time(NULL);
        }
        else if (!is_pause && !is_fst) {
            current = time(NULL);
            last = current - diff;
            diff = 0;
            is_fst = 1;
        }
        else {
            diff = current - last;
        }
        Screen_stack.top()->display((int) difftime(current, last));
        if ((int)difftime(current, last) >= Screen_stack.top()->media.duration) 
        {
        out:
            media_file_index++;
            if (list_files.empty())
            {
                if (media_file_index >= (int)List_playlist[pli].__list.size())
                {
                    media_file_index = 0;
                }
                if (!pathExists(const_cast<char *>(List_playlist[pli].__list[media_file_index].c_str())))
                {
                    goto out;
                }
                Screen_stack.top()->set_metedata(GetMedia(List_playlist[pli].__list[media_file_index]));
            }
            else
            {
                if (media_file_index >= (int)list_files.size())
                {
                    media_file_index = 0;
                }
                if (!pathExists(const_cast<char *>(list_files[media_file_index].c_str())))
                {
                    goto out;
                }
                Screen_stack.top()->set_metedata(GetMedia(list_files[media_file_index]));
            }
            //
            last = time(NULL);
            if (music != NULL)
            {
                Mix_FreeMusic(music);
                music = NULL;
            }
            if (list_files.empty())
            {

                music = Mix_LoadMUS(const_cast<char *>(List_playlist[pli].__list[media_file_index].c_str()));
            }
            else
            {
                music = Mix_LoadMUS(const_cast<char *>(list_files[media_file_index].c_str()));
            }
            if (!music)
            {
                std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
                Mix_CloseAudio();
                SDL_Quit();
                is_play = 0;
            }
            if (Mix_PlayMusic(music, -1) == -1)
            {
                std::cerr << "Failed to play music: " << Mix_GetError() << std::endl;
                Mix_FreeMusic(music);
                Mix_CloseAudio();
                SDL_Quit();
                is_play = 0;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}