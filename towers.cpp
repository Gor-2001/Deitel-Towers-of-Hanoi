#include "towers.h"

Towers::Towers(const unsigned int disks_count, const cursorPosition_t cursor_position)
{
    setDisksCount(disks_count);
    setCursorPosition(cursor_position);
    towerFillBasic();
    towersIsValid();
}

void Towers::displayNum() const {
    displayTowerNum((std::vector<unsigned int>)towerLeft, (std::string)"The Left Tower");
    displayTowerNum((std::vector<unsigned int>)towerMiddle, (std::string)"The Middle Tower");
    displayTowerNum((std::vector<unsigned int>)towerRight, (std::string)"The Right Tower");

    std::cout << std::endl;
}

void Towers::displayPic() const {

    // CEIL_HIGH lines
    printCeil();

    // disksCount lines
    printDisks();

    // FLOOR_HIGH lines
    printFloor();

}

void Towers::printString(std::string string, const unsigned int count, bool endl = false) const {

    for (unsigned int i = 0; i < count; ++i)
        std::cout << string;

    if (endl)
        std::cout << std::endl;
}


void Towers::printCeil() const {

    const unsigned int width = 6 * disksCount + 13;

    printString("#", width, true);
    for (size_t i = 0; i < CEIL_HIGH - 1; i++)
    {
        printString("#", 1);
        printString(" ", width - 2);
        printString("#", 1, true);
    }  
}

void Towers::printDisk(const unsigned int diskWidth) const {

    printString(" ", disksCount - diskWidth);
    printString("*", diskWidth);
    printString("#", 1);
    printString("*", diskWidth);
    printString(" ", disksCount - diskWidth);

}

void Towers::printDisks() const {

    for (size_t level = disksCount; level > 0; --level)
    {
        printString("#  ", 1);
        towerLeft.size() >= level ? printDisk(towerLeft[level - 1]) : printDisk(0);
        printString(" ", 2);
        towerMiddle.size() >= level ? printDisk(towerMiddle[level - 1]) : printDisk(0);
        printString(" ", 2);
        towerRight.size() >= level ? printDisk(towerRight[level - 1]) : printDisk(0);
        printString("  #", 1, true);
    }

}

void Towers::printCursor() const {

    printString("#  ", 1);
    printString(" ", cursorPosition * (disksCount * 2 + 3) + disksCount - 1);
    printString("#", 3);
    printString(" ", (2 - cursorPosition) * (disksCount * 2 + 3) + disksCount - 1);
    printString("  #", 1, true);

}
void Towers::printFloor() const {

    const unsigned int width = 6 * disksCount + 13;

    printString("#  ", 1);
    printString("#", 2 * disksCount + 1);
    printString(" ", 2);
    printString("#", 2 * disksCount + 1);
    printString(" ", 2);
    printString("#", 2 * disksCount + 1);
    printString("  #", 1, true);

    printCursor();

    printString("#", 1);
    printString(" ", width - 2);
    printString("#", 1, true);

    printString("#", width, true);
}

void Towers::setDisksCount(const unsigned int disks_count) {
    disksCount = disks_count;
}

void Towers::setCursorPosition(const cursorPosition_t cursor_position) {
    cursorPosition = cursor_position;
}

unsigned int Towers::getDisksCount(){
    return disksCount;
}

unsigned int Towers::getCursorY()
{ 
    return 
        CEIL_HIGH + getDisksCount() + 1;
}

void Towers::towersClear() {
    towerLeft.clear();
    towerMiddle.clear();
    towerRight.clear();
}

void Towers::towerFillBasic() {
    towersClear();

    for (size_t i = 0; i < disksCount; i++)
        towerLeft.push_back(disksCount - i);
}

void Towers::displayTowerNum(std::vector<unsigned int>& tower, std::string& str) const {

    std::cout << str << std::endl;

    if (!tower.size())
        std::cout << "Is empty";

    for (unsigned int diskSize : tower)
        std::cout << diskSize << " ";
    std::cout << std::endl;
}

bool Towers::vectorIsMonotone(std::vector<unsigned int> vec) const {
    for (unsigned int i = 1; i < vec.size(); ++i) {
        if (vec[i - 1] <= vec[i])
            return false;
    }

    return true;
}

void Towers::towersIsValid() const {

    assert((cursorPosition >= cursorPositionMin && cursorPosition <= cursorPositionMax) && "Cursor Position is invalid");
    assert((disksCount > 0 && disksCount <= MAX_DISKS_COUNT) && "Disk count is invalid");

    std::vector<unsigned int> temp;

    assert(vectorIsMonotone((std::vector<unsigned int>)towerLeft) && "Left tower disks are not monotone\n");
    assert(vectorIsMonotone((std::vector<unsigned int>)towerMiddle) && "Middle tower disks are not monotone\n");
    assert(vectorIsMonotone((std::vector<unsigned int>)towerRight) && "Right tower disks are not monotone\n");

    temp.insert(temp.end(), towerLeft.begin(), towerLeft.end());
    temp.insert(temp.end(), towerMiddle.begin(), towerMiddle.end());
    temp.insert(temp.end(), towerRight.begin(), towerRight.end());

    assert(temp.size() == disksCount && "Incorrect disk count\n");

    sort(temp.begin(), temp.end());
    for (unsigned int i = 0; i < temp.size(); ++i)
        assert(temp[i] == (i + 1) && "Incorrect tower disks\n");
}

void Towers::cursorMoveRight()
{
    switch (cursorPosition){
    case cursorPositionLeft:
        setCursorPosition(cursorPositionMiddle);
        break;
    case cursorPositionMiddle:
        setCursorPosition(cursorPositionRight);
        break;
    default:
        break;
    }
}

void Towers::cursorMoveLeft()
{
    switch (cursorPosition) {
    case cursorPositionRight:
        setCursorPosition(cursorPositionMiddle);
        break;
    case cursorPositionMiddle:
        setCursorPosition(cursorPositionLeft);
        break;
    default:
        break;
    }
}
