/*
*****************************************************************************
                             Milestone 3
Full Name  : Juhan Kim
Student ID#: 126478221
Email      : jkim687@myseneca.ca
Section    : OOP244 NRB
Date       : Mar 27, 2023

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include "Item.h"
#include <cstring>                              //Used for functions: strcpy, strncpy, strlen, etc
#include <iostream>                             //Used for io streams
#include <iomanip>                              //Used for functions: fixed, setPrecision, etc
#include <limits>                               //Used to clear input buffer and clearing whole line
#include <algorithm>                            //Used to clear input buffer and use max() function
#include <fstream>                              //Used for file streams
#include <sstream>                              //Used to output strings to a file

using namespace std;

namespace sdds {
    Item::Item() {                              //0 parameter constructor sets all values to empty state
        sku[0] = {};
        name = nullptr;
        price = 0.0;
        taxed = false;
        i_quantity = 0;
        i_displayType = 0;
        errState.clear();
    }

    Item::Item(const Item& other) {             //Copy using overloaded = operator
        *this = other;
    }

    Item::~Item() {                             //Free dynamic memory
        delete[] name;
    }

    Item& Item::operator=(const Item& other) {              
        if (this != &other && other.name != nullptr) {      //Safe copy
            strncpy(sku, other.sku, MAX_SKU_LEN);
            if (name != nullptr) {
                delete[] name;
            }
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
            price = other.price;
            taxed = other.taxed;
            i_quantity = other.i_quantity;
            i_displayType = other.i_displayType;
            errState = other.errState;
        }
        return *this;
    }


    bool Item::operator== (const char* sku) const {             //Returns compared sku value between 2 items
        return strcmp(this->sku, sku) == 0;
    }

    bool Item::operator>(const Item& other) const {             //Compares two items' names and return its result
        return strcmp(name, other.name) > 0;
    }

    int Item::operator+=(int quantity) {                        //Adds item quantity by its paramter
        if (quantity + this->i_quantity > MAX_STOCK_NUMBER) {   //Going over Max stock number sets error message
            errState = ERROR_POS_QTY;
            this->i_quantity = MAX_STOCK_NUMBER;
        }
        else {
            this->i_quantity += quantity;
        }
        return this->i_quantity;
    }


    int Item::operator-=(int quantity) {                        //Removes item quantity by its paramter
        if (this->i_quantity < quantity) {                      //Attemp to remove more than existing stock sets error message
            errState = ERROR_POS_STOCK;
            this->i_quantity = 0;
        }
        else {
            this->i_quantity -= quantity;
        }
        return this->i_quantity;
    }


    Item::operator bool() const {                               //Returns true when there is no error
        return !errState;
    }


    double& operator+=(double& lhs, const Item& rhs) {          //Addes total price to the lhs value
        lhs += rhs.cost() * rhs.i_quantity;
        return lhs;
    }

    Item& Item::displayType(int pos) {                          //Sets display type to given parameter
        i_displayType = pos;
        return *this;
    }

    double Item::cost() const {                                 //Returns the cost of a single item
        double ret = this->price;                               //Add tax if necessary
        if (this->taxed) {
            ret *= (1 + TAX);
        }
        return ret;
    }

    int Item::quantity() const {                                //Returns the quantity of an item
        return i_quantity;
    }

    Item& Item::clear() {                                       //Clear the error state
        this->errState.clear();
        return *this;
    }


    ostream& Item::write(std::ostream& os) const {              //Print item in format(list or form)
        char buffer[21];                                        //Create variable to limit print length of name to 20
        if (name != nullptr) {
            strncpy(buffer, name, 20);
            buffer[20] = '\0';
        }
        else {
            buffer[0] = '\0';
        }
        os.fill(' ');
        if (errState) {
            os << errState << endl;                                     //If error exists, print error
        }
        else if (i_displayType == POS_LIST) {                   //Else format print for List
            os << " "<<setw(MAX_SKU_LEN) << left << sku << '|'
                << setw(20) << left << buffer << '|'
                << setw(7) << right << fixed << setprecision(2) << price << '|'
                << ' ' << (taxed ? 'X' : ' ') << " |"
                << setw(4) << right << i_quantity << '|'
                << setw(9) << right << fixed << setprecision(2) << cost()*i_quantity << '|';
        }
        else if (i_displayType == POS_FORM) {                   //Format print for Form
            os << "=============v"<<endl;
            os << setw(13) << left << "Name:" << buffer << endl
               << setw(13) << "Sku: " << sku << endl
                << setw(13) << "Price: " << fixed << setprecision(2) << price << endl;
            if (taxed) {
                os << setw(13) << "Price + tax: " << fixed << setprecision(2) << cost() << endl;
            }
            else {
                os << setw(13) << "Price + tax: " << "N/A" << endl;
            }
            os << setw(13) << "Stock Qty: "  << i_quantity << endl;
        }
        os << left;
        return os;
    }

    std::ofstream& Item::save(std::ofstream& file) const {                  //Save item to a file
        if (errState) {                                                     //Save error message in case of error
            cerr << errState;
        }   
        else {
            stringstream ss;                                                //Format into a string and add to file
            ss << itemType() <<"," << sku << "," << name << "," << fixed << setprecision(2) << price << "," << taxed << "," << i_quantity;
            file << ss.str();
        }
        return file;
    }

    std::istream& Item::read(std::istream& is) {                            //Read input values
        errState.clear();

        char taxedInput;
        double priceInput;
        int qtyInput;
        std::string input;
        bool flag = true;

        std::cout << "Sku\n> ";
        do {
            std::getline(is, input);                                //Get sku from input
            if (input.length() > MAX_SKU_LEN) {                     //If input is larger than max length, set error
                errState = ERROR_POS_SKU;
                std::cout << errState <<"\n"<<"> ";
            }
            else {
                errState.clear();
                strcpy(sku, input.c_str());
                flag = false;
            }
        } while (flag);
        flag = true;


        std::cout << "Name\n> ";
        do {
            std::getline(is, input);                                //Get name from input
            if (input.length() > MAX_NAME_LEN) {                    //Error if overflow
                errState = ERROR_POS_NAME;
                std::cout << errState << "\n" << "> ";
            }
            else {
                errState.clear();
                if (name != nullptr) {
                    delete[] name;
                }
                name = new char[MAX_NAME_LEN + 1];
                strcpy(name, input.c_str());
                flag = false;
            }
        } while (flag);
        flag = true;

        std::cout << "Price\n> ";
        do {
            is >> priceInput;
            if (priceInput < 0 || is.fail()) {                      //If input is less than 0 or not an integer, set error
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                errState = ERROR_POS_PRICE;
                std::cout << errState << "\n" << "> ";
            }
            else {
                errState.clear();
                price = priceInput;
                flag = false;
            }
        } while (flag);
        flag = true;


        std::cout << "Taxed?\n(Y)es/(N)o: ";
        do {
            is >> taxedInput;
            if (is.fail() || (taxedInput != 'y' && taxedInput != 'n')) {    //Validate input
                std::cin.clear();                                           //Clear buffer as taxedInput is a single char
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                errState = "Only 'y' and 'n' are acceptable: ";
                std::cout << errState;
            }
            else {
                errState.clear();
                taxed = (taxedInput == 'y');
                flag = false;
            }
        } while (flag);
        flag = true;


        std::cout << "Quantity\n> ";
        do {
            is >> qtyInput;
            if (qtyInput <= 0 || is.fail() || qtyInput >= 100) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                errState = ERROR_POS_QTY;
                std::cout << errState << "\n" << "> ";
            }
            else {
                errState.clear();
                i_quantity = qtyInput;
                flag = false;
            }
        } while (flag);

        return is;
    }

    ifstream& Item::load(std::ifstream& ifs) {
        errState.clear();
        std::string line;
        int inputQuant;

        std::getline(ifs, line, ',');                       //Read line up to a comma
        if (ifs.fail() || line.length() > MAX_SKU_LEN) {    //Validate
            errState = ERROR_POS_SKU;
            return ifs;
        }
        else {
            strcpy(sku, line.c_str());
        }

        std::getline(ifs, line, ',');
        if (ifs.fail() || line.length() > MAX_NAME_LEN) {
            errState = ERROR_POS_NAME;
            return ifs;
        }
        else {
            if (name != nullptr) {
                delete[] name;
            }
            name = new char[line.length() + 1];
            strcpy(name, line.c_str());

        }

        std::getline(ifs, line, ',');
        if (ifs.fail() || stod(line) < 0) {
            errState = ERROR_POS_PRICE;
            return ifs;
        }
        else {
            price = stod(line);
        }

        std::getline(ifs, line, ',');
        if (ifs.fail() || (stoi(line) != 0 && stoi(line) != 1)) {
            errState = ERROR_POS_TAX;
            return ifs;
        }
        else {
            taxed = stoi(line);
        }

        ifs >> inputQuant;
        if (ifs.fail() || inputQuant <= 0 || inputQuant >= 100) {
            errState = ERROR_POS_QTY;
            return ifs;
        }
        else {
            i_quantity = inputQuant;
        }

        return ifs;
    }

    std::ostream& Item::bprint(std::ostream& os) const {
        char buffer[21];                            //Create buffer to shorten name to 20 char
        if (name != nullptr) {
            strncpy(buffer, name, 20);
            buffer[20] = '\0';
        }
        else {
            buffer[0] = '\0';
        }
        os                                          //Format print
            << "| " << setw(20) << left << buffer << "|"
            << setw(10) << right << fixed << setprecision(2) << (taxed ? price*(1+TAX) : price) << " |"
            << "  " << (taxed ? 'T' : ' ') << "  |" << endl;

        return os;
    }

}