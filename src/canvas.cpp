#include "canvas.h"

/*****************************************************************************/

void Canvas::CanvasInit(
    const unsigned int disks_count, 
    const gameStartingMode_t game_starting_mode) {

    setDisksCount(disks_count);
    setCursorPosition(positionLeft);
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

void Canvas::printNextMove() const {

    gotoxy(0, calcNextMoveY());
    std::cout <<
        "The next move is " << nextMove.src + 1 << " to " << nextMove.dst + 1 << std::endl;
}

/*****************************************************************************/

void Canvas::cursorMoveRight() {

    switch (cursorPosition) {
    case positionLeft:
        setCursorPosition(positionMiddle);
        break;
    case positionMiddle:
        setCursorPosition(positionRight);
        break;
    default:
        return;
    }

    gotoxy(0, calcUpperDiskY());
    printUpperDisk();

    gotoxy(0, calcCursorY());
    printCursor();
}

void Canvas::cursorMoveLeft() {

    switch (cursorPosition) {
    case positionRight:
        setCursorPosition(positionMiddle);
        break;
    case positionMiddle:
        setCursorPosition(positionLeft);
        break;
    default:
        return;
    }

    gotoxy(0, calcUpperDiskY());
    printUpperDisk();

    gotoxy(0, calcCursorY());
    printCursor();
}

void Canvas::diskMoveUp() {

    if (towers[cursorPosition].empty())
        return;

    if (diskPosition == diskPositionDown)
        setDiskPosition(diskPositionUp);
    else
        return;

    setUpperDiskSize(towers[cursorPosition].back());
    towers[cursorPosition].pop_back();

    gotoxy(0, calcUpperDiskY());
    printUpperDisk();

    gotoxy(0, CEIL_HIGH + disksCount - (towers[cursorPosition].size() + 1));
    printDiskByIndex(towers[cursorPosition].size());
}

void Canvas::diskMoveDown() {

    if (!upperDiskSize)
        return;

    if (!towers[cursorPosition].empty() && upperDiskSize > towers[cursorPosition].back())
        return;

    if (diskPosition == diskPositionUp)
        setDiskPosition(diskPositionDown);
    else
        return;

    towers[cursorPosition].push_back(upperDiskSize);
    setUpperDiskSize(0);

    gotoxy(0, calcUpperDiskY());
    printUpperDisk();

    gotoxy(0, CEIL_HIGH + disksCount - towers[cursorPosition].size());
    printDiskByIndex(towers[cursorPosition].size() - 1);
}

void Canvas::diskPick(const position_t cursor_position, const unsigned long ms) {
    cursorMoveToPos(cursor_position, ms);
    diskMoveUp();
    SLEEP(ms);
}

void Canvas::diskPut(const position_t cursor_position, const unsigned long ms) {
    cursorMoveToPos(cursor_position, ms);
    diskMoveDown();
    SLEEP(ms);
}

/*****************************************************************************/

void Canvas::determineSubProblem() {


    if (towers[0].size() == disksCount) {
        subproblemData = { positionLeft, positionMiddle, positionRight, disksCount };
        return;
    }

    if (towers[1].size() == disksCount) {
        subproblemData = { positionMiddle, positionLeft, positionRight, disksCount };
        return;
    }
    

    subproblemData_t data;
    memset(&data, 0, sizeof(data));
    bool flag = true;
    unsigned int count;
    unsigned int size;

    // Find src
    for (int i = 0; i < 3 && flag; ++i) {
        if (towers[i].size() && towers[i].back() == 1) {
            data.src = (position_t)i;
            flag = false;
        }
    }

    // Find disk count
    count = 1;
    flag = true;
    size = towers[data.src].size();
    while (flag && count < size) {
        if (count > size || towers[data.src][size - count] + 1 < towers[data.src][size - count - 1])
            flag = false;
        else
            ++count;
    }

    data.disksCount = count;

    // Find dst
    flag = true;
    for (int i = 0; i < 3 && flag; ++i) {
        if (towers[i].size() && towers[i].back() == count + 1) {
            data.dst = (position_t)i;
            flag = false;
        }
    }

    // Find aux
    flag = true;
    for (int i = 0; i < 3 && flag; ++i) {
        if ((position_t)i != data.src && (position_t)i != data.dst) {
            data.aux = (position_t)i;
            flag = false;
        }
    }

    subproblemData = data;
}

void Canvas::upperDiskReset() {
    // Find 1 pos (src)
    for (int i = 0; i < 3 && upperDiskSize; ++i) {
        position_t pos = (position_t)((cursorPosition + i) % 3);
        if (towers[pos].empty() || towers[pos].back() > upperDiskSize)
            diskPut(pos);
    }
}

/*****************************************************************************/

bool Canvas::isProblemSolved() const {

    if (upperDiskSize)
        return false;

    if (towers[0].size() || towers[1].size() || towers[2].size() != disksCount)
        return false;

    towersAreValid();

    return true;
}

//bool Canvas::isInitialStat() const {
//
//    if (upperDiskSize)
//        return false;
//
//    if (towers[0].size() != disksCount || towers[1].size() || towers[2].size())
//        return false;
//
//    towersAreValid();
//
//    return true;
//}

bool Canvas::canMove(position_t src, position_t dst) const {
    if (towers[src].empty()) return false;
    if (towers[dst].empty()) return true;
    return towers[src].back() < towers[dst].back();
}

/*****************************************************************************/

unsigned int Canvas::getDisksCount() const {
    return disksCount;
}

unsigned int Canvas::getUpperDiskSize() const {
    return upperDiskSize;
}

position_t Canvas::getCursorPosition() const {
    return cursorPosition;
}

nextMove_t Canvas::getNextMove() const {
    return nextMove;
}

subproblemData_t Canvas::getSubproblemData() const {
    return subproblemData;
}

/*****************************************************************************/

void Canvas::setDisksCount(const unsigned int disks_count) {
    disksCount = disks_count;
}

void Canvas::setCursorPosition(const position_t cursor_position) {
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

void Canvas::setNextMove(const nextMove_t next_move) {
    nextMove = next_move;
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

    const unsigned int leftDiskWidth = towers[0].size() > index ? towers[0][index] : 0;
    const unsigned int middleDiskWidth = towers[1].size() > index ? towers[1][index] : 0;
    const unsigned int rightDiskWidth  = towers[2].size() > index ? towers[2][index] : 0;
    
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

unsigned int Canvas::calcCursorY() const{
    return CEIL_HIGH + getDisksCount() + 1;
}

unsigned int Canvas::calcUpperDiskY() const {
    return UPPER_DISK_Y;
}

unsigned int  Canvas::calcNextMoveY() const {
    return CEIL_HIGH + FLOOR_HIGH + disksCount;
}

/*****************************************************************************/

void Canvas::towersClear() {
    towers[0].clear();
    towers[1].clear();
    towers[2].clear();
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
        towers[0].push_back(disksCount - i);
}

void Canvas::towersInitRandom() {
    srand(static_cast<unsigned int>(time(NULL)));

    for (size_t i = 0; i < disksCount; i++)
        towers[rand() % 3].push_back(disksCount - i);
}

/*****************************************************************************/

bool Canvas::towerIsMonotone(std::vector<unsigned int> tower) const {

    for (unsigned int i = 1; i < tower.size(); ++i) {
        if (tower[i - 1] <= tower[i])
            return false;
    }

    return true;
}

void Canvas::towersAreValid() const {

    assert(
        (cursorPosition >= positionMin && cursorPosition <= positionMax) &&
        "Cursor Position is invalid");

    assert(
        (disksCount >= MIN_DISKS_COUNT && disksCount <= MAX_DISKS_COUNT) && 
        "Disk count is invalid");

    std::vector<unsigned int> temp;

    assert(
        towerIsMonotone((std::vector<unsigned int>)towers[0]) &&
        "Left tower disks are not monotone\n");

    assert(
        towerIsMonotone((std::vector<unsigned int>)towers[1]) &&
        "Middle tower disks are not monotone\n");

    assert(
        towerIsMonotone((std::vector<unsigned int>)towers[2]) &&
        "Right tower disks are not monotone\n");

    temp.insert(temp.end(), towers[0].begin(), towers[0].end());
    temp.insert(temp.end(), towers[1].begin(), towers[1].end());
    temp.insert(temp.end(), towers[2].begin(), towers[2].end());
    
    if(upperDiskSize)
        temp.push_back(upperDiskSize);

    assert(temp.size() == disksCount && "Incorrect disk count\n");

    sort(temp.begin(), temp.end());
    for (unsigned int i = 0; i < temp.size(); ++i)
        assert(temp[i] == (i + 1) && "Incorrect tower disks\n");
}

void Canvas::cursorMoveToPos(const position_t cursor_position, const unsigned long ms) {
    switch (cursorPosition)
    {
    case positionLeft:
        switch (cursor_position)
        {
        case positionLeft:
            break;
        case positionMiddle:
            cursorMoveRight();
            break;
        case positionRight:
            cursorMoveRight();
            SLEEP(ms);
            cursorMoveRight();
            break;
        default:
            break;
        }
        break;

    case positionMiddle:
        switch (cursor_position)
        {
        case positionLeft:
            cursorMoveLeft();
            break;
        case positionMiddle:
            break;
        case positionRight:
            cursorMoveRight();
            break;
        default:
            break;
        }
        break;

    case positionRight:
        switch (cursor_position)
        {
        case positionLeft:
            cursorMoveLeft();
            SLEEP(ms);
            cursorMoveLeft();
            break;
        case positionMiddle:
            cursorMoveLeft();
            break;
        case positionRight:
            break;
        default:
            break;
        }
        break;

    default:
        break;
    }

    SLEEP(ms);
}
