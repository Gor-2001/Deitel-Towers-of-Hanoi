#include <iostream>
#include <stack>
#include <vector>

class Towers
{

public:

    Towers(int disks_count = 3)
    {
        setDisksCount(disks_count);
        towerClear(towerLeft);
        towerClear(towerMiddle);
        towerClear(towerRight);

        towerFill(towerLeft, disks_count);
    }

    void setDisksCount(int disks_count) {
        disksCount = disks_count;
    }

    void displayTowers() const {

        std::cout << "The Leftmost Tower" << std::endl;
        if (!towerLeft.size())
            std::cout << "Is empty";

        for(int diskSize : towerLeft)
            std::cout << diskSize << " ";
        std::cout << std::endl;

        std::cout << "The Middle Tower" << std::endl;
        if (!towerMiddle.size())
            std::cout << "Is empty";

        for (int diskSize : towerMiddle)
            std::cout << diskSize << " ";
        std::cout << std::endl;

        std::cout << "The Rightmost Tower" << std::endl;
        if(!towerRight.size())
            std::cout << "Is empty";

        for (int diskSize : towerRight)
            std::cout << diskSize << " ";
        std::cout << std::endl;
    }

private:

    int disksCount;
    std::vector<int> towerLeft;
    std::vector<int> towerMiddle;
    std::vector<int> towerRight;

    void towerClear(std::vector<int>& tower){
        tower.clear();
    }

    void towerFill(std::vector<int>& tower, int disks_count) {
        towerClear(tower);

        for (size_t i = 0; i < disks_count; i++)
            tower.push_back(i + 1);
    }

};

int main()
{
    Towers towers(13);
    towers.displayTowers();

    return 0;
}
