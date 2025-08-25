#ifndef TOWER_H
#define TOWER_H

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <windows.h>

#define MAX_DISKS_COUNT 20

#define CEIL_HIGH 9
#define FLOOR_HIGH 4

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

class Towers
{
public:

    // Constructor
    Towers::Towers(const unsigned int disks_count = 10);
    
    // Input and output functions
    void displayNum() const;
    void displayPic() const;

    // Movement functions
    void cursorMoveRight();
    void cursorMoveLeft();

    void diskMoveUp();
    void diskMoveDown();

    // Validation functions
    bool winningPosition() const;

private:

    // Variables
    unsigned int disksCount;
    unsigned int upperDiskSize;
    std::vector<unsigned int> tower[3];
    cursorPosition_t cursorPosition;
    diskPosition_t diskPosition;

    // Input and output functions
    void displayTowerNum(std::vector<unsigned int>& tower, std::string& str) const;

    void printString(std::string string, const unsigned int count, bool endl) const;
    void printEmptyString(const unsigned int count) const;

    void printCeil() const;

    void printDisks() const;
    void printDisk(const unsigned int diskWidth) const;

    void printUpperDisk() const;
    void printLowerDisk() const;

    void printCursor() const;
    void printFloor() const;

    // Set functions
    void setDisksCount(const unsigned int disks_count);
    void setCursorPosition(const cursorPosition_t cursor_position);
    void setDiskPosition(const diskPosition_t disk_position);
    void setUpperDiskSize(const unsigned int upper_disk_size);

    // Get functions
    unsigned int getDisksCount();
    unsigned int getCursorY();
    unsigned int getUpperDiskY();
    unsigned int getLowerDiskY();

    // Value manipulation functions
    void towersClear();
    void towerFillBasic();

    // Validation functions
    bool vectorIsMonotone(std::vector<unsigned int> vec) const;
    void towersIsValid() const;

};

#endif