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


#ifndef SDDS_ERROR_H_
#define SDDS_ERROR_H_
#include <iostream>


namespace sdds {

	class Error {
		char* desc;												//Dynamic memory to store error message

	public:	
		Error();												//Default constructor
		Error(const char* err);									//Set message to parameter
		Error(const Error& other);								//Set error to another error object
		~Error();												//Destructor

		Error& operator=(const Error& rhs);						//Copy function
		void operator=(const char* msg);						//Set message to a string
		operator bool() const;									//Check if message exists

		Error& clear();											//Clear message
		std::ostream& outputData(std::ostream& os) const;		//Formatted output of the message

	};

	std::ostream& operator<<(std::ostream& os, const Error& err);	//Output Error object using outputData function
}


#endif