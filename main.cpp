#include "towers.h"
#include <conio.h>

int main(int argc, char** argv)
{
    Towers towers(15);
    //towers.displayNum();
    towers.displayPic();

    while (true) {
        if (_kbhit()) { 
            int ch = _getch();
            if (ch == 27)
                break;
        }
    }

    std::cout << "ESC pressed. Exiting.\n";

    return 0;
}
