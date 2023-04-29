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

#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iomanip>
#include <cstring>
#include <string>
#include "PosApp.h"
#include "Bill.h"
namespace sdds {

	PosApp::PosApp(const char* name) {
		delete[] fileName;
		int len = strlen(name);
		fileName = new char[len+1];
		strcpy(fileName, name);
		nptr = 0;
	}

	PosApp::~PosApp() {
		delete[] fileName;
		for (int i = 0; i < nptr; i++) {
			delete Iptr[i];
		}
	}

	void PosApp::run() {

		loadRecs();

		bool exit = false;
		while (!exit) {

			menu();

			char* input = nullptr;											//Used for storing user input
			bool flag = true;												//Flag goes down when valid input is present
			int temp = 0;													//To store user input as integer
			do
			{
				delete[] input;
				input = new char[10];
				std::cin >> input;

																			//Check if input is a number
				if (input[0] == '-' || isdigit(input[0])) {					//Only check if the first char is either a '-' sign or a digit
					bool number = true;
					int len = strlen(input);
					for (int i = 1; i < len; i++) {				//Go through each char and check if its a digit
						if (!isdigit(input[i]))
							number = false;
					}

					if (!number) {											//If any one of a char is not a number, print error
						std::cout << "Invalid Integer, try again: ";
					}	
					else {													//If the input is a number,
						temp = atoi(input);									//use atoi to change input char to integer
						if (temp >= 0 && temp <= 5) {						//If the number is in range, pass
							flag = false;
						}
						else {
							std::cout << "[0<=value<=5], retry: > ";				//If not in range, show range and repeat
						}
					}

				}
				else {
					std::cout << "Invalid Integer, try again: ";					//If input is not a number, print error and repeat
				}
			} while (flag);													//Continue until valid input

			delete[] input;													//Free dynamic memory

			switch (temp)													//Use switch for menu options
			{
			case 0:
				saveRecs();
				std::cout << "Goodbye!" << std::endl;
				exit = true;
				break;
			case 1:
				listItems();
				break;
			case 2:
				addItem();
				break;
			case 3:
				removeItem();
				break;
			case 4:
				stockItem();
				break;
			case 5:
				POS();
				break;

			default:
				break;
			}
		}
	}


	void PosApp::menu() {														//Display menu
		std::cout << "The Sene-Store" << std::endl;
		std::cout << "1- List items" << std::endl;
		std::cout << "2- Add item" << std::endl;
		std::cout << "3- Remove item" << std::endl;
		std::cout << "4- Stock item" << std::endl;
		std::cout << "5- POS" << std::endl;
		std::cout << "0- exit program" << std::endl;
		std::cout << "> ";
	}

	void PosApp::act_title(const char* title) {					//Prints given title in format
		std::cout << ">>>> ";
		std::cout.fill('.');
		std::cout << std::setw(72) << std::left << title << std::endl;
	}

	void PosApp::loadRecs() {													//Load records from file
		act_title("Loading Items");
		std::ifstream input(fileName);											//Create ifstream
		if (input.fail()) {														//If unsuccessful, create and close file
			std::ofstream output(fileName);
			output.close();
			return;
		}
		nptr = 0;																//Set Number of items to 0
		while (input.good() && nptr < MAX_NO_ITEMS && input.peek() != EOF) {	//While file is valid, nptr is less than max items and next char is not end of file,
			char iType = input.get();					//Get item type and set to char
			input.ignore(1);							//Ignore next char, a comma
			if (iType == 'P') {							//If item type is 'P'
				Perishable* p = new Perishable();		//Create dynamic perishable item
				Iptr[nptr] = p;							//Set address to next spot in array
			}
			else if (iType == 'N') {					//Same for Non perishable
				NonPerishable* np = new NonPerishable();
				Iptr[nptr] = np;
			}
			Iptr[nptr]->load(input);					//Load item onto the array
			if (input.good() && input.peek() != EOF) {	//Increment number of items and proceed if the file is still valid and not at the end
				nptr++;
				input.ignore(1000, '\n');
			}
		}
	}

	void PosApp::saveRecs() {							//Save records to file
		act_title("Saving Data");
		std::ofstream file(fileName);					//Create ofstream
		if (file.is_open()) {
			for (int i = 0; i < nptr; i++) {			//Go through the array and save each items in the array
				Iptr[i]->save(file);
				file << '\n';
			}
			file.close();
		}
	}

	void PosApp::listItems() {							//Format display items
		act_title("Listing Items");
		std::cout.fill(' ');
		std::cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |\n"
				  << "-----|--------|--------------------|-------|---|----|---------|-------------|\n";

		double total = 0;
		bubbleSort(Iptr, nptr);							//Sort the array alphabetically
		for (int i = 0; i < nptr; i++) {				//Go through the array and format print
			std::cout << std::right<<std::setw(4) << i+1 << " |" << std::left;
			Iptr[i]->displayType(POS_LIST).write(std::cout);
			total += Iptr[i]->cost()* Iptr[i]->quantity();	//Add up total price for the items
			std::cout << "\n";
		}

		std::cout	<< "-----^--------^--------------------^-------^---^----^---------^-------------^\n"
					<< "                               Total Asset: $  |      "<<std::right<<std::setw(8)<<total<<"|\n"
					<< "-----------------------------------------------^--------------^\n\n";
	}

	void PosApp::bubbleSort(Item* data[], int itemCount)		//Sort the array
	{
		int i, j;
		Item* temp;
		for (i = itemCount - 1; i > 0; i--)				//Go through the items
		{
			for (j = 0; j < i; j++)						//Index only up to i
			{
				if (*data[j] > *data[j + 1])			//Compare two items by implemented > operator
				{										//If Item on the left is "higher" than the right alphabetically, 
					temp = data[j];						//switch places
					data[j] = data[j + 1];
					data[j + 1] = temp;
				}
			}
		}
	}

	void PosApp::addItem() {
		act_title("Adding Item to the store");
		if (nptr >= MAX_NO_ITEMS) {					//If the number of items is at max
			std::cout << "Inventory Full!";
		}
		else {
			Item* temp;									//Create Item pointer
			char itemty;								//Store user input for 'y'/'n'
			bool flag = true;
			bool flag2 = true;
			std::cout << "Is the Item perishable? (Y)es/(N)o: ";
			do {
				do {
					std::cin >> itemty;					//Get user input
					if (itemty == 'y') {				//If 'y', store as perishable
						flag = false;
						temp = new Perishable();		//Set temp to a new Perishable item

						std::cin.ignore(1000, '\n');
						std::cin >> *temp;				//Read in values using >> operator of Perishable class

						if (*temp) {					//If item is valid, store to next Iptr array and increment nptr
							flag2 = false;
							Iptr[nptr] = temp;
							nptr++;
						}
						else {
							std::cin.clear();				//If item is not valid,
							std::cin.ignore(1000, '\n');
							std::cout << *temp;
							std::cout << ", try again...\n";
						}
					}
					else if (itemty == 'n') {			//In case of NonPerishables
						flag = false;
						temp = new NonPerishable();
						std::cin.ignore(1000, '\n');
						std::cin >> *temp;

						if (*temp) {
							flag2 = false;
							Iptr[nptr] = temp;
							nptr++;
						}
						else {
							std::cin.clear();
							std::cin.ignore(1000, '\n');
							std::cout << *temp;
							std::cout << ", try again...\n";
						}
					}
					else {
						std::cout << "Only 'y' and 'n' are valid\n> ";		//In case of user input other than 'y' or 'n'
						std::cin.ignore(1000, '\n');
					}
				} while (flag);
			} while (flag2);
			//act_title("DONE!");											//Title does not work as the expected output has 70 width
			std::cout << ">>>> ";
			std::cout.fill('.');
			std::cout << std::setw(70) << std::left << "DONE!" << std::endl;
		}
	}

	int PosApp::selectItem(bool tot) {
		int ret = -1;												//Create int varaible for return value
		act_title("Item Selection by row number");
		std::cout << "Press <ENTER> to start....";					//Pause for newline char
		std::cin.ignore(1000, '\n');
		std::cin.ignore(1000, '\n');

		//Display Items
		act_title("Listing Items");
		std::cout.fill(' ');
		std::cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |\n"
			<< "-----|--------|--------------------|-------|---|----|---------|-------------|\n";

		double total = 0;
		bubbleSort(Iptr, nptr);							//Sort the array alphabetically
		for (int i = 0; i < nptr; i++) {				//Go through the array and format print
			std::cout << std::right << std::setw(4) << i + 1 << " |" << std::left;
			Iptr[i]->displayType(POS_LIST).write(std::cout);
			total += Iptr[i]->cost() * Iptr[i]->quantity();	//Add up total price for the items
			std::cout << "\n";
		}

		std::cout << "-----^--------^--------------------^-------^---^----^---------^-------------^\n";

		//If parameter given is true, also print total
		if (tot) {
				std::cout << "                               Total Asset: $  |      " << std::right << std::setw(8) << total << "|\n"
				<< "-----------------------------------------------^--------------^\n\n";
		}

		//Prompt user for row number to delete
		std::cout << "Enter the row number: ";
		bool flag = true;
		do {
			std::cin >> ret;		//Read in value
			if (std::cin.fail()) {	//If non-integer input was given,
				std::cout << "Invalid Integer, try again: ";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
			}
			else if(ret < 1 || ret > nptr){	//If input was out of range,
				std::cout << "[1<=value<=" << nptr << "], retry: Enter the row number: ";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
			}
			else {
				flag = false;
			}
		} while (flag);

		return ret;
	}



	void PosApp::removeItem() {
		int index = -1;
		act_title("Remove Item");
		index = selectItem(false);						//Get index of item to be deleted
		std::cout << "Removing....\n";
		std::cout << Iptr[index - 1]->displayType(POS_FORM);	//Display item in POSFORM format
		delete Iptr[index-1];									//Remove item from the array
		memmove(Iptr + index-1, Iptr + index, (nptr - index) * sizeof(Item*));	//Shift all items behind index to one array to the left
		nptr--;															//Decrement nptr value
		//act_title("DONE!");											//Title does not work as the expected output has 70 width
		std::cout << ">>>> ";
		std::cout.fill('.');
		std::cout << std::setw(70) << std::left << "DONE!" << std::endl;
	}


	void PosApp::stockItem() {
		act_title("Select an item to stock");
		int index = selectItem(false);										//Get index of the item to stock
		std::cout << "Selected Item:\n";
		std::cout << Iptr[index - 1]->displayType(POS_FORM);				//Dispaly Item in POS_FORM format
		std::cout << "Enter quantity to add: ";
		int quan = -1;							//Variable to store quanity to add
		bool flag = true;						
		do {
			std::cin >> quan;
			if (std::cin.fail()) {				//In case of non-integer input
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				std::cout << "Invalid Integer, try again: ";
			}
			else if (quan < 1 || quan > MAX_STOCK_NUMBER - Iptr[index - 1]->quantity()) {	//In case of input out of bounds
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				std::cout << "[1<=value<="<<MAX_STOCK_NUMBER - Iptr[index-1]->quantity()<<"], retry: Enter quantity to add: ";
			}
			else {							//Successful input
				flag = false;
				*Iptr[index - 1] += quan;	//Add quantity to the item
			}


		} while (flag);


		//act_title("DONE!");											//Title does not work as the expected output has 70 width
		std::cout << ">>>> ";
		std::cout.fill('.');
		std::cout << std::setw(70) << std::left << "DONE!" << std::endl;
	}

	Item* PosApp::search(char* SKU) {
		int index = -1;
		for (int i = 0; i < nptr; i++) {							//Go through the Iptr array
			if (*Iptr[i] == SKU) {									//If SKU value matches current index
				index = i;											//Store index
			}
		}
		if (index == -1) {
			return nullptr;
		}
		return Iptr[index];											//Return the address of Item in that index
	}

	void PosApp::POS() {
		act_title("Starting Point of Sale");
		Bill* receipt = new Bill();							//Create dynamic bill
		receipt->clear();									//Initialize bill
		std::string tempst;									//Create string to store user input
		char input[MAX_SKU_LEN];							//Change string input to cstring
		bool flag = true;
		double trackTot = 0;								//Track total cost

		std::cin.ignore(1000, '\n');
		do {
			std::cout << "Enter SKU or <ENTER> only to end sale...\n";		//Prompt
			std::cout << "> ";
			std::getline(std::cin, tempst);									//Get input up to newline char
			strcpy(input, tempst.c_str());									//Convert input to cstring
			if (input[0] == '\0') {											//If input is empty, exit loop
				flag = false;
			}
			else if (tempst.length() < MAX_SKU_LEN && input[0] != '\0') {	//If read value is less than max capacity and input is valid,
				Item* found = search(input);								//Create dynamic Item to store address of search result
				if (found != nullptr) {										//If found item is valid,
					*found -= 1;											//Decrement its quantity by one
					if (!*found) {											//If Item has error message after the decrementation,
						std::cout << found->displayType(POS_FORM);			//Print error message,
						found->clear();										//Clear error message
					}
					else {													//If item is valid after decrementation,
						std::cout << found->displayType(POS_FORM);			//Print Item info as POS FORM format
						receipt->add(found);								//Add item to Bill
						trackTot += found->cost();							//Add its cost to the total
						std::cout << std::endl;
						std::cout << ">>>>> Added to bill\n"
							">>>>> Total: "<<trackTot<<"\n";				//Display current total
					}
				}
				else {
					std::cout << "!!!!! Item Not Found !!!!!\n";			//If found is a nullptr, display error
				}
			}
			else if (tempst.length() > MAX_SKU_LEN) {						//If user input is too long, print error
				std::cout << "SKU too long\n";
				std::cin.clear();
			}
		} while (flag);

		receipt->print(std::cout);											//Print bill
		delete receipt;														//Free memory
	}


}
