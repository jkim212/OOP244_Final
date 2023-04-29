/*
*****************************************************************************
							 Milestone 4
Full Name  : Juhan Kim
Student ID#: 126478221
Email      : jkim687@myseneca.ca
Section    : OOP244 NRB
Date       : Mar 31, 2023

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#include "Perishable.h"

namespace sdds {
	char Perishable::itemType() const {
		return 'P';												//Return itemType 'P'
	}

	std::ostream& Perishable::write(std::ostream& os) const {
		Item::write(os);									//Call base class function
		if (Item::operator bool()) {							//If Item is valid
			
			if (Item::i_displayType == POS_LIST) {				//If display type is "List"
				os << "  " << date << " |";						//Add date in format
			}
			else if (Item::i_displayType == POS_FORM) {			//If display type is "Form"
				os << "Expiry date: " << date << std::endl;		//Add date as follows
				os << "=============^\n";
			}
		}
		return os;
	}

	std::istream& Perishable::read(std::istream& is) {
		Item::read(is);											//Read item info
		if (Item::operator bool()) {							//If item is valid
			std::cout<< "Expiry date (YYYY/MM/DD)\n> ";			//Prompt user to enter expiry date
			is >> date;											//Get date from istream
			if (!date) {										//If date has error, set to Item error
				Item::errState = date.error();
			}
		}
		return is;
	}

	std::ifstream& Perishable::load(std::ifstream& file) {
		Item::load(file);										//Load Item info from file
		if (Item::operator bool() && !file.fail()) {			//If Item is valid and read didn't fail
			Date temp;									//Create temp Date object
			temp.dateOnly(true);								//Set to "Date Only"
			file.ignore(1);										//Ignore 1 char
			file >> temp;										//Read to temp
			if (temp) {											//If date is valid, set to temp, if not set Item error to date error
				date = temp;
			}
			else {
				Item::errState = temp.error();
			}
		}
		return file;
	}
	std::ofstream& Perishable::save(std::ofstream& file) const {
		if (Item::operator bool()) {							//If Item is valid
			Item::save(file);									//Save Item to file,
			file << "," << date;								//Add Expiry date info
		}
		return file;
	}
}