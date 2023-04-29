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

#ifndef POSIO_H_SDDS_
#define POSIO_H_SDDS_

#include <iostream>
#include <fstream>

namespace sdds {
    class PosIO {
    public:
        //Create Virtual functions as base class
        virtual std::ostream& write(std::ostream& os) const = 0;
        virtual std::istream& read(std::istream& is) = 0;
        virtual std::ofstream& save(std::ofstream& ofs) const = 0;
        virtual std::ifstream& load(std::ifstream& ifs) = 0;
        virtual ~PosIO() {}

        //Overload operators that uses above functions
        friend std::ostream& operator<<(std::ostream& os, const PosIO& pos);
        friend std::ofstream& operator<<(std::ofstream& ofs, const PosIO& pos);
        friend std::istream& operator>>(std::istream& is, PosIO& pos);
        friend std::ifstream& operator>>(std::ifstream& ifs, PosIO& pos);
    };
}

#endif // POSIO_H
