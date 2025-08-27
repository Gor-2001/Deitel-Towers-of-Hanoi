#include "towers.h"

void gotoxy(const int x, const int y) {

    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/*****************************************************************************/

Towers::Towers(
    const unsigned int disks_count, 
    const gameStartingMode_t gameStartingMode) {

    setDisksCount(disks_count);
    setCursorPosition(cursorPositionLeft);
    setDiskPosition(diskPositionDown);
    setUpperDiskSize(0);
    setGameStartingMode(gameStartingMode);
    towerInit();
    towersIsValid();
    displayTowers();
}

/*****************************************************************************/

void Towers::displayTowers() const {
    
    printFullLines();
    printEmptyLines(UPPER_DISK_Y - 1);
    printUpperDisk();
    printEmptyLines(CEIL_HIGH - UPPER_DISK_Y - 1);

    for (int index = disksCount - 1; index >= 0; --index)
        printDisksByIndex(index);

    printTowersBases();
    printCursor();
    printEmptyLines();
    printFullLines();
}

/*****************************************************************************/

void Towers::cursorMoveRight() {

    switch (cursorPosition) {
    case cursorPositionLeft:
        setCursorPosition(cursorPositionMiddle);
        break;
    case cursorPositionMiddle:
        setCursorPosition(cursorPositionRight);
        break;
    default:
        return;
    }

    gotoxy(0, getUpperDiskY());
    printUpperDisk();

    gotoxy(0, getCursorY());
    printCursor();
}

void Towers::cursorMoveLeft() {

    switch (cursorPosition) {
    case cursorPositionRight:
        setCursorPosition(cursorPositionMiddle);
        break;
    case cursorPositionMiddle:
        setCursorPosition(cursorPositionLeft);
        break;
    default:
        return;
    }

    gotoxy(0, getUpperDiskY());
    printUpperDisk();

    gotoxy(0, getCursorY());
    printCursor();
}

void Towers::diskMoveUp() {

    if (tower[cursorPosition].empty())
        return;

    if (diskPosition == diskPositionDown)
        setDiskPosition(diskPositionUp);
    else
        return;

    setUpperDiskSize(tower[cursorPosition].back());
    tower[cursorPosition].pop_back();

    gotoxy(0, getUpperDiskY());
    printUpperDisk();

    gotoxy(0, CEIL_HIGH + disksCount - (tower[cursorPosition].size() + 1));
    printDisksByIndex(tower[cursorPosition].size());
}

void Towers::diskMoveDown() {

    if (!upperDiskSize)
        return;

    if (!tower[cursorPosition].empty() && upperDiskSize > tower[cursorPosition].back())
        return;

    if (diskPosition == diskPositionUp)
        setDiskPosition(diskPositionDown);
    else
        return;

    tower[cursorPosition].push_back(upperDiskSize);
    setUpperDiskSize(0);

    gotoxy(0, getUpperDiskY());
    printUpperDisk();

    gotoxy(0, CEIL_HIGH + disksCount - tower[cursorPosition].size());
    printDisksByIndex(tower[cursorPosition].size() - 1);
}

/*****************************************************************************/

bool Towers::isWinningPosition() const {

    if (upperDiskSize)
        return false;

    if (tower[0].size() || tower[1].size() || tower[2].size() != disksCount)
        return false;

    towersIsValid();

    return true;
}

/*****************************************************************************/

void Towers::printString(const std::string string, const unsigned int count, const bool endl = false) const {

    for (unsigned int i = 0; i < count; ++i)
        std::cout << string;

    if (endl)
        std::cout << std::endl;
}

void Towers::printEmptyLines(const unsigned int count) const {

    const unsigned int width = 6 * disksCount + 13;
    for (size_t i = 0; i < count; i++)
    {
        printString("#", 1);
        printString(" ", width - 2);
        printString("#", 1, true);
    } 
}

void Towers::printFullLines(const unsigned int count) const {

    const unsigned int width = 6 * disksCount + 13;

    for (size_t i = 0; i < count; i++)
        printString("#", width, true);
}

void Towers::printUpperDisk() const {

    if (!upperDiskSize) {
        printEmptyLines();
        return;
    }

    // The wall 
    printString("#  ", 1);

    // Disk
    printString(" ", (2 * disksCount + 3) * cursorPosition + disksCount - upperDiskSize);
    printString("*", upperDiskSize);
    printString(" ", 1);
    printString("*", upperDiskSize);
    printString(" ", (2 * disksCount + 3) * (2 - cursorPosition) + disksCount - upperDiskSize);

    // The wall 
    printString("  #", 1, true);
}


void Towers::printDisksByIndex(const unsigned int index) const {

    const unsigned int leftDiskWidth = tower[0].size() > index ? tower[0][index] : 0;
    const unsigned int middleDiskWidth = tower[1].size() > index ? tower[1][index] : 0;
    const unsigned int rightDiskWidth  = tower[2].size() > index ? tower[2][index] : 0;
    
    // The wall 
    printString("#  ", 1);

    // The left disk
    printString(" ", disksCount - leftDiskWidth);
    printString("*", leftDiskWidth);
    printString("#", 1);
    printString("*", leftDiskWidth);
    printString(" ", disksCount - leftDiskWidth);

    // Space 
    printString(" ", 2);

    // The Middle disk
    printString(" ", disksCount - middleDiskWidth);
    printString("*", middleDiskWidth);
    printString("#", 1);
    printString("*", middleDiskWidth);
    printString(" ", disksCount - middleDiskWidth);

    // Space 
    printString(" ", 2);

    // The Right disk
    printString(" ", disksCount - rightDiskWidth);
    printString("*", rightDiskWidth);
    printString("#", 1);
    printString("*", rightDiskWidth);
    printString(" ", disksCount - rightDiskWidth);


    // The wall 
    printString("  #", 1, true);
}

void Towers::printTowersBases() const {

    // The wall 
    printString("#  ", 1);

    // Left Part
    printString("#", 2 * disksCount + 1);
    printString(" ", 2);

    // Middle
    printString("#", 2 * disksCount + 1);
    printString(" ", 2);

    // Right
    printString("#", 2 * disksCount + 1);
    printString(" ", 2);

    // The wall 
    printString("#", 1, true);
}

void Towers::printCursor() const {

    printString("#  ", 1);
    printString(" ", cursorPosition * (disksCount * 2 + 3) + disksCount - 1);
    printString("#", 3);
    printString(" ", (2 - cursorPosition) * (disksCount * 2 + 3) + disksCount - 1);
    printString("  #", 1, true);

}

/*****************************************************************************/

void Towers::setDisksCount(const unsigned int disks_count) {
    disksCount = disks_count;
}

void Towers::setCursorPosition(const cursorPosition_t cursor_position) {
    cursorPosition = cursor_position;
}

void Towers::setDiskPosition(const diskPosition_t disk_position) {
    diskPosition = disk_position;
}

void Towers::setUpperDiskSize(const unsigned int upper_disk_size) {
    upperDiskSize = upper_disk_size;
}

void Towers::setGameStartingMode(const gameStartingMode_t game_starting_mode) {
    gameStartingMode = game_starting_mode;
}

/*****************************************************************************/

unsigned int Towers::getDisksCount() const{
    return disksCount;
}

unsigned int Towers::getCursorY() const{ 
    return CEIL_HIGH + getDisksCount() + 1;
}

unsigned int Towers::getUpperDiskY() {
    return UPPER_DISK_Y;
}

/*****************************************************************************/

void Towers::towersClear() {
    tower[0].clear();
    tower[1].clear();
    tower[2].clear();
}


void Towers::towerInit() {

    towersClear();

    switch (gameStartingMode)
    {
    case gameStartingModeBasic:
        towerInitBasic();
        break;
    case gameStartingModeRandom:
        towerInitRandom();
        break;
    default:
        assert((true) && "Game starting mode is invalid");
    }
}

void Towers::towerInitBasic() {

    for (size_t i = 0; i < disksCount; i++)
        tower[0].push_back(disksCount - i);
}

void Towers::towerInitRandom() {
    
    for (size_t i = 0; i < disksCount; i++)
        tower[rand() % 3].push_back(disksCount - i);
}

/*****************************************************************************/

bool Towers::vectorIsMonotone(std::vector<unsigned int> vec) const {

    for (unsigned int i = 1; i < vec.size(); ++i) {
        if (vec[i - 1] <= vec[i])
            return false;
    }

    return true;
}

void Towers::towersIsValid() const {

    assert(
        (cursorPosition >= cursorPositionMin && cursorPosition <= cursorPositionMax) &&
        "Cursor Position is invalid");

    assert(
        (disksCount >= MIN_DISKS_COUNT && disksCount <= MAX_DISKS_COUNT) && 
        "Disk count is invalid");

    std::vector<unsigned int> temp;

    assert(
        vectorIsMonotone((std::vector<unsigned int>)tower[0]) &&
        "Left tower disks are not monotone\n");

    assert(
        vectorIsMonotone((std::vector<unsigned int>)tower[1]) &&
        "Middle tower disks are not monotone\n");

    assert(
        vectorIsMonotone((std::vector<unsigned int>)tower[2]) &&
        "Right tower disks are not monotone\n");

    temp.insert(temp.end(), tower[0].begin(), tower[0].end());
    temp.insert(temp.end(), tower[1].begin(), tower[1].end());
    temp.insert(temp.end(), tower[2].begin(), tower[2].end());
    
    if(upperDiskSize)
        temp.push_back(upperDiskSize);

    assert(temp.size() == disksCount && "Incorrect disk count\n");

    sort(temp.begin(), temp.end());
    for (unsigned int i = 0; i < temp.size(); ++i)
        assert(temp[i] == (i + 1) && "Incorrect tower disks\n");
}