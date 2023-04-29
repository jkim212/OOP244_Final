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

#include "NonPerishable.h"
#include <iostream>
#include <iomanip>

namespace sdds {
	char NonPerishable::itemType() const {
		return 'N';													//Return Item type as 'N' for NonPerishable
	}

	std::ostream& NonPerishable::write(std::ostream& os) const {
		Item::write(os);										//Write Item info
		if (Item::operator bool()) {								//If Item is valid,
			if (Item::i_displayType == POS_LIST) {
				os << "     N / A   |";								//Add "N/A" since no expiry date exists
			}
			else if (Item::i_displayType == POS_FORM) {
				os << "=============^\n";
			}
		}
        return os;
	}


}
