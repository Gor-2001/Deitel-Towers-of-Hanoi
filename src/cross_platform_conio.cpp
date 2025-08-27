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

// Function to set the terminal to non-canonical mode
// This is needed to get non-echoing, non-buffered input.
void set_terminal_mode() {
    #if defined(__unix__)
        struct termios t;
        tcgetattr(STDIN_FILENO, &t);
        t.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &t);
    #endif
}

// Function to restore the terminal to canonical mode
// This should be called before the program exits.
void restore_terminal_mode() {
    #if defined(__unix__)
        struct termios t;
        tcgetattr(STDIN_FILENO, &t);
        t.c_lflag |= (ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &t);
    #endif
}


char waitForInput(
    const std::string& message,
    const std::string& allowedChars
) {

    CLEAR_SCREEN();
    std::cout << message << std::endl;

    char ch;
    bool flag = true;

    while (flag) {
        if (_KBHIT()) {
            ch = __GET_CH();

            if (allowedChars.find(ch) != std::string::npos) {
                flag = false;
            }
        }
    }

    CLEAR_SCREEN();
    return ch;
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