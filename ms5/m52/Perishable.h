/* ------------------------------------------------------
Projcet MS5
Module: N/A
Filename: Perishable.h
Version 1
Author	Sepehr Alipour
Email   salipour2@myseneca.ca
StudentID 107296212
Revision History
-----------------------------------------------------------
Date       04/09/2022
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
*/

#ifndef PERISHABLE_H
#define PERISHABLE_H
#include "Item.h"
#include "Date.h"
namespace sdds {

	class Perishable : public Item {
		Date m_expiryDate;
		char* m_instruction{};
	public:
		~Perishable();
		Perishable();
		Perishable(const Perishable& perishable);

		Perishable& operator=(const Perishable& item);
		
		ostream& display(std::ostream& ostr)const;
		ifstream& load(std::ifstream& ifstr);
		int readSku(istream& istr);
		ofstream& save(std::ofstream& ofstr)const;
		istream& read(std::istream& istr);
		operator bool() const;
		const Date& expiry()const;
	};
}
#endif