#include <iostream>
#include <string>
#include "head.h"

using namespace std;

int main() {
    Interface();
    return 0;
}

void Interface()
{
    int mode;
    bool flag = true;
    string modes = "1 mode: Create calendar; 2 mode: Test program; 3 mode: Exit";
    while (flag)
    {
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
        cout << modes << endl;
        cout << "Enter mode for work: ";
        cin >> mode;
        cout << endl;
        switch (mode)
        {
            case 1:
                Create_Calendar();
                break;
            case 2:
                Test();
                break;
            default:
                flag = false;
                break;
        }
        cout << endl;
    }
}

int GetDays(int year, int month)
{
    int Moths[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    int leapDay = IsLeapYear(year);
    if (month == 2) return Moths[month - 1] + leapDay;
    else return Moths[month - 1];
}

bool IsLeapYear(int year)
{
    return ((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0));
}

bool TestCase(int exeption, int real) {
    return exeption == real;
}

bool TestCase(string exeption, string real) {
    return exeption == real;
}

void Test() {

    int FailsCountOfGetDays = 0, FailsCountOfMonthName = 0, FailsOfGetDaysOfWeek = 0;

    FailsCountOfGetDays += !TestCase(31, GetDays(2021, 10));
    FailsCountOfGetDays += !TestCase(28, GetDays(1983, 2));
    FailsCountOfGetDays += !TestCase(31, GetDays(2017, 3));
    FailsCountOfGetDays += !TestCase(31, GetDays(1, 3));
    FailsCountOfGetDays += !TestCase(31, GetDays(22563, 12));

    FailsCountOfMonthName += !TestCase("February", MonthName(2));
    FailsCountOfMonthName += !TestCase("March", MonthName(3));
    FailsCountOfMonthName += !TestCase("June", MonthName(6));
    FailsCountOfMonthName += !TestCase("January", MonthName(1));
    FailsCountOfMonthName += !TestCase("December", MonthName(12));

    FailsOfGetDaysOfWeek += !TestCase(4, GetDayOfWeek(2021, 10));
    FailsOfGetDaysOfWeek += !TestCase(5, GetDayOfWeek(2022, 1));
    FailsOfGetDaysOfWeek += !TestCase(0, GetDayOfWeek(2004, 3));
    FailsOfGetDaysOfWeek += !TestCase(0, GetDayOfWeek(2022, 8));
    FailsOfGetDaysOfWeek += !TestCase(3, GetDayOfWeek(2022, 9));

    if (FailsCountOfGetDays + FailsCountOfMonthName + FailsOfGetDaysOfWeek == 0) cout << "All tests passed sucsesfully" << endl;
    else {
        if (FailsCountOfGetDays != 0) cout << "There is " << FailsCountOfGetDays << " Errors in GetDays \n";
        if (FailsCountOfMonthName != 0) cout << "There is " << FailsCountOfMonthName << " Errors in MonthName \n";
        if (FailsOfGetDaysOfWeek != 0) cout << "There is " << FailsOfGetDaysOfWeek << " Errors in GetDaysOfWeek \n";
    }
}

string MonthName(int number_month) {
    string month[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    return month[number_month - 1];
}

void Create_Calendar() {
    int year, month;

    cout << "Enter year: ";
    cin >> year;
    cout << "Enter month: ";
    cin >> month;

    string bl = "  ";
    int place_in_weak = 0;
    int days = GetDays(year, month);
    int start = GetDayOfWeek(year, month);
    string name_of_the_month = MonthName(month);

    cout << "----------------------------------" << endl;

    cout << "\t" << name_of_the_month << "\t" << year << endl;

    cout << bl << bl << "MN  TE  WD  TH  FR  ST  SN\n  ";

    if (start != place_in_weak)
        while (true) {
            cout << bl << bl;
            place_in_weak++;
            if (place_in_weak == start) break;
        }

    for (int i = 0; i < days; i++) {
        string data = "";
        data = to_string(i + 1);
        data.size() == 1 ? data = " " + data : data = data;
        if (place_in_weak == 7) {
            cout << "\n" << bl << bl << data;
            place_in_weak = 0;
        }
        else
            cout << bl << data;
        place_in_weak++;
    }
    cout << "\n----------------------------------" << endl;
}

int CalcDayNumFromDate(int y, int m, int d)
{
    m = (m + 9) % 12;
    y -= m / 10;
    int dn = 365 * y + y / 4 - y / 100 + y / 400 + (m * 306 + 5) / 10 + (d - 1);
    return dn;
}

int GetDayOfWeek(int year, int month)
{
    int day[] = { 2,3,4,5,6,0,1 };
    int dn = CalcDayNumFromDate(year, month, 1);
    return day[dn % 7];
}





