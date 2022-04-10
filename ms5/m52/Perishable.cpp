/* ------------------------------------------------------
Projcet MS5
Module: N/A
Filename: Item.cpp
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

#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <string.h>

#include <iostream>
#include <fstream>
#include <iomanip>

#include "Utils.h"
#include "Item.h"
#include "Perishable.h"

using namespace std;
namespace sdds {
	Perishable::Perishable() {
		m_instruction = nullptr;
	}
	const Date& Perishable::expiry()const {
		return m_expiryDate;
	}

	Perishable& Perishable::operator=(const Perishable& item) {
		if (&item != this) {

			ut.alocpy(m_instruction, item.m_instruction);
			m_expiryDate = item.m_expiryDate;
			Item::operator=(item);


		}

		return *this;
	}
	Perishable::~Perishable() {
		delete[] m_instruction;
		m_instruction = nullptr;

	}
	int Perishable::readSku(istream& istr) {
		cout << "SKU: ";

		do
		{
			istr >> m_stockNumber;
			if (!istr)
			{
				cout << "Invalid Integer, retry: ";
				istr.clear();
				istr.ignore(1000, '\n');
			}
			else if (10000 > m_stockNumber || m_stockNumber > 39999)
			{
				cout << "Value out of range [10000<=val<=39999]: ";
				istr.clear();
				istr.ignore(1000, '\n');

			}

		} while (10000 > m_stockNumber || m_stockNumber > 39999 || !istr);

		return m_stockNumber;
	}

	ofstream& Perishable::save(std::ofstream& ofstr) const {
		if (m_status)
		{

			Date expiryDate = m_expiryDate;
			Item::save(ofstr);
			ofstr << "\t";
			if (m_instruction)
				ofstr << m_instruction;
			ofstr << expiryDate.formatted(false);

		}
		return ofstr;
	}
	ifstream& Perishable::load(ifstream& ifstr) {
		char instruction[1000] = {};

		Item::load(ifstr);

		delete[] m_instruction;
		m_instruction = nullptr;
		if (ifstr.fail()) {
			m_status = "Input file stream read (perishable) failed!";
		}
		else
		{
			ifstr.getline(instruction, 1000, '\t');
			ut.alocpy(m_instruction, instruction);
			ifstr >> m_expiryDate;
			ifstr.ignore();
		}
		return ifstr;

	}
	Perishable::Perishable(const Perishable& perishable) :Item(perishable) {
		if (m_status) {
			m_instruction = nullptr;

			(*this) = (perishable);
		}
	}
	Perishable::operator bool() const {
		if (m_stockNumber <= 39999 && m_stockNumber >= 10000)
			return true;
		return false;
	}
	istream& Perishable::read(std::istream& istr) {
		string desc;


		Item::read(istr);
		delete[] m_instruction;
		m_instruction = nullptr;


		cout << "Expiry date (YYMMDD): ";
		istr >> m_expiryDate;
		istr.ignore(1000, '\n');
		cout << "Handling Instructions, ENTER to skip: ";
		getline(istr, desc, '\n');
		ut.alocpy(m_instruction, desc.c_str());

		if (!m_status)
			m_status = "Input file stream read(perishable) failed!";


		return istr;
	}
	ostream& Perishable::display(std::ostream& ostr)const {
		if (!m_status)
		{
			ostr << m_status;
		}

		else if (linear())
		{
			Item::display(ostr);
			if (m_expiryDate && m_instruction && strcmp(m_instruction, "") != 0)
				ostr << "*";
			else ostr << " ";
			ostr << m_expiryDate;
		}
		else {
			ostr << "Perishable ";
			Item::display(ostr);
			ostr << "Expiry date: ";
			ostr << m_expiryDate;
			if (m_instruction && strcmp(m_instruction, "") != 0)
				ostr << endl << "Handling Instructions: " << m_instruction;

			ostr << endl;
		}


		return ostr;
	}


}