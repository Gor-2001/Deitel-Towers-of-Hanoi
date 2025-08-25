#include <iostream>
#include <conio.h>
#include <windows.h>

#include "towers.h"

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main() {
    char ch;
    bool needsRedraw = true;
    Towers towers(15, (cursorPosition_t)0);

    while (true) {
        if (needsRedraw) {
            system("cls");
            towers.displayPic();
            needsRedraw = false;
        }

        if (_kbhit()) {
            ch = _getch();

            switch (ch) {
            case 27:
                system("cls");
                std::cout << "ESC pressed. Exiting.\n";
                return 0;
            case 77:
                towers.cursorMoveRight();
                gotoxy(0, towers.getCursorY());
                towers.printCursor();
                break;
            case 75:
                towers.cursorMoveLeft();
                gotoxy(0, towers.getCursorY());
                towers.printCursor();
                break;
            default:
                break;
            }
        }
        Sleep(10);
    }

    return 0;
}
