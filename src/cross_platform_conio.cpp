#include "cross_platform_conio.h"

void gotoxy(const int x, const int y) {

    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}