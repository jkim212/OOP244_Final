/*
*****************************************************************************
						Milestone - 1 / 5.1 / 5.2 / 5.3 / 5.4 / 5.5
Full Name  : Juhan Kim
Student ID#: 126478221
Email      : jkim687@myseneca.ca
Section    : OOP244 NRB
Date       : Mar 9, 2023 / April 1, 2023

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#ifndef SDDS_POSAPP_H_
#define SDDS_POSAPP_H_
#include <iostream>
#include "Perishable.h"
#include "NonPerishable.h"


namespace sdds {

	const int NAME_LENGTH = 128;

	class PosApp {
		char* fileName = new char[NAME_LENGTH+1];			//Store file name
		Item* Iptr[MAX_NO_ITEMS];							//Dynamic array of Items
		int nptr;											//Number of items

		PosApp(const PosApp&);
		PosApp& operator=(const PosApp&);

	public:
		PosApp(const char* name);
		~PosApp();
		void run();

		void act_title(const char* title);					//Print formatted title
		void loadRecs();									//Load records from file

		void addItem();										//Adds Item to the Iptr array
		void removeItem();									//Remove Item from the array
		void stockItem();									//Add quantity to the item in array
		void listItems();									//List items in alphabetical order
		void POS();	
		void saveRecs();									//Save to a file
		void menu();										//Dispaly Menu
		
		int selectItem(bool tot);							//Used to display items in alphabetical list. If parameter = true, also display total

		void bubbleSort(Item* data[], int itemCount);		//Sort array

		Item* search(char* SKU);							//Search Iptr array by given SKU cstring and return Item pointer
	};

}


#endif // !SDDS_POSAPP_H_
