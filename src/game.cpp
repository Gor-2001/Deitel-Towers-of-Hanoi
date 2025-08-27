#include "game.h"


void Game::start() const {
    
    char ch;
    unsigned int disk_count = 3;
    gameStartingMode_t game_starting_mode = gameStartingModeBasic;
    std::string allowedChars;
    
    allowedChars.push_back(ENTER_VALUE);
    print_file_content(GRADING_INSTRUCTIONS);
    waitForInput(allowedChars);


    allowedChars = "rb";
    allowedChars.push_back(ENTER_VALUE);
    print_file_content(START_MODE_SELECTION);
    ch = waitForInput(allowedChars);
    if (ch == 'r')
        game_starting_mode = gameStartingModeRandom;


    allowedChars = "123456789";
    allowedChars.push_back(ENTER_VALUE);
    print_file_content(DIFFICULTY_SELECTION);
    ch = waitForInput(allowedChars);
    if(ch >= '1' && ch <= '9')
        disk_count = ch - '0';


    // Tower Init and start the game
    Canvas canvas(disk_count, game_starting_mode);
    set_terminal_mode();
    process(canvas);
    restore_terminal_mode();
}

void Game::process(Canvas& canvas) const {
    volatile int ch; // Use volatile to prevent compiler optimizations
    
    while (true) {
        if (_KBHIT()) {
            ch = __GET_CH();

            switch (ch) {

            // Validate
            case ENTER_VALUE:
                if (win(canvas))
                    return;
                break;

            // Move Left (a)
            case 'a':
                canvas.cursorMoveLeft();
                break;

            // Move Right (d)
            case 'd':
                canvas.cursorMoveRight();
                break;

            // Open help window (h)
            case 'h':
                help(canvas);
                break;

             // Quite the game (q)
            case 'q':
                if (exit(canvas))
                    return;
                break;

            // Move Down (s)
            case 's':
                canvas.diskMoveDown();
                break;

            // Move Up (w)
            case 'w':
                canvas.diskMoveUp();
                break;

            default:
                break;
            }
        }
        SLEEP(10);
    }
}


bool Game::exit(const Canvas& canvas) const {

    char ch;

    print_file_content(ESCAPE_WARNING);
    ch = waitForInput("ny");

    if(ch == 'n') {
        CLEAR_SCREEN();
        canvas.displayCanvas();
        return false;
    }
    else {
        CLEAR_SCREEN();
        std::cout << "Exiting.\n";
        return true;
    }
}

bool Game::win(const Canvas& canvas) const {

    if(canvas.isWinningPosition()) {
        CLEAR_SCREEN();
        std::cout << "You Win.\n";
        return true;
    }

    return false;
}

void Game::help(const Canvas& canvas) const {

    print_file_content(HELP_GUIDE);
    waitForInput("h");
    canvas.displayCanvas();
}