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

#include "PosIO.h"

namespace sdds {

    //Operator << prints to ostream using write functions
    std::ostream& operator<<(std::ostream& os, const PosIO& pos) {
        return pos.write(os);
    }

    //Operator << writes into files using save function
    std::ofstream& operator<<(std::ofstream& ofs, const PosIO& pos) {
        return pos.save(ofs);
    }

    //Operator >> reads in values from istream using read function
    std::istream& operator>>(std::istream& is, PosIO& pos) {
        return pos.read(is);
    }

    //Operator >> reads in values from files using load function
    std::ifstream& operator>>(std::ifstream& ifs, PosIO& pos) {
        return pos.load(ifs);
    }
}