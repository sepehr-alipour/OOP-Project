/* ------------------------------------------------------
Projcet MS4
Module: N/A
Filename:  iProduct.h
Version 1
Author	Sepehr Alipour
Email   salipour2@myseneca.ca
StudentID 107296212
Revision History
-----------------------------------------------------------
Date       04/06/2022
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
*/

#ifndef IPRODUCT_H
#define IPRODUCT_H
namespace sdds {

	class iProduct {
	public:
		// to read the Stock-Keeping Unit from console before
	// main data entry
		virtual int readSku(std::istream& istr) = 0;
		// to reduce the quantity on hand
		virtual int operator-=(int qty) = 0;
		// to increase the quantity on hand
		virtual int operator+=(int qty) = 0;
		// returns the price of the produce
		virtual operator double()const = 0;
		// returns if the iProduct is in a good state
		virtual operator bool()const = 0;
		// returns the number of products needed
		virtual int qtyNeeded()const = 0;
		// retuns the quantity on hand
		virtual int qty()const = 0;
		// determines if the iProduct is displayed in a linear format or 
		// descriptive format
		virtual void linear(bool isLinear) = 0;
		// saves the iProduct into a file
		virtual std::ofstream& save(std::ofstream& ofstr)const = 0;
		// loads an iProduct from a file
		virtual std::ifstream& load(std::ifstream& ifstr) = 0;
		// displays the iProduct on the screen
		virtual std::ostream& display(std::ostream& ostr)const = 0;
		// reads the iProduct from the console
		virtual std::istream& read(std::istream& istr) = 0;
		// return true if the sku is a match to the iProduct's sku
		virtual bool operator==(int sku)const = 0;
		// rtrns true if the description is found in the iPorduct's description
		virtual bool operator==(const char* description)const = 0;
		//destructor
		virtual ~iProduct() {};
	};

	std::istream& operator>>(std::istream& istr, iProduct& iProduct);
	std::ostream& operator<<(std::ostream& ostr, iProduct& iProduct);
}

#endif