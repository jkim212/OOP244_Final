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

#ifndef SDDS_PERISHABLE_H_
#define SDDS_PERISHABLE_H_

#include "Item.h"													//Import necessary headers
#include "Date.h"

namespace sdds {
	class Perishable : public Item {								//Derived class of Item
		Date date;											//Object Date to store expiry date

		char itemType() const override;								//Return item type as Perishable
		//Override Item class functions to add information
		std::ostream& write(std::ostream& os) const override;		
		std::istream& read(std::istream& is) override;
		std::ifstream& load(std::ifstream& file) override;
		std::ofstream& save(std::ofstream& file) const override;
	};



}



#endif