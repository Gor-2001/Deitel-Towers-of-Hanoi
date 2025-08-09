#include <iostream>
#include <string>
#include <ctime>
#include <vector>
using namespace std;

typedef struct Data Data;

struct Data {
    unsigned int day;
    unsigned int month;
    unsigned int year;
};

class HeartRates {

public:

    HeartRates(string f_name = "Gor", string l_name = "Melkumyan", Data b_day = {23, 12, 2001}) {

        if(!validBirthday(b_day))
            cout << "INVALID BIRTHDAY DATA" << endl;

        setFirstName(f_name);
        setLastName(l_name);
        setBirthday(b_day);
        
    }

    void setFirstName(string f_name) {
       firstName = f_name;
    }
    
    void setLastName(string l_name) {
        lastName = l_name;
    }

    void setBirthday(Data b_day) {

        if (!validBirthday(b_day))
            cout << "INVALID BIRTHDAY DATA" << endl;

        birthday.day = b_day.day;
        birthday.month = b_day.month;
        birthday.year = b_day.year;
    }

    string getFirstName() const{
        return firstName;
    }
    
    string getLastName() const {
        return lastName;
    }

    Data getBirthday() const{
        Data b_day;
        b_day.day = birthday.day;
        b_day.month = birthday.month;
        b_day.year = birthday.year;
        return b_day;
    }

    string dataToString() const{
        string b_day_str;
        b_day_str.append(to_string(birthday.day));
        b_day_str.append("-");
        b_day_str.append(to_string(birthday.month));
        b_day_str.append("-");
        b_day_str.append(to_string(birthday.year));
        return b_day_str;
    }

    unsigned int getMaxiumumHeartRate() const {
        return 220 - getAge();
    }

    vector <double> getTargetHeartRate() const {
        unsigned int max = getMaxiumumHeartRate();

        return {max * 0.5, max * 0.8};
    }

    unsigned int getAge() const {

        if (!validBirthday(birthday))
            cout << "INVALID BIRTHDAY DATA" << endl;

        Data today = getTodayData();

        unsigned int age = today.year - birthday.year;
        if(today.month > birthday.month)
            return age;
        else if(today.month < birthday.month)
            return age - 1;
        else{
            if(today.day >= birthday.day)
                return age;
            else
                return age - 1;
        }
    }
    
    void printInfo() const {
        cout << "Last Name is " << getLastName() << endl;
        cout << "First Name is " << getFirstName() << endl;
        cout << "Birthday Data is " << dataToString() << endl;
        cout << "Age is " << getAge() << endl;
        cout << "Max Heart Rate is " << getMaxiumumHeartRate() << endl;

        vector<double> targetRange = getTargetHeartRate();
        cout << "Target Heart Rate is from " << targetRange[0] << " to " << targetRange[1] << endl;
    }

private:
    string firstName;
    string lastName;
    Data birthday;

    Data getTodayData() const {
        Data today;
        tm localTime;
        time_t currentTime = time(0);

        if (localtime_s(&localTime, &currentTime) == 0) {
            today.year = localTime.tm_year + 1900;
            today.month = localTime.tm_mon + 1;
            today.day = localTime.tm_mday;
        }
        else {
            today.year = 0;
            today.month = 0;
            today.day = 0;
        }

        return today;
    }

    bool validBirthday(Data birthday) const
    {
        Data today = getTodayData();
        //Year
        if(today.year > birthday.year)
            return true;
        else if(today.year < birthday.year)
            return false;
        else {
            //Month    
            if(today.month > birthday.month)
                return true;
            else if(today.month < birthday.month)
                return false;
            else{
                //Day
                if (today.day >= birthday.day)
                    return true;
                else
                    return false;
            }
        }

        return false;
    }
};


int main()
{
    HeartRates Person("Vaxoyan", "Vaxo", {8, 8, 2024});
    Person.printInfo();

    return 0;
}
