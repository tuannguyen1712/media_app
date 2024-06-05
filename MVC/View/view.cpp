#include <iostream>
#include <string>
#include "view.h"

void clean_stdin(void)
{
    int c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void clear_terminal()
{
    printf("\033[2J\033[H");
}

Media Screen::media;
std::string Screen::playlist;
std::string Screen::name;
std::vector<std::string> Screen::usb_path;
int Screen::volume = 0;

void Screen::set_metedata(const Media &input)
{
    media.name = input.name;
    media.album = input.album;
    media.artist = input.artist;
    media.duration = input.duration;
    media.year = input.year;
}

void Screen::print_metadata(const int &index)
{
    std::cout << std::setw(4) << std::left << index;
    std::cout << "| " << std::setw(TITLE_WIDTH) << std::left << media.name
              << "| " << std::setw(ARTIRST_WIDTH) << std::left << media.artist
              << "| " << std::setw(ALBUM_WIDTH) << std::left << media.album
              << "| " << std::setw(YEAR_WIDTH) << std::left << media.year;
    printf("| %02d:%02d\n", media.duration / 60, media.duration % 60);
}

void Screen::print_metadata_invalid(const int &index)
{
    std::cout << std::setw(4) << std::left << index;
    std::cout << "| " << std::setw(TITLE_WIDTH) << std::left << "Path is not exist"
              << "| " << std::setw(ARTIRST_WIDTH) << std::left << ""
              << "| " << std::setw(ALBUM_WIDTH) << std::left << ""
              << "| " << std::setw(YEAR_WIDTH) << std::left << 0;
    printf("| %02d:%02d\n", 0, 0);
}

void Screen::print_table()
{
    std::cout << std::endl
              << std::setw(4) << std::left << "Num" << "| " << std::setw(TITLE_WIDTH) << std::left << "Name"
              << "| " << std::setw(ARTIRST_WIDTH) << std::left << "Artist"
              << "| " << std::setw(ALBUM_WIDTH) << std::left << "Album"
              << "| " << std::setw(YEAR_WIDTH) << std::left << "Year";
    std::cout << "| Duration" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------------------" << std::endl;
}
void Screen::print_end_table(const int &page, const int &total_page)
{
    std::cout << "------------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "Page" << page + 1 << "/" << total_page << std::endl
             << std::endl;
}

void Screen::set_playlist_name(const std::string &pl_name) {
    playlist = pl_name;
}
void Screen::print_playlist_name(const int &index) {
    std::cout << "[" << index + 1 << "]. " << playlist << std::endl;
}

void Screen::print_media_name()
{
    std::cout << name << std::endl;
}
int Screen::getID()
{
    return id;
}

void Screen_start::display(int input)
{
    clear_terminal();
    printf("-------------PLAY MEDIA FILE-------------\n"); // terminal
    printf("===================================================================================================================\n");
    printf("\nWELCOME\n");
    printf("\n");
    printf("1. Find media files.\n");
    printf("2. Playlist.\n");
    printf("3. Find from USB.\n");
    printf("4. Exit.\n");
}

std::string Screen_start::getChoice()
{
    std::string opt;
    printf("\n===================================================================================================================\n");
    std::cout << "Enter your choice: ";
    std::getline(std::cin, opt);
    // clean_stdin\(\);
    return opt;
}

int Screen_start::getID()
{
    return id;
}

void Screen_find::display(int input)
{
    clear_terminal();
    printf("-------------PLAY MEDIA FILE-------------\n"); // terminal1.1
    printf("===================================================================================================================\n");
    printf("\n1. Find media files.\n");
    printf("\n");
    printf("Enter directoty path: ");
    printf("\n\n<[B]ack\n");
}

std::string Screen_find::getChoice()
{
    std::string opt;
    printf("\n===================================================================================================================\n");
    std::cout << "Enter your choice: ";
    std::getline(std::cin, opt);
    // clean_stdin\(\);
    return opt;
}

int Screen_find::getID()
{
    return id;
}

void Screen_find_result::display(int input)
{
    clear_terminal();
    printf("-------------PLAY MEDIA FILE-------------\n");
    printf("===================================================================================================================\n");
    printf("\n1. Find media files.\n");
    printf("Result\n");
}

std::string Screen_find_result::getChoice()
{
    std::string opt;
    std::cout << "<[B]ack\t\t[P]revious\t\t[N]ext" << std::endl;
    printf("\n===================================================================================================================\n");
    std::cout << "Enter your choice: ";
    std::getline(std::cin, opt);
    // clean_stdin\(\);
    return opt;
}

int Screen_find_result::getID()
{
    return id;
}

void Screen_playlist::display(int input)
{
    clear_terminal();
    printf("-------------PLAY MEDIA FILE-------------\n");
    printf("===================================================================================================================\n");
    printf("\n2. Playlist.\n\n");
}

std::string Screen_playlist::getChoice()
{
    std::string opt;
    std::cout << "<[B]ack\t\t[A]dd\t\t[D]elete" << std::endl;
    printf("\n===================================================================================================================\n");
    std::cout << "\nEnter your choice: ";
    std::getline(std::cin, opt);
    // clean_stdin\(\);
    return opt;
}

int Screen_playlist::getID()
{
    return id;
}

void Screen_playlist_element::display(int input)
{
    clear_terminal();
    printf("-------------PLAY MEDIA FILE-------------\n");
    printf("===================================================================================================================\n");
    printf("\n2. Playlist.\n\n");
}

std::string Screen_playlist_element::getChoice()
{
    std::string opt;
    std::cout << "<[B]ack\t\t[A]dd\t\t[D]elete\t\t[R]ename\t\t[P]revious\t\t[N]ext" << std::endl;
    printf("\n===================================================================================================================\n");
    std::cout << "\nEnter your choice: ";
    std::getline(std::cin, opt);
    // clean_stdin\(\);
    return opt;
}

int Screen_playlist_element::getID()
{
    return id;
}

void Screen_playlist_element_add::display(int input)
{
    clear_terminal();
    printf("-------------PLAY MEDIA FILE-------------\n");
    printf("===================================================================================================================\n");
    printf("\n2. Playlist.\n\n");
}

std::string Screen_playlist_element_add::getChoice()
{
    std::string opt;
    std::cout << "Enter soucre folder: " << std::endl;
    std::cout << "<[B]ack" << std::endl;
    printf("\n===================================================================================================================\n");
    std::cout << "\nEnter your choice: ";
    std::getline(std::cin, opt);
    // clean_stdin\(\);
    return opt;
}

int Screen_playlist_element_add::getID()
{
    return id;
}

void Screen_playlist_element_add_list::display(int input)
{
    clear_terminal();
    printf("-------------PLAY MEDIA FILE-------------\n");
    printf("===================================================================================================================\n");
    printf("\n2. Playlist.\n\n");
}

std::string Screen_playlist_element_add_list::getChoice()
{
    std::string opt;
    std::cout << "Enter file number you want to add: " << std::endl;
    std::cout << "<[B]ack\t\t[P]revious\t\t[N]ext\t\t[D]one" << std::endl;
    printf("\n===================================================================================================================\n");
    std::cout << "\nEnter your choice: ";
    std::getline(std::cin, opt);
    // clean_stdin\(\);
    return opt;
}

int Screen_playlist_element_add_list::getID()
{
    return id;
}

void Screen_playlist_add::display(int input)
{
    clear_terminal();
    printf("-------------PLAY MEDIA FILE-------------\n");
    printf("===================================================================================================================\n");
    printf("\n2. Playlist.\nAdd new playlist\n");
}

std::string Screen_playlist_add::getChoice()
{
    std::string opt;
    printf("\n===================================================================================================================\n");
    std::cout << "Enter playlist name: " << std::endl;
    std::cout << "<[B]ack" << std::endl;
    std::cout << "\nEnter your choice: ";
    std::getline(std::cin, opt);
    // clean_stdin\(\);
    return opt;
}

int Screen_playlist_add::getID()
{
    return id;
}

void Screen_playlist_delete::display(int input)
{
    clear_terminal();
    printf("-------------PLAY MEDIA FILE-------------\n");
    printf("===================================================================================================================\n");
    printf("\n2. Playlist.\nDelete playlist\n");
}

std::string Screen_playlist_delete::getChoice()
{
    std::string opt;
    std::cout << "Enter index of playlist: " << std::endl;
    std::cout << "<[B]ack" << std::endl;
    printf("===================================================================================================================\n");
    std::cout << "\nEnter your choice: ";
    std::getline(std::cin, opt);
    // clean_stdin\(\);
    return opt;
}

int Screen_playlist_delete::getID()
{
    return id;
}

void Screen_playlist_element_delete::display(int input)
{
    clear_terminal();
    printf("-------------PLAY MEDIA FILE-------------\n");
    printf("===================================================================================================================\n");
    printf("\n2. Playlist.\nDelete element in playlist\n");
}

std::string Screen_playlist_element_delete::getChoice()
{
    std::string opt;
    std::cout << "Enter index of element: " << std::endl;
    std::cout << "<[B]ack\t\t[P]revious\t\t[N]ext" << std::endl;
    printf("===================================================================================================================\n");
    std::cout << "\nEnter your choice: ";
    std::getline(std::cin, opt);
    // clean_stdin\(\);
    return opt;
}

int Screen_playlist_element_delete::getID()
{
    return id;
}

void Screen_playlist_rename::display(int input)
{
    clear_terminal();
    printf("-------------PLAY MEDIA FILE-------------\n");
    printf("===================================================================================================================\n");
    printf("\n2. Playlist.\n");
}

std::string Screen_playlist_rename::getChoice()
{
    std::string opt;
    std::cout << "\nRename playlist\nEnter new name: " << std::endl;
    std::cout << "<[B]ack" << std::endl;
    printf("===================================================================================================================\n");
    std::cout << "\nEnter your choice: ";
    std::getline(std::cin, opt);
    // clean_stdin\(\);
    return opt;
}

int Screen_playlist_rename::getID()
{
    return id;
}

void Screen_media_detail::display(int input)
{
    clear_terminal();
    printf("-------------PLAY MEDIA FILE-------------\n");
    printf("===================================================================================================================\n");
    printf("\nCurrent file: ");
    std::cout << media.name << std::endl;
}

std::string Screen_media_detail::getChoice()
{
    std::string opt;
    std::cout << "<[B]ack\t\t|>[P]lay\t\t[R]ename" << std::endl;
    printf("===================================================================================================================\n");
    std::cout << "\nEnter your choice: ";
    std::getline(std::cin, opt);
    // clean_stdin\(\);
    return opt;
}

int Screen_media_detail::getID()
{
    return id;
}

void Screen_media_rename::display(int input)
{
    clear_terminal();
    printf("-------------PLAY MEDIA FILE-------------\n");
    printf("===================================================================================================================\n");
    printf("\nCurrent file: ");
    // std::cout << name << std::endl;
    std::cout << media.name << std::endl;
}

std::string Screen_media_rename::getChoice()
{
    std::string opt;
    std::cout << "Enter new name: \n";
    std::cout << "<[B]ack\t\t" << std::endl;
    printf("===================================================================================================================\n");
    std::cout << "\nEnter your choice: ";
    std::getline(std::cin, opt);
    // clean_stdin\(\);
    return opt;
}

int Screen_media_rename::getID()
{
    return id;
}

void Screen_play_media::display(int input)
{
    clear_terminal();
    printf("-------------PLAY MEDIA FILE-------------\n");
    printf("===================================================================================================================\n");
    printf("\nCurrent file: ");
    // std::cout << name << std::endl;
    std::cout << media.name << std::endl;
    printf("\n\t%02d:%02d/%02d:%02d\n", input / 60, input % 60, media.duration / 60, media.duration % 60);
    // std::cout << input / 60 << ":" << input % 60 << "/" << media.duration / 60 << "/" << media.duration % 60 << std::endl;
    double ratio = (double) input / media.duration;
    int num = (int) (ratio * 50);
    double v_ratio = (double) volume / 128;
    int v_level = (int)(v_ratio * 8);

    std::cout << "\t[";
    for (int i = 0 ; i < 50; i++) {
        if (i <= num || num == 49) {
            std::cout <<"#";
        }
        else
        {
            std::cout <<"-";
        }
    }
    std::cout << "]\n\n";
    std:: cout << "\tVolume: " << v_level << std::endl;
    std::cout << "\t[";
    for (int i = 1; i <= 8; i++) {
        if (i <= v_level) {
            std::cout << "=";
        }
        else {
            std::cout << " ";
        }
    }
    std::cout << "]\n";
    std::cout << "\n<[R]eturn\t\t|<|[B]ack\t\t[P]lay/[P]ause\t\t|>|[S]kip\t\t[-]Volume[+]" << std::endl;
    printf("===================================================================================================================\n");
    std::cout << "Enter your choice: \n";
}

std::string Screen_play_media::getChoice()
{
    std::string opt;
    // std::getline(std::cin, opt);
    std::cin >> opt;
    // clean_stdin\(\);
    return opt;
}

int Screen_play_media::getID()
{
    return id;
}

void Screen_usb::display(int input)
{
    clear_terminal();
    printf("-------------PLAY MEDIA FILE-------------\n"); // terminal1.1
    printf("===================================================================================================================\n");
    printf("\n3. Find from USB.\n");
    printf("\n");
    std::cout << "Current path: \n";
    for (int i = 0; i < (int) usb_path.size(); i++) {
        std::cout << "[" << i + 1 << "]. " << usb_path[i] << std::endl;
    }
    std::cout << std::endl;
    printf("Enter directoty path: ");
    printf("\n\n<[B]ack\n");
}

std::string Screen_usb::getChoice()
{
    std::string opt;
    printf("===================================================================================================================\n");
    std::cout << "\nEnter your choice: ";
    std::getline(std::cin, opt);
    // clean_stdin\(\);
    return opt;
}

int Screen_usb::getID()
{
    return id;
}