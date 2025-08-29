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

enum cursorPosition_t 
{ 
    cursorPositionMin       = 0, 
    cursorPositionLeft      = cursorPositionMin, 
    cursorPositionMiddle    = cursorPositionLeft + 1,
    cursorPositionRight     = cursorPositionMiddle + 1,
    cursorPositionMax       = cursorPositionRight,
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
    cursorPosition_t src;
    cursorPosition_t dst;
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
        const cursorPosition_t cursorPosition,
        const unsigned int ms = 0);

    void diskPut(
        const cursorPosition_t cursorPosition,
        const unsigned int ms = 0);

    // Solution
    void findNextMove();

    //Get functions
    unsigned int getDisksCount() const;
    unsigned int getUpperDiskSize() const;
    cursorPosition_t getCursorPosition() const;
    nextMove_t getNextMove() const;

    // Validation functions
    bool isWinningPosition() const;


private:

    // Variables
    unsigned int disksCount;
    unsigned int upperDiskSize;
    cursorPosition_t cursorPosition;
    std::vector<unsigned int> tower[3];
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

    // Set functions
    void setDisksCount(const unsigned int disks_count);
    void setCursorPosition(const cursorPosition_t cursor_position);
    void setDiskPosition(const diskPosition_t disk_position);
    void setUpperDiskSize(const unsigned int upper_disk_size);
    void setGameStartingMode(const gameStartingMode_t game_starting_mode);

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
    bool towerIsMonotone(std::vector<unsigned int> vec) const;
    void towersAreValid() const;
    bool canMove(cursorPosition_t src, cursorPosition_t dst) const;

    // Movement functions
    void cursorMoveToPos(
        const cursorPosition_t cursor_position,
        const unsigned int ms = 0);

};

#endif