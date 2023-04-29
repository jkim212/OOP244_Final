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

#ifndef SDDS_NONPERISHABLE_H_
#define SDDS_NONPERISHABLE_H_

#include "Item.h"												//Import necessary headers

namespace sdds {
	class NonPerishable : public Item {
		char itemType() const override;							//Return item type as NonPerishable

		std::ostream& write(std::ostream& os) const override;	//Override write function to add extra info
	};

}



#endif