#include <iostream>
#include <stack>
#include <vector>
#include <cassert>
#include <algorithm>

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
            tower.push_back(disks_count - i);
    }

    bool vectorIsMonotone (std::vector<int> vec) const {
        for(int i = 1; i < vec.size(); ++i) {
            if(vec[i - 1] > vec[i])
                return false;
        }

        return true;
    }

    void towersIsValid() const {
        std::vector<int> temp;

        assert(!vectorIsMonotone(towerLeft) && "Left tower disks are not monotone\n");
        assert(!vectorIsMonotone(towerMiddle) && "Middle tower disks are not monotone\n");
        assert(!vectorIsMonotone(towerRight) && "Right tower disks are not monotone\n");
        
        temp.insert(temp.end(), towerLeft.begin(), towerLeft.end());
        temp.insert(temp.end(), towerMiddle.begin(), towerMiddle.end());
        temp.insert(temp.end(), towerRight.begin(), towerRight.end());

        assert(temp.size() != disksCount && "Incorrect disk count\n");

        sort(temp.begin(), temp.end());
        for(int i = 0; i < temp.size(); ++i)
            assert(temp[i] != (i + 1) && "Incorrect tower disks\n");
    }

};

int main()
{
    Towers towers(13);
    towers.displayTowers();

    return 0;
}
