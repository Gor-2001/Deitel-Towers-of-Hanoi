#include "canvas.h"

/*****************************************************************************/

Canvas::Canvas(
    const unsigned int disks_count, 
    const gameStartingMode_t game_starting_mode) {

    setDisksCount(disks_count);
    setCursorPosition(cursorPositionLeft);
    setDiskPosition(diskPositionDown);
    setUpperDiskSize(0);
    setGameStartingMode(game_starting_mode);
    towersInit();
    towersAreValid();
    displayCanvas();
}

/*****************************************************************************/

void Canvas::displayCanvas() const {
    
    printFullLines();
    printEmptyLines(UPPER_DISK_Y - 1);
    printUpperDisk();
    printEmptyLines(CEIL_HIGH - UPPER_DISK_Y - 1);

    for (int index = disksCount - 1; index >= 0; --index)
        printDiskByIndex(index);

    printTowersBase();
    printCursor();
    printEmptyLines();
    printFullLines();
}

/*****************************************************************************/

void Canvas::cursorMoveRight() {

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

void Canvas::cursorMoveLeft() {

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

void Canvas::diskMoveUp() {

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
    printDiskByIndex(tower[cursorPosition].size());
}

void Canvas::diskMoveDown() {

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
    printDiskByIndex(tower[cursorPosition].size() - 1);
}

/*****************************************************************************/

bool Canvas::isWinningPosition() const {

    if (upperDiskSize)
        return false;

    if (tower[0].size() || tower[1].size() || tower[2].size() != disksCount)
        return false;

    towersAreValid();

    return true;
}

/*****************************************************************************/

void Canvas::printString(const std::string string, const unsigned int count, const bool endl = false) const {

    for (unsigned int i = 0; i < count; ++i)
        std::cout << string;

    if (endl)
        std::cout << std::endl;
}

void Canvas::printEmptyLines(const unsigned int count) const {

    const unsigned int width = 6 * disksCount + 13;
    for (size_t i = 0; i < count; i++)
    {
        printString("#", 1);
        printString(" ", width - 2);
        printString("#", 1, true);
    } 
}

void Canvas::printFullLines(const unsigned int count) const {

    const unsigned int width = 6 * disksCount + 13;

    for (size_t i = 0; i < count; i++)
        printString("#", width, true);
}

void Canvas::printUpperDisk() const {

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


void Canvas::printDiskByIndex(const unsigned int index) const {

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

void Canvas::printTowersBase() const {

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

void Canvas::printCursor() const {

    printString("#  ", 1);
    printString(" ", cursorPosition * (disksCount * 2 + 3) + disksCount - 1);
    printString("#", 3);
    printString(" ", (2 - cursorPosition) * (disksCount * 2 + 3) + disksCount - 1);
    printString("  #", 1, true);

}

/*****************************************************************************/

void Canvas::setDisksCount(const unsigned int disks_count) {
    disksCount = disks_count;
}

void Canvas::setCursorPosition(const cursorPosition_t cursor_position) {
    cursorPosition = cursor_position;
}

void Canvas::setDiskPosition(const diskPosition_t disk_position) {
    diskPosition = disk_position;
}

void Canvas::setUpperDiskSize(const unsigned int upper_disk_size) {
    upperDiskSize = upper_disk_size;
}

void Canvas::setGameStartingMode(const gameStartingMode_t game_starting_mode) {
    gameStartingMode = game_starting_mode;
}

/*****************************************************************************/

unsigned int Canvas::getDisksCount() const{
    return disksCount;
}

unsigned int Canvas::getCursorY() const{
    return CEIL_HIGH + getDisksCount() + 1;
}

unsigned int Canvas::getUpperDiskY() {
    return UPPER_DISK_Y;
}

/*****************************************************************************/

void Canvas::towersClear() {
    tower[0].clear();
    tower[1].clear();
    tower[2].clear();
}


void Canvas::towersInit() {

    towersClear();

    switch (gameStartingMode)
    {
    case gameStartingModeBasic:
        towersInitBasic();
        break;
    case gameStartingModeRandom:
        towersInitRandom();
        break;
    default:
        assert((true) && "Game starting mode is invalid");
    }
}

void Canvas::towersInitBasic() {

    for (size_t i = 0; i < disksCount; i++)
        tower[0].push_back(disksCount - i);
}

void Canvas::towersInitRandom() {
    
    for (size_t i = 0; i < disksCount; i++)
        tower[rand() % 3].push_back(disksCount - i);
}

/*****************************************************************************/

bool Canvas::towerIsMonotone(std::vector<unsigned int> vec) const {

    for (unsigned int i = 1; i < vec.size(); ++i) {
        if (vec[i - 1] <= vec[i])
            return false;
    }

    return true;
}

void Canvas::towersAreValid() const {

    assert(
        (cursorPosition >= cursorPositionMin && cursorPosition <= cursorPositionMax) &&
        "Cursor Position is invalid");

    assert(
        (disksCount >= MIN_DISKS_COUNT && disksCount <= MAX_DISKS_COUNT) && 
        "Disk count is invalid");

    std::vector<unsigned int> temp;

    assert(
        towerIsMonotone((std::vector<unsigned int>)tower[0]) &&
        "Left tower disks are not monotone\n");

    assert(
        towerIsMonotone((std::vector<unsigned int>)tower[1]) &&
        "Middle tower disks are not monotone\n");

    assert(
        towerIsMonotone((std::vector<unsigned int>)tower[2]) &&
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