#include "cross_platform_conio.h"

void gotoxy(const int x, const int y) {
    #if defined(_WIN32) || defined(_WIN64)
        // Windows implementation
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    #elif defined(__unix__)
        // Unix implementation using ANSI escape codes
        printf("\033[%d;%dH", y + 1, x + 1);
        fflush(stdout); // Ensure the output is written immediately
    #endif
}

 #if defined(__unix__)
    int kbhit(void) {
        static struct termios oldt, newt;
        int bytesWaiting;

        // Save old terminal settings
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;

        // Disable canonical mode and echo
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        // Check how many bytes are waiting
        ioctl(STDIN_FILENO, FIONREAD, &bytesWaiting);

        // Restore terminal settings
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

        return bytesWaiting > 0;
    }
#endif