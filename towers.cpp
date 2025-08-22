#include "towers.h"

Towers::Towers(unsigned int disks_count)
{
    setDisksCount(disks_count);
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
    const unsigned int height = disksCount + 12;
    const unsigned int width = 6 * disksCount + 13;

    printCeil(height, width);

    for (size_t i = disksCount; i > 0; --i)
        printLine(width, i);

    printFloor(height, width);

}

void Towers::printString(std::string string, const unsigned int count, bool endl = false) const {
    for (unsigned int i = 0; i < count; ++i)
        std::cout << string;

    if (endl)
        std::cout << std::endl;
}

void Towers::printDisk(const unsigned int diskWidth) const {

    printString(" ", disksCount - diskWidth);
    printString("*", diskWidth);
    printString("#", 1);
    printString("*", diskWidth);
    printString(" ", disksCount - diskWidth);
    
}

void Towers::printCeil(const unsigned int height, const unsigned int width) const {
    printString("#", width, true);
    
    for (size_t i = 0; i < 8; i++)
    {
        printString("#", 1);
        printString(" ", width - 2);
        printString("#", 1, true);
    }  
}

void Towers::printLine(const unsigned int width, const unsigned int level) const {
    printString("#  ", 1);
    towerLeft.size() >= level ? printDisk(towerLeft[level - 1]) : printDisk(0);
    printString(" ", 2);
    towerMiddle.size() >= level ? printDisk(towerMiddle[level - 1]) : printDisk(0);
    printString(" ", 2);
    towerRight.size() >= level ? printDisk(towerRight[level - 1]) : printDisk(0);
    printString("  #", 1, true);
}

void Towers::printFloor(const unsigned int height, const unsigned int width) const {

    printString("#  ", 1);
    printString("#", 2 * disksCount + 1);
    printString(" ", 2);
    printString("#", 2 * disksCount + 1);
    printString(" ", 2);
    printString("#", 2 * disksCount + 1);
    printString("  #", 1, true);

    printString("#", 1);
    printString(" ", width - 2);
    printString("#", 1, true);

    printString("#", width, true);
}

void Towers::setDisksCount(unsigned int disks_count) {
    disksCount = disks_count;
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
