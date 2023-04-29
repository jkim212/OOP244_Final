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
#include <cstring>
#include "Error.h"

using namespace std;

namespace sdds {

	Error::Error() {
		desc = nullptr;										//Default null pointer
	}

	Error::Error(const char* err) {
		if (err != nullptr) {								//If Error message exists, copy to its attribute
			desc = new char[strlen(err) + 1];
			strcpy(desc, err);
		}
		else {
			desc = nullptr;
		}
	}

	Error::Error(const Error& other) {
		if (other.desc != nullptr) {						//Copy error message from another Error object
			desc = new char[strlen(other.desc) + 1];		//Possible implementation to restrict self-assignment
			strcpy(desc, other.desc);
		}
		else {
			desc = nullptr;
		}
	}

	Error::~Error() {										//Free dynamic memory
		delete[] desc;
		desc = nullptr;
	}

	Error& Error::operator=(const Error& rhs)
	{
		if (rhs.desc != nullptr) {							//Same logic as copy constructor
			if (desc != nullptr) {
				delete[] desc;
			}
			desc = new char[strlen(rhs.desc) + 1];
			strcpy(desc, rhs.desc);
		}
		else {
			if (desc != nullptr) {
				delete[] desc;
			}
			desc = nullptr;
		}

		return *this;
	}

	void Error::operator=(const char* msg) {
		if (msg != nullptr) {
			delete[] desc;
			desc = new char[strlen(msg) + 1];
			strcpy(desc, msg);
		}
		else {
			delete[] desc;
			desc = nullptr;
		}
	}

	Error::operator bool() const {
		return !(desc == nullptr);					//Return true for error existance
	}

	Error& Error::clear() {
		delete[] desc;								//Delete any existing message
		desc = nullptr;
		return *this;
	}

	ostream& Error::outputData(ostream& os) const {
		if (desc != nullptr) {
			os << desc;								//Print Error message
		}
		return os;
	}


	ostream& operator<<(ostream& os, const Error& err) {
		return err.outputData(os);
	}


}