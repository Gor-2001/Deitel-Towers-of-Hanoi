// cross_platform_conio.h
// Header file for cross-platform console functions.

#ifndef CROSS_PLATFORM_CONIO_H
#define CROSS_PLATFORM_CONIO_H

// Define a macro for Windows platform
#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>
    #include <stdlib.h>
    #include <windows.h>

    // Macro for clearing the screen on Windows
    #define CLEAR_SCREEN() system("cls")

    // The _getch() and _kbhit() functions are already available.
    // Macro for cross-platform sleep
    #define SLEEP(ms) Sleep(ms)

    // gotoxy function prototype for Windows
    void gotoxy(const int x, const int y);

// Define a macro for Linux platform
#elif defined(__linux__)
    #include <stdio.h>
    #include <termios.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <sys/select.h>
    #include <time.h>

    // Macro for clearing the screen on Linux
    #define CLEAR_SCREEN() system("clear")

    // Function prototypes for Linux
    char _getch();
    int _kbhit();
    void SLEEP(int ms);
    void gotoxy(const int x, const int y);

#else
    #error "Unsupported platform"
#endif

#endif // CROSS_PLATFORM_CONIO_H
