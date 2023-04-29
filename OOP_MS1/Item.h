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

#ifndef SDDS_ITEM_H_
#define SDDS_ITEM_H_
#include "POS.h"
#include "Error.h"
#include "PosIO.h"

namespace sdds {
    class Item : public PosIO{
        char sku[MAX_SKU_LEN + 1];          //C-string used to store SKU value
        char* name;                         //Dynamic memory to store name of the item
        double price;                       //Store item price
        bool taxed;                         //Store Taxability
        int i_quantity;                     //Store quantity of the item
    protected:
        int i_displayType;                  //Stores item display type(list or form)
        Error errState;                     //Stores error state of the object
    public:
        Item();                             //0 parameter constructor
        Item(const Item& other);            //Copy constructor
        ~Item();                            //Destructor for freeing dynamic memory

        //Operator overloads
        Item& operator=(const Item& other);
        bool operator== (const char* sku) const;
        bool operator>(const Item& other) const;
        int operator+=(int quantity);
        int operator-=(int quantity);
        operator bool() const;
        friend double& operator+=(double& lhs, const Item& rhs);

        virtual char itemType() const = 0;

        //Member functions
        Item& displayType(int pos);
        double cost() const;
        int quantity() const;
        Item& clear();

        //Override virtual functions of base class
        std::ostream& write(std::ostream& os) const;
        std::ofstream& save(std::ofstream& file) const;
        std::istream& read(std::istream& is);
        std::ifstream& load(std::ifstream& file);

        //Formatted print of item
        std::ostream& bprint(std::ostream& os) const;
    };
}

#endif // !SDDS_ITEM_H_
