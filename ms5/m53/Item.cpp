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
using namespace std;
namespace sdds {

	Item::~Item() {
		delete[] m_description;
		m_description = nullptr;
	}
	Item::Item() {
		m_price = 0;
		m_qty = 0;
		m_qtyNeeded = 0;
		m_stockNumber = 0;
		m_description = nullptr;
		isLinear = false;

	}
	Item::Item(const Item& item) {
		(*this) = (item);
	}

	void Item::clear() {
		m_status = true;
	}
	ostream& Item::display(std::ostream& ostr)const {
		if (!m_status)
		{
			ostr << m_status;
		}
		else if (linear())
		{
			ostr << m_stockNumber << " | ";
			string description = m_description;
			if (strlen(m_description) > 35)
			{
				description = description.substr(0, 35);

			}
			



			ostr << setw(36) << setfill(' ') << left << description
				<< "|" << right << setw(5) << setfill(' ') << m_qty
				<< " |" << right << setw(5) << setfill(' ') << m_qtyNeeded
				<< setw(2) << "|" << right << setw(8) << setfill(' ') << m_price
				<< " |";


		}
		else
		{
			ostr << "AMA Item:" << endl;
			ostr << m_stockNumber << ": " << m_description << endl;
			ostr << "Quantity Needed: " << m_qtyNeeded << endl;
			ostr << "Quantity Available: " << m_qty << endl;
			ostr << "Unit Price: $" << fixed << setprecision(2) << m_price << endl;
			ostr << "Needed Purchase Fund: $" << (m_qtyNeeded - m_qty) * m_price << endl;
		}

		return ostr;
	}

	void Item::linear(bool isLinear) {
		this->isLinear = isLinear;
	}

	bool Item::linear() const {
		return isLinear;
	}

	ifstream& Item::load(ifstream& ifstr) {

		char description[1000] = {};

		delete[] m_description;
		m_description = nullptr;
		if (ifstr.fail()) {
			m_status = "Input file stream read failed!";
		}
		else
		{
			ifstr >> m_stockNumber;
			ifstr.ignore();
			ifstr.getline(description, 1000, '\t');
			ut.alocpy(m_description, description);
			ifstr >> m_qty;
			ifstr.ignore();
			ifstr >> m_qtyNeeded;
			ifstr.ignore();

			ifstr >> m_price;
			ifstr.ignore();

		}

		return ifstr;
	}

	Item::operator bool()const {
		return m_status;
	}
	Item::operator double()const {
		return m_price;
	}
	int Item::operator+=(int qty) {
		m_qty += qty;
		return m_qty;
	}
	Item& Item::operator=(const Item& item) {
		m_description = nullptr;
		if (&item != this && m_description != item.m_description && item.m_description != nullptr) {
			ut.alocpy(m_description, item.m_description);
			m_price = item.m_price;
			m_qty = item.m_qty;
			m_stockNumber = item.m_stockNumber;
			m_qtyNeeded = item.m_qtyNeeded;
			isLinear = item.isLinear;
		}

		return *this;
	}

	int Item::operator-=(int qty) {
		m_qty -= qty;
		return m_qty;
	}
	bool Item::operator==(int sku)const {
		return m_stockNumber == sku;
	}
	bool Item::operator==(const char* description)const {

		if (!description || !m_description)
			return false;
		string key = description;
		string descStr = m_description;
		if (descStr.find(key) != string::npos)
			return true;
		else return false;


	}
	int Item::qty() const {
		return m_qty;
	}
	int Item::qtyNeeded() const {
		return m_qtyNeeded;
	}

	istream& Item::read(std::istream& istr) {
		string desc;
		delete[] m_description;
		m_description = nullptr;
		m_status.clear();

		cout << "AMA Item:" << endl;
		cout << "SKU: " << m_stockNumber;
		cout << endl;
		cout << "Description: ";

		istr.ignore(1000, '\n');
		getline(istr, desc);
		ut.alocpy(m_description, desc.c_str());
		istr.clear();


		cout << "Quantity Needed: ";
		do
		{
			istr >> m_qtyNeeded;
			if (!istr)
			{
				cout << "Invalid Integer, retry: ";
				istr.clear();
				istr.ignore(1000, '\n');
				m_qtyNeeded = -1;
			}
			else if (m_qtyNeeded < 1 || m_qtyNeeded > 9999)
			{
				cout << "Value out of range [1<=val<=9999]: ";
				istr.clear();
				istr.ignore(1000, '\n');
			}


		} while (m_qtyNeeded < 1 || m_qtyNeeded > 99999);

		cout << "Quantity On Hand: ";
		do
		{
			istr >> m_qty;

			if (!istr)
			{
				cout << "Invalid Integer, retry: ";
				istr.clear();
				istr.ignore(1000, '\n');
				m_qty = -1;
			}
			else if (m_qty < 0 || m_qty > m_qtyNeeded)
			{
				cout << "Value out of range [0<=val<=" << m_qtyNeeded << "]: ";
				istr.clear();
				istr.ignore(1000, '\n');
			}


		} while (m_qty < 0 || m_qty > m_qtyNeeded);

		cout << "Unit Price: $";
		do
		{
			istr >> m_price;
			if (!istr)
			{
				cout << "Invalid number, retry: ";
				istr.clear();
				istr.ignore(1000, '\n');
				m_price = -1;
			}
			else if (m_price < 0 || m_price > 9999)
			{
				cout << "Value out of range [0.00<=val<=9999.00]: ";
			}


		} while (m_price < 0 || m_price > 9999);

		return istr;
	}



	int Item::readSku(istream& istr) {
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
			else if (40000 > m_stockNumber || m_stockNumber > 99999)
			{
				cout << "Value out of range [40000<=val<=99999]: ";
				istr.clear();
				istr.ignore(1000, '\n');

			}

		} while (40000 > m_stockNumber || m_stockNumber > 99999 || !istr);

		return m_stockNumber;
	}

	ofstream& Item::save(std::ofstream& ofstr)const {
		if (m_status)
		{
			ofstr
				<< m_stockNumber << "\t"
				<< m_description << "\t"
				<< m_qty << "\t"
				<< m_qtyNeeded << "\t"
				<< m_price;
		}
		return ofstr;
	}

	istream& operator>>(istream& istr, Item& item)
	{
		item.read(istr);
		return istr;
	}

	ostream& operator<<(ostream& ostr, Item& item)
	{
		item.display(ostr);
		return ostr;
	}

}
