#ifndef CANVAS_H
#define CANVAS_H

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

struct subproblemData_t
{
    position_t src;
    position_t aux;
    position_t dst;
    unsigned int disksCount;
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
    void determineSubProblem();
    void upperDiskReset();

    // Validation functions
    bool isProblemSolved() const;
    bool canMove(position_t src, position_t dst) const;

    //Get functions
    unsigned int        getDisksCount() const;
    unsigned int        getUpperDiskSize() const;
    position_t          getCursorPosition() const;
    nextMove_t          getNextMove() const;
    subproblemData_t    getSubproblemData() const;

    // Set functions
    void setDisksCount(const unsigned int disks_count);
    void setCursorPosition(const position_t cursor_position);
    void setDiskPosition(const diskPosition_t disk_position);
    void setUpperDiskSize(const unsigned int upper_disk_size);
    void setGameStartingMode(const gameStartingMode_t game_starting_mode);
    void setNextMove(const nextMove_t next_move);

private:

    // Variables
    // Towers
    unsigned int disksCount;
    std::vector<unsigned int> towers[3];
    
    // Upper Disk
    unsigned int upperDiskSize;
    diskPosition_t diskPosition;
    
    //Stat
    position_t cursorPosition;
    gameStartingMode_t gameStartingMode;

    // Solution
    nextMove_t nextMove;
    subproblemData_t subproblemData;

    // Input and output functions
    void printString(std::string string, const unsigned int count, bool endl) const;
    void printEmptyLines(const unsigned int count = 1) const;
    void printFullLines(const unsigned int count = 1) const;

    void printUpperDisk() const;
    void printDiskByIndex(const unsigned int index) const;

    void printTowersBase() const;
    void printCursor() const;

    // Calculation functions
    unsigned int calcCursorY() const;
    unsigned int calcUpperDiskY() const;
    unsigned int calcNextMoveY() const;

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

#endif // CANVAS_H