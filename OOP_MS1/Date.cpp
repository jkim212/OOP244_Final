/*
*****************************************************************************
                             Milestone 2
Full Name  : Juhan Kim
Student ID#: 126478221
Email      : jkim687@myseneca.ca
Section    : OOP244 NRB
Date       : Mar 16, 2023

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include "Date.h"
#include "POS.h"

namespace sdds {

    Date::Date() {
        year = month = day = hour = minute = 0;                         //Initialize all varibles
        date_only = false;                                              
        getSystemDate(year, month, day, hour, minute, date_only);
    }

    Date::Date(int year, int mon, int day) {                            //Set attributes to given parameters
        this->year = year;
        this->month = mon;
        this->day = day;
        this->hour = 0;
        this->minute = 0;
        date_only = true;                                               //When only given 3 parameters, set date_only to true

        if (year < MIN_YEAR || year > MAX_YEAR) {                       //Validation process
            err = "Invalid Year";
        }
        else if (month < 1 || month > 12) {
            err = "Invalid Month";
        }
        else if (day < 1 || day > daysOfMonth(year, month)) {
            err = "Invalid Day";
        }
    }

    Date::Date(int year, int mon, int day, int hour, int minute) {      //Set attributes to given parameters
        this->year = year;
        this->month = mon;
        this->day = day;
        this->hour = hour;
        this->minute = minute;
        date_only = false;

        if (year < MIN_YEAR || year > MAX_YEAR) {                       //Validation
            err = "Invalid Year";
        }
        else if (month < 1 || month > 12) {
            err = "Invalid Month";
        }
        else if (day < 1 || day > daysOfMonth(year, month)) {
            err = "Invalid Day";
        }
        else if (hour < 0 || hour > 23) {
            err = "Invalid Hour";
        }
        else if (minute < 0 || minute > 59) {
            err = "Invlid Minute";
        }
    }

    //Provided
    void Date::getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly) {
        time_t t = time(NULL);
        tm lt = *localtime(&t);
        day = lt.tm_mday;
        mon = lt.tm_mon + 1;
        year = lt.tm_year + 1900;
        if (dateOnly) {
            hour = min = 0;
        }
        else {
            hour = lt.tm_hour;
            min = lt.tm_min;
        }
    }

    //Provided
    int Date::uniqueDateValue(int year, int mon, int day, int hour, int min) const {
        return year * 535680 + mon * 44640 + day * 1440 + hour * 60 + min;                          //Calculate total time in minutes
    }

    //Provided
    int Date::daysOfMonth(int year, int month) {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = month >= 1 && month <= 12 ? month : 13;
        mon--;
        return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }

    //Comparison operators
    bool Date::operator ==(const Date& right) const {
        return uniqueDateValue(year, month, day, hour, minute) == uniqueDateValue(right.year, right.month, right.day, right.hour, right.minute);
    }

    bool Date::operator !=(const Date& right) const {
        return uniqueDateValue(year, month, day, hour, minute) != uniqueDateValue(right.year, right.month, right.day, right.hour, right.minute);
    }

    bool Date::operator <(const Date& right) const {
        return uniqueDateValue(year, month, day, hour, minute) < uniqueDateValue(right.year, right.month, right.day, right.hour, right.minute);
    }

    bool Date::operator >(const Date& right) const {
        return uniqueDateValue(year, month, day, hour, minute) > uniqueDateValue(right.year, right.month, right.day, right.hour, right.minute);
    }

    bool Date::operator <=(const Date& right) const {
        return uniqueDateValue(year, month, day, hour, minute) <= uniqueDateValue(right.year, right.month, right.day, right.hour, right.minute);
    }

    bool Date::operator >=(const Date& right) const {
        return uniqueDateValue(year, month, day, hour, minute) >= uniqueDateValue(right.year, right.month, right.day, right.hour, right.minute);
    }


    Date& Date::dateOnly(bool inp) {
        if (date_only != inp || inp) {              //If parameter value is different and inp is true (a.k.a discard hours and minutes)
            date_only = inp;
            hour = 0;
            minute = 0;
        }
        return *this;
    }

    //Return inverse boolean value of err -> return true if no error
    Date::operator bool() const {
        return !err;
    }

    //Return Error object
    const Error& Date::error() const {
        return err;
    }

    //Copy constructor used to copy right hand date value to the left
    Date& Date::operator=(const Date& rhs) {
        year = rhs.year;
        month = rhs.month;
        day = rhs.day;
        hour = rhs.hour;
        minute = rhs.minute;
        date_only = rhs.date_only;
        err = rhs.err;

        return *this;
    }

    //Formatted output depending on existance of Error
    std::ostream& Date::outputData(std::ostream& os) const {
        if (err) {
            os << err << "(";
        }

        os << year << "/";
        if (month < 10) {                               //Add 0 to the start of single digit
            os << "0";
        }
        os << month << "/";

        if (day < 10) {
            os << "0";
        }
        os << day;
        if (!date_only) {
            os << ", ";
            if (hour < 10) {
                os << "0";
            }
            os << hour << ":";
            if (minute < 10) {
                os << "0";
            }
            os << minute;
        }

        if (err) {
            os << ")";
        }
        return os;
    }

    void Date::reset() {
        year = 0;
        month = 0;
        day = 0;
        hour = 0;
        minute = 0;
    }

    std::ostream& operator<<(std::ostream& os, const Date& date) {
        return date.outputData(os);
    }


    std::istream& operator>>(std::istream& is, Date& date) {
        date.err.clear();                                       //Clear any Error messages
        date.reset();                                           //Clear all date/time value
        int year = 0, month = 0, day = 0, hour = 0, minute = 0;

        is >> year;
        if (is.fail()) {                                        //If import fails, set current values to temp
            Date temp(year, month, day, hour, minute);          //Copy to given date object
            date = temp;
            date.err = "Cannot read year entry";                //Set Error message of given date object
            return is;                                          //Exit
        }
        is.ignore();                                            //Repeat
        is >> month;
        if (is.fail()) {
            Date temp(year, month, day, hour, minute);
            date = temp;
            date.err = "Cannot read month entry";
            return is;
        }
        is.ignore();
        is >> day;
        if (is.fail()) {
            Date temp(year, month, day, hour, minute);
            date = temp;
            date.err = "Cannot read day entry";
            return is;
        }

        if (is.peek() != '\n') {                                //If more inputs are present, check for hour and minutes
            is.ignore();
            is >> hour;
            if (is.fail()) {
                Date temp(year, month, day, hour, minute);
                date = temp;
                date.err = "Cannot read hour entry";
                return is;
            }
            is.ignore();
            is >> minute;
            if (is.fail()) {
                Date temp(year, month, day, hour);
                date = temp;
                date.err = "Cannot read minute entry";
                return is;
            }

            Date temp(year, month, day, hour, minute);
            date = temp;
        }
        else {

            Date temp(year, month, day);
            date = temp;
        }


        return is;
    }

}

