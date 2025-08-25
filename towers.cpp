#include "towers.h"

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

Towers::Towers(const unsigned int disks_count)
{
    setDisksCount(disks_count);
    setCursorPosition(cursorPositionLeft);
    setDiskPosition(diskPositionDown);
    setUpperDiskSize(0);
    towerFillBasic();
    towersIsValid();
}

void Towers::displayNum() const {
    displayTowerNum((std::vector<unsigned int>)tower[0], (std::string)"The Left Tower");
    displayTowerNum((std::vector<unsigned int>)tower[1], (std::string)"The Middle Tower");
    displayTowerNum((std::vector<unsigned int>)tower[2], (std::string)"The Right Tower");

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

void Towers::printEmptyString(const unsigned int count = 1) const {

    const unsigned int width = 6 * disksCount + 13;
    for (size_t i = 0; i < count; i++)
    {
        printString("#", 1);
        printString(" ", width - 2);
        printString("#", 1, true);
    } 
}

void Towers::printCeil() const {

    const unsigned int width = 6 * disksCount + 13;

    printString("#", width, true);
    printEmptyString(CEIL_HIGH - 1);
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
        printString("#", 1);
        for (size_t i = 0; i < 3; i++)
        {
            printString(" ", 2);
            tower[i].size() >= level ? printDisk(tower[i][level - 1]) : printDisk(0);

        }
        printString("  #", 1, true);
    }
}

void Towers::printUpperDisk() const {

    if(upperDiskSize)
    {
        printString("#  ", 1);
        printString(" ", cursorPosition * (disksCount * 2 + 3));

        printString(" ", disksCount - upperDiskSize);
        printString("*", upperDiskSize);
        printString("#", 1);
        printString("*", upperDiskSize);
        printString(" ", disksCount - upperDiskSize);

        printString(" ", (2 - cursorPosition) * (disksCount * 2 + 3));
        printString("  #", 1, true);
    }
    else
        printEmptyString();

}

void Towers::printLowerDisk() const {
    
    const unsigned int index = tower[cursorPosition].size() - 1;
    unsigned int diskSize;
    printString("#  ", 1);

    diskSize = tower[0].size() > index ? tower[0][index] : 0;
    printString(" ", disksCount - diskSize);
    printString("*", diskSize);
    printString("#", 1);
    printString("*", diskSize);
    printString(" ", disksCount - diskSize);
    printString(" ", 2);

    diskSize = tower[1].size() > index ? tower[1][index] : 0;
    printString(" ", disksCount - diskSize);
    printString("*", diskSize);
    printString("#", 1);
    printString("*", diskSize);
    printString(" ", disksCount - diskSize);
    printString(" ", 2);

    diskSize = tower[2].size() > index ? tower[2][index] : 0;
    printString(" ", disksCount - diskSize);
    printString("*", diskSize);
    printString("#", 1);
    printString("*", diskSize);
    printString(" ", disksCount - diskSize);
    printString(" ", 2);

    printString("#", 1, true);
}

void Towers::printCursor() const {

    printString("#  ", 1);
    printString(" ", cursorPosition * (disksCount * 2 + 3) + disksCount - 1);
    printString("#", 3);
    printString(" ", (2 - cursorPosition) * (disksCount * 2 + 3) + disksCount - 1);
    printString("  #", 1, true);

}
void Towers::printFloor() const {

    printString("#  ", 1);
    printString("#", 2 * disksCount + 1);
    printString(" ", 2);
    printString("#", 2 * disksCount + 1);
    printString(" ", 2);
    printString("#", 2 * disksCount + 1);
    printString("  #", 1, true);

    printCursor();
    printEmptyString();
    printString("#", 6 * disksCount + 13, true);
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

void Towers::setUpperDiskSize(const unsigned int upper_disk_size){
    upperDiskSize = upper_disk_size;
}

unsigned int Towers::getDisksCount(){
    return disksCount;
}

unsigned int Towers::getCursorY()
{ 
    return 
        CEIL_HIGH + getDisksCount() + 1;
}

unsigned int Towers::getUpperDiskY()
{
    return UPPER_DISK_Y;
}

unsigned int Towers::getLowerDiskY()
{
    return 
        CEIL_HIGH + disksCount - tower[cursorPosition].size();
}

void Towers::towersClear() {
    tower[0].clear();
    tower[1].clear();
    tower[2].clear();
}

void Towers::towerFillBasic() {
    towersClear();

    for (size_t i = 0; i < disksCount; i++)
        tower[0].push_back(disksCount - i);
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

bool Towers::winningPosition() const
{
    if(upperDiskSize)
        return false;

    if(tower[0].size() != 0 || tower[1].size() != 0 || tower[2].size() != disksCount)
        return false;
    
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
        return;
    }

    gotoxy(0, getUpperDiskY());
    printUpperDisk();

    gotoxy(0, getCursorY());
    printCursor();
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
        return;
    }

    gotoxy(0, getUpperDiskY());
    printUpperDisk();

    gotoxy(0, getCursorY());
    printCursor();
}

void Towers::diskMoveUp()
{
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

    gotoxy(0, CEIL_HIGH);
    printDisks();
    //gotoxy(0, CEIL_HIGH + disksCount - tower[cursorPosition].size());
    //printLowerDisk();
}
void Towers::diskMoveDown()
{
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

    gotoxy(0, CEIL_HIGH);
    printDisks();
    //gotoxy(0, CEIL_HIGH + disksCount - tower[cursorPosition].size() );
    //printLowerDisk();
}
