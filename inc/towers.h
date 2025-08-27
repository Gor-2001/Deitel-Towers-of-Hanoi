#ifndef TOWER_H
#define TOWER_H

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <windows.h>

#define MAX_DISKS_COUNT 9
#define MIN_DISKS_COUNT 1

#define CEIL_HIGH 9
#define UPPER_DISK_Y 4

void gotoxy(int x, int y);

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


class Towers
{
public:

    // Constructor
    Towers::Towers(
        const unsigned int disks_count = 10,
        const gameStartingMode_t gameStartingMode = gameStartingModeBasic
    );

    // Input and output functions
    void displayTowers() const;

    // Movement functions
    void cursorMoveRight();
    void cursorMoveLeft();

    void diskMoveUp();
    void diskMoveDown();

    // Validation functions
    bool isWinningPosition() const;


private:

    // Variables
    unsigned int disksCount;
    unsigned int upperDiskSize;
    std::vector<unsigned int> tower[3];
    cursorPosition_t cursorPosition;
    diskPosition_t diskPosition;
    gameStartingMode_t gameStartingMode;

    // Input and output functions
    void printString(std::string string, const unsigned int count, bool endl) const;
    void printEmptyLines(const unsigned int count = 1) const;
    void printFullLines(const unsigned int count = 1) const;

    void printUpperDisk() const;
    void printDisksByIndex(const unsigned int index) const;

    void printTowersBases() const;
    void printCursor() const;

    // Set functions
    void setDisksCount(const unsigned int disks_count);
    void setCursorPosition(const cursorPosition_t cursor_position);
    void setDiskPosition(const diskPosition_t disk_position);
    void setUpperDiskSize(const unsigned int upper_disk_size);
    void setGameStartingMode(const gameStartingMode_t game_starting_mode);

    // Get functions
    unsigned int getDisksCount() const;
    unsigned int getCursorY() const;
    unsigned int getUpperDiskY();

    // Towers filling and cleaning functions
    void towersClear();
    void towerInit();
    void towerInitBasic();
    void towerInitRandom();

    // Validation functions
    bool vectorIsMonotone(std::vector<unsigned int> vec) const;
    void towersIsValid() const;

};

#endif