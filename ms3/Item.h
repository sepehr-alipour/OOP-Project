/* ------------------------------------------------------
Projcet MS3
Module: N/A
Filename: Item.h
Version 1
Author	Sepehr Alipour
Email   salipour2@myseneca.ca
StudentID 107296212
Revision History
-----------------------------------------------------------
Date       04/01/2022
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
*/

#ifndef ITEM_H
#define ITEM_H
#include "iProduct.h"
#include "Status.h"
using namespace std;
namespace sdds {

	class Item : public iProduct {

		double m_price;
		int m_qty;
		int m_qtyNeeded;
		char* m_description;
		bool isLinear;

	protected:

		Status m_status; 
		int m_stockNumber;
		bool linear();

	public:
		~Item();
		Item();
		void clear();
		ostream& display(std::ostream& ostr)const;
		void linear(bool isLinear);
		ifstream& load(std::ifstream& ifstr);

		operator bool()const;
		operator double()const;
		int operator+=(int qty);
		Item& operator=(const Item& item);
		int operator-=(int qty);
		bool operator==(int sku)const;
		bool operator==(const char* description)const;

		int qty() const;
		int qtyNeeded() const;
		istream& read(std::istream& istr);
		int readSku(istream& istr);
		ofstream& save(std::ofstream& ofstr)const;



	};
	std::istream& operator>>(std::istream& istr, Item& item);
	std::ostream& operator<<(std::ostream& ostr, Item& item);
}
#endif