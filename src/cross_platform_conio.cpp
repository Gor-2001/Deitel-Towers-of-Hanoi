// cross_platform_conio.c
// Source file with implementations of cross-platform console functions.
#include "cross_platform_conio.h"

// Define a macro for Windows platform
#if defined(_WIN32) || defined(_WIN64)
    // Windows implementation of gotoxy
    void gotoxy(const int x, const int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

// Define a macro for Linux platform
#elif defined(__linux__)
    // Linux implementation of _getch()
    char _getch() {
        char ch;
        struct termios old_settings, new_settings;
        tcgetattr(STDIN_FILENO, &old_settings);
        new_settings = old_settings;
        new_settings.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
        return ch;
    }

    // Linux implementation of _kbhit()
    int _kbhit() {
        struct timeval tv;
        fd_set fds;
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
        return FD_ISSET(STDIN_FILENO, &fds);
    }
    
    // Linux implementation of SLEEP()
    void SLEEP(int ms) {
        struct timespec ts;
        ts.tv_sec = ms / 1000;
        ts.tv_nsec = (ms % 1000) * 1000000;
        nanosleep(&ts, NULL);
    }

    // Linux implementation of gotoxy()
    void gotoxy(const int x, const int y) {
        printf("\033[%d;%dH", y + 1, x + 1);
        fflush(stdout);
    }

#else
    #error "Unsupported platform"
#endif

