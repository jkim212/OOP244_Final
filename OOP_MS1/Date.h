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


#ifndef SDDS_DATE_H_
#define SDDS_DATE_H_
#include <iostream>
#include "Error.h"

namespace sdds {

	class Date {												//Create required attributes
		int year;
		int month;
		int day;
		int hour;
		int minute;
		bool date_only;											//Flag if date does not include time


	public:
		Error err;												//Error attribute left as public to access in >> operator
		Date();													//Basic constructors
		Date(int year, int mon, int day);
		Date(int year, int mon, int day, int hour, int minute = 0);

		void getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly);		//Gets current system date and time
		int uniqueDateValue(int year, int mon, int day, int hour = 0, int min = 0) const;			//Converts to unique time for comparison
		int daysOfMonth(int year, int month);														//Calculates the days in each month

		Date& operator=(const Date& rhs);						//Copy constructor for use in >> operator
		bool operator ==(const Date& right) const;				//Simple comparison operators
		bool operator !=(const Date& right) const;
		bool operator <(const Date& right) const;
		bool operator >(const Date& right) const;
		bool operator <=(const Date& right) const;
		bool operator >=(const Date& right) const;

		Date& dateOnly(bool);									//Sets the date_only attribute to given boolean values
		operator bool() const;									//Returns true if no Error exists

		void reset();											//Resets all date and time values to 0


		const Error& error() const;								//Returns Error object of the Date
		std::ostream& outputData(std::ostream& os) const;				//Formatted output data

	};
	std::ostream& operator<<(std::ostream& os, const Date& date);		//Outputs formatted data from outputData function
	std::istream& operator>>(std::istream& is, Date& date);		//Reads values and sets to Date given in parameter

}


#endif