#include <conio.h>
#include "towers.h"

int main() {
    char ch;
    bool needsRedraw = true;
    Towers towers(3);

    while (true) {
        if (needsRedraw) {
            system("cls");
            towers.displayPic();
            needsRedraw = false;
        }

        if (_kbhit()) {
            ch = _getch();

            switch (ch) {

            // Validate
            case 13:
                if(towers.winningPosition()){
                    system("cls");
                    std::cout << "You Win.\n";
                    return 0;
                }
                break;

            // Escape
            case 27:
                system("cls");
                std::cout << "ESC pressed. Exiting.\n";
                return 0;

            // Move Up
            case 72:
                towers.diskMoveUp();
                break;

            // Move Left
            case 75:
                towers.cursorMoveLeft();
                break;

            // Move Right
            case 77:
                towers.cursorMoveRight();
                break;

            // Move Down
            case 80:
                towers.diskMoveDown();
                break;

            default:
                break;
            }
        }
        Sleep(10);
    }

    return 0;
}
