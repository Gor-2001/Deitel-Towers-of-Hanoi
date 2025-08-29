#ifndef TOWER_H
#define TOWER_H

#include <vector>
#include <cassert>
#include <algorithm>
#include "cross_platform_conio.h"

#define MAX_DISKS_COUNT 9
#define MIN_DISKS_COUNT 1

#define CEIL_HIGH 9
#define UPPER_DISK_Y 4
#define FLOOR_HIGH 4

enum position_t 
{ 
    positionMin       = 0, 
    positionLeft      = positionMin, 
    positionMiddle    = positionLeft + 1,
    positionRight     = positionMiddle + 1,
    positionMax       = positionRight,
};

enum diskPosition_t
{
    diskPositionMin     = 0,
    diskPositionDown    = diskPositionMin,
    diskPositionUp      = diskPositionDown + 1,
    diskPositionMax     = diskPositionUp,
};

enum gameStartingMode_t
{
    gameStartingModeMin = 0,
    gameStartingModeBasic = gameStartingModeMin,
    gameStartingModeRandom = gameStartingModeBasic + 1,
    gameStartingModeMax = gameStartingModeBasic,
};

struct nextMove_t
{
    position_t src;
    position_t dst;
};

class Canvas
{
public:

    // Initializer
    void CanvasInit(
        const unsigned int disks_count = 10,
        const gameStartingMode_t game_starting_mode = gameStartingModeBasic
    );

    // Input and output functions
    void displayCanvas() const;
    void printNextMove() const;

    // Movement functions
    void cursorMoveRight();
    void cursorMoveLeft();

    void diskMoveUp();
    void diskMoveDown();

    void diskPick(
        const position_t cursorPosition,
        const unsigned long ms = 0);

    void diskPut(
        const position_t cursorPosition,
        const unsigned long ms = 0);

    // Solution
    void findNextMove();

    //Get functions
    unsigned int getDisksCount() const;
    unsigned int getUpperDiskSize() const;
    position_t getCursorPosition() const;
    nextMove_t getNextMove() const;
    std::vector<unsigned int> getTowers() const;

    // Set functions
    void setDisksCount(const unsigned int disks_count);
    void setCursorPosition(const position_t cursor_position);
    void setDiskPosition(const diskPosition_t disk_position);
    void setUpperDiskSize(const unsigned int upper_disk_size);
    void setGameStartingMode(const gameStartingMode_t game_starting_mode);
    void setNextMove(const nextMove_t next_move);

    // Validation functions
    bool isWinningPosition() const;
    bool canMove(position_t src, position_t dst) const;
    bool isInitialStat() const;


private:

    // Variables
    unsigned int disksCount;
    unsigned int upperDiskSize;
    position_t cursorPosition;
    std::vector<unsigned int> towers[3];
    diskPosition_t diskPosition;
    gameStartingMode_t gameStartingMode;
    nextMove_t nextMove;

    // Input and output functions
    void printString(std::string string, const unsigned int count, bool endl) const;
    void printEmptyLines(const unsigned int count = 1) const;
    void printFullLines(const unsigned int count = 1) const;

    void printUpperDisk() const;
    void printDiskByIndex(const unsigned int index) const;

    void printTowersBase() const;
    void printCursor() const;

    // Calculation functions
    unsigned int getCursorY() const;
    unsigned int getUpperDiskY() const;
    unsigned int getNextMoveY() const;

    // Towers filling and cleaning functions
    void towersClear();
    void towersInit();
    void towersInitBasic();
    void towersInitRandom();

    // Validation functions
    bool towerIsMonotone(std::vector<unsigned int> tower) const;
    void towersAreValid() const;

    // Movement functions
    void cursorMoveToPos(
        const position_t cursor_position,
        const unsigned long ms = 0);

};

#endif