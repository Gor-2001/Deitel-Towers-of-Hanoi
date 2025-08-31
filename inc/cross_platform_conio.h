// cross_platform_conio.h
// Header file for cross-platform console functions.

#ifndef CROSS_PLATFORM_CONIO_H
#define CROSS_PLATFORM_CONIO_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <cstring>

namespace fs = std::filesystem;

fs::path get_message_path(const std::string& filename);
void print_file_content(const std::string& filename);
char waitForInput(const std::string& allowedChars);
void gotoxy(const int x, const int y);
void set_terminal_mode();
void restore_terminal_mode();

#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>
    #include <windows.h>
    #define SLEEP(n) Sleep(n)
    #define __GET_CH() _getch()
    #define _KBHIT() _kbhit()
    #define CLEAR_SCREEN() system("cls")
    #define ENTER_VALUE 13
#elif defined(__unix__) || defined(__linux__)
    #include <unistd.h>
    #include <termios.h>
    #include <sys/ioctl.h>
    #include <stdio.h>
    #include <unistd.h>
    #define SLEEP(n) usleep((n) * 1000)
    #define __GET_CH() getchar()
    int kbhit(void);
    #define _KBHIT() kbhit()
    #define CLEAR_SCREEN() system("clear")
    #define ENTER_VALUE 10
#else
    #error "Unsupported platform."
#endif

#define GRADING_INSTRUCTIONS   "grading_instructions.txt"
#define HELP_GUIDE             "help_guide.txt"
#define ESCAPE_WARNING         "escape_warning.txt"
#define START_MODE_SELECTION   "start_mode_selection.txt"
#define DIFFICULTY_SELECTION   "difficulty_selection.txt"


#endif // CROSS_PLATFORM_CONIO_H
