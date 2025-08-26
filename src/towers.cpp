#include "towers.h"

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

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

void Towers::displayTowers() const {

    // CEIL_HIGH lines
    printCeil();

    // disksCount lines
    printLevels();

    // FLOOR_HIGH lines
    printFloor();
}

void Towers::printString(std::string string, const unsigned int count, bool endl = false) const {

    for (unsigned int i = 0; i < count; ++i)
        std::cout << string;

    if (endl)
        std::cout << std::endl;
}

void Towers::printEmptyLines(const unsigned int count = 1) const {

    const unsigned int width = 6 * disksCount + 13;
    for (size_t i = 0; i < count; i++)
    {
        printString("#", 1);
        printString(" ", width - 2);
        printString("#", 1, true);
    } 
}

void Towers::printFullLines(const unsigned int count = 1) const {

    const unsigned int width = 6 * disksCount + 13;

    for (size_t i = 0; i < count; i++)
        printString("#", width, true);
}

void Towers::printCeil() const {

    printFullLines();
    printEmptyLines(UPPER_DISK_Y - 1);
    printUpperDisk();
    printEmptyLines(CEIL_HIGH - UPPER_DISK_Y - 1);
}

void Towers::printLevelByValues(
    const unsigned int leftDiskWidth, 
    const unsigned int middleDiskWidth, 
    const unsigned int rightDiskWidth, 
    const char diskDelimiter,
    const char diskCharacter
) const {

    // The wall 
    printString("#  ", 1);

    // The left disk
    printString(" ", disksCount - leftDiskWidth);
    printString(std::string(1, diskCharacter), leftDiskWidth);
    printString(std::string(1, diskDelimiter), 1);
    printString(std::string(1, diskCharacter), leftDiskWidth);
    printString(" ", disksCount - leftDiskWidth);

    // Space 
    printString(" ", 2);

    // The Middle disk
    printString(" ", disksCount - middleDiskWidth);
    printString(std::string(1, diskCharacter), middleDiskWidth);
    printString(std::string(1, diskDelimiter), 1);
    printString(std::string(1, diskCharacter), middleDiskWidth);
    printString(" ", disksCount - middleDiskWidth);

    // Space 
    printString(" ", 2);

    // The Right disk
    printString(" ", disksCount - rightDiskWidth);
    printString(std::string(1, diskCharacter), rightDiskWidth);
    printString(std::string(1, diskDelimiter), 1);
    printString(std::string(1, diskCharacter), rightDiskWidth);
    printString(" ", disksCount - rightDiskWidth);


    // The wall 
    printString("  #", 1, true);
}

void Towers::printLevels() const {

    for (int index = disksCount - 1; index >= 0; --index)
        printLevelByIndex(index);
}

void Towers::printUpperDisk() const {

    if(!upperDiskSize) {
        printEmptyLines();
        return;
    }
    
    switch (cursorPosition) {
    case cursorPositionLeft:
        printLevelByValues(upperDiskSize, 0, 0, ' ');
        break;
    case cursorPositionMiddle:
        printLevelByValues(0, upperDiskSize, 0, ' ');
        break;
    case cursorPositionRight:
        printLevelByValues(0, 0, upperDiskSize, ' ');
        break;
    default:
        assert((true) && "Cursor position is invalid");
    }
}

void Towers::printLevelByIndex(
    const unsigned int index,
    const char diskDelimiter,
    const char diskCharacter) const {

    const unsigned int leftDiskWidth = tower[0].size() > index ? tower[0][index] : 0;
    const unsigned int middleDiskWidth = tower[1].size() > index ? tower[1][index] : 0;
    const unsigned int rightDiskWidth  = tower[2].size() > index ? tower[2][index] : 0;
    
    printLevelByValues(leftDiskWidth, middleDiskWidth, rightDiskWidth, diskDelimiter, diskCharacter);
}

void Towers::printCursor() const {

    printString("#  ", 1);
    printString(" ", cursorPosition * (disksCount * 2 + 3) + disksCount - 1);
    printString("#", 3);
    printString(" ", (2 - cursorPosition) * (disksCount * 2 + 3) + disksCount - 1);
    printString("  #", 1, true);

}

void Towers::printTowersBases() const {
    printLevelByValues(disksCount, disksCount, disksCount, '#', '#');
}

void Towers::printFloor() const {

    printTowersBases();
    printCursor();
    printEmptyLines();
    printFullLines();
}

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

unsigned int Towers::getDisksCount() const{
    return disksCount;
}

unsigned int Towers::getCursorY() const{ 
    return 
        CEIL_HIGH + getDisksCount() + 1;
}

unsigned int Towers::getUpperDiskY() {
    return UPPER_DISK_Y;
}

unsigned int Towers::getLowerDiskY() {
    return 
        CEIL_HIGH + disksCount - tower[cursorPosition].size();
}

void Towers::towersClear() {
    tower[0].clear();
    tower[1].clear();
    tower[2].clear();
}


void Towers::towerInit() {

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
    towersClear();

    for (size_t i = 0; i < disksCount; i++)
        tower[0].push_back(disksCount - i);
}

void Towers::towerInitRandom() {
    towersClear();
    
    for (size_t i = 0; i < disksCount; i++)
        tower[rand() % 3].push_back(disksCount - i);
}

bool Towers::isWinningPosition() const {
    if(upperDiskSize)
        return false;

    if(tower[0].size() || tower[1].size() || tower[2].size() != disksCount)
        return false;

    towersIsValid();

    return true;
}

void Towers::towersIsValid() const {

    assert((cursorPosition >= cursorPositionMin && cursorPosition <= cursorPositionMax) && "Cursor Position is invalid");
    assert((disksCount > 0 && disksCount <= MAX_DISKS_COUNT) && "Disk count is invalid");

    std::vector<unsigned int> temp;

    assert(vectorIsMonotone((std::vector<unsigned int>)tower[0]) && "Left tower disks are not monotone\n");
    assert(vectorIsMonotone((std::vector<unsigned int>)tower[1]) && "Middle tower disks are not monotone\n");
    assert(vectorIsMonotone((std::vector<unsigned int>)tower[2]) && "Right tower disks are not monotone\n");

    temp.insert(temp.end(), tower[0].begin(), tower[0].end());
    temp.insert(temp.end(), tower[1].begin(), tower[1].end());
    temp.insert(temp.end(), tower[2].begin(), tower[2].end());

    assert(temp.size() == disksCount && "Incorrect disk count\n");

    sort(temp.begin(), temp.end());
    for (unsigned int i = 0; i < temp.size(); ++i)
        assert(temp[i] == (i + 1) && "Incorrect tower disks\n");
}

bool Towers::vectorIsMonotone(std::vector<unsigned int> vec) const {
    for (unsigned int i = 1; i < vec.size(); ++i) {
        if (vec[i - 1] <= vec[i])
            return false;
    }

    return true;
}

void Towers::cursorMoveRight() {
    switch (cursorPosition){
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
    if(tower[cursorPosition].empty()) 
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
    printLevelByIndex(tower[cursorPosition].size());
}
void Towers::diskMoveDown() {
    if (!upperDiskSize)
        return;

    if(!tower[cursorPosition].empty() && upperDiskSize > tower[cursorPosition].back())
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
    printLevelByIndex(tower[cursorPosition].size() - 1);
}

//void Towers::displayTowerNumFormat(std::vector<unsigned int>& tower, std::string& str) const {
//
//    std::cout << str << std::endl;
//
//    if (!tower.size())
//        std::cout << "Is empty";
//
//    for (unsigned int diskSize : tower)
//        std::cout << diskSize << " ";
//    std::cout << std::endl;
//}

//void Towers::displayTowersNumFormat() const {
//
//    displayTowerNumFormat((std::vector<unsigned int>)tower[0], (std::string)"The Left Tower");
//    displayTowerNumFormat((std::vector<unsigned int>)tower[1], (std::string)"The Middle Tower");
//    displayTowerNumFormat((std::vector<unsigned int>)tower[2], (std::string)"The Right Tower");
//
//    std::cout << std::endl;
//}
