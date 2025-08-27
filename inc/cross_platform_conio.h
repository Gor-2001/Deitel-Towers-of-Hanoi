// cross_platform_conio.h
// Header file for cross-platform console functions.

#ifndef CROSS_PLATFORM_CONIO_H
#define CROSS_PLATFORM_CONIO_H

#include <cstdlib>
#include <iostream>

void gotoxy(const int x, const int y);
char waitForInput(const std::string& message, const std::string& allowedChars);
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
    #error "Unsupported platform. Cannot define __GET_CH() and _KBHIT()."
#endif


#endif // CROSS_PLATFORM_CONIO_H
