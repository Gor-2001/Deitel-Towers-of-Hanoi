#ifndef TOWER_H
#define TOWER_H

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

#define MAX_DISKS_COUNT 20
enum cursorPosition_t { left, middle, right };
class Towers
{
public:

    Towers(unsigned int disks_count = 3);
    void displayNum() const;
    void displayPic() const;

private:

    unsigned int disksCount;
    std::vector<unsigned int> towerLeft;
    std::vector<unsigned int> towerMiddle;
    std::vector<unsigned int> towerRight;
    cursorPosition_t cursorPosition;

    void printString(std::string string, const unsigned int count, bool endl) const;
    void printDisk(const unsigned int diskWidth) const;
    void printCeil(const unsigned int height, const unsigned int width) const;
    void printLine(const unsigned int width, const unsigned int level) const;
    void printCursor() const;
    void printFloor(const unsigned int height, const unsigned int width) const;
    void setDisksCount(unsigned int disks_count);
    void towersClear();
    void towerFillBasic();
    void displayTowerNum(std::vector<unsigned int>& tower, std::string& str) const;
    bool vectorIsMonotone(std::vector<unsigned int> vec) const;
    void towersIsValid() const;

};

#endif