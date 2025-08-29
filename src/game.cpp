#include "game.h"


void Game::start() {
    
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


    // Tower Init and start the process of game
    canvas.CanvasInit(disk_count, game_starting_mode);
    set_terminal_mode();
    process();
    restore_terminal_mode();
}

void Game::process() {
    char ch;
    
    while (true) {
        if (_KBHIT()) {
            ch = __GET_CH();

            switch (ch) {

            // Validate
            case ENTER_VALUE:
                if (win())
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
                help();
                break;

            // Make the next move (m)
            case 'm':
                makeNextMove();
                break;

            // Print the next move (n)
            case 'n':
                canvas.findNextMove();
                canvas.printNextMove();
                break;

             // Quite the game (q)
            case 'q':
                if (exit())
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

            // Solving (x)
            case 'x':
                solveRandom();
                break;

            default:
                break;
            }
        }
        SLEEP(10);
    }
}

void Game::help() const {

    print_file_content(HELP_GUIDE);
    waitForInput("h");
    canvas.displayCanvas();
}

bool Game::win() const {

    if (canvas.isWinningPosition()) {
        CLEAR_SCREEN();
        std::cout << "You Win.\n";
        return true;
    }

    return false;
}

bool Game::exit() const {

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


void Game::makeNextMove(unsigned int pause_time_ms) {
    
    canvas.findNextMove();
    canvas.printNextMove();
    
    cursorPosition_t cursor_position_curr = canvas.getCursorPosition();
    nextMove_t next_move_curr = canvas.getNextMove();
    unsigned int upper_disk_size = canvas.getUpperDiskSize();

    if(upper_disk_size && next_move_curr.src != cursor_position_curr)
        canvas.diskPut(cursor_position_curr, pause_time_ms);

    canvas.diskPick(next_move_curr.src, pause_time_ms);
    canvas.diskPut(next_move_curr.dst, pause_time_ms);
}

void Game::solveRandom() {

    char ch;
    bool flag = true;

    while (flag && !win()) {
        makeNextMove();

        if (_KBHIT()) {
            ch = __GET_CH();

            if (ch != 'q' || ch != 'z')
                flag = false;
        }
    }
}