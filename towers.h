#ifndef TOWER_H
#define TOWER_H

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

#define MAX_DISKS_COUNT 20

#define CEIL_HIGH 9
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

class Towers
{
public:

    // Constructor
    Towers::Towers(const unsigned int disks_count = 10, const cursorPosition_t cursor_position = cursorPositionLeft);
    
    // Input and output functions
    void displayNum() const;
    void displayPic() const;

    void printDisks() const;
    void printFloor() const;
    void printCursor() const;

    // Movement functions
    void cursorMoveRight();
    void cursorMoveLeft();

    // Get function
    unsigned int getDisksCount();
    unsigned int getCursorY();

private:

    // Variables
    unsigned int disksCount;
    std::vector<unsigned int> towerLeft;
    std::vector<unsigned int> towerMiddle;
    std::vector<unsigned int> towerRight;
    cursorPosition_t cursorPosition;

    // Input and output functions
    void displayTowerNum(std::vector<unsigned int>& tower, std::string& str) const;

    void printString(std::string string, const unsigned int count, bool endl) const;
    void printCeil() const;
    void printDisk(const unsigned int diskWidth) const;

    // Set functions
    void setDisksCount(const unsigned int disks_count);
    void setCursorPosition(const cursorPosition_t cursor_position);

    void towersClear();
    void towerFillBasic();

    // Validation functions
    bool vectorIsMonotone(std::vector<unsigned int> vec) const;
    void towersIsValid() const;

};

#endif