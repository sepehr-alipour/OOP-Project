/* ------------------------------------------------------
Projcet MS3
Module: N/A
Filename: Item.cpp
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
	}
	Item::Item() {
		m_price = 0;
		m_qty = 0;
		m_qtyNeeded = 0;
		m_stockNumber = 0;
		m_description = nullptr;
		isLinear = false;

	}
	void Item::clear() {
		m_status = true;
	}
	ostream& Item::display(std::ostream& ostr)const {
		if (!m_status.operator bool())
		{
			ostr << m_status;
		}
		else if (isLinear)
		{
			ostr << m_stockNumber << " | ";

			if (strlen(m_description) > 35)
			{

				int i;
				for (i = 0; i < 35; i++)
					ostr << m_description[i];

				ostr << " |  "
					<< m_qty << " | "
					<< m_qtyNeeded << " |  "
					<< m_price << " |";
			}
			else
			{

				ostr << setw(36) << left << m_description
					<< "|" << right << setw(5) << m_qty
					<< " |" << right << setw(5) << m_qtyNeeded
					<< setw(2) << "|" << right << setw(8) << m_price
					<< " |";
			}

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

	bool Item::linear() {
		return isLinear;
	}

	ifstream& Item::load(ifstream& ifstr) {
		string desc;
		delete[] m_description;
		m_description = nullptr;

		if (!m_status.operator bool())
			ut.alocpy(m_description, "Input file stream read failed!");


		ifstr >> m_stockNumber;
		getline(ifstr, desc, '\t');
		getline(ifstr, desc, '\t');
		ut.alocpy(m_description, desc.c_str());
		ifstr >> m_qty;
		ifstr >> m_qtyNeeded;
		ifstr >> m_price;

		return ifstr;
	}


	Item::operator bool()const {
		return m_status.operator bool();
	}
	Item::operator double()const {
		return m_price;
	}
	int Item::operator+=(int qty) {
		m_qty += qty;
		return m_qty;
	}
	Item& Item::operator=(const Item& item) {
		if (&item != this) {
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
		if (descStr.find(key)!=string::npos)
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
		istr >> desc;
		ut.alocpy(m_description, desc.c_str());

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


		} while (m_qtyNeeded < 1 || m_qtyNeeded > 99999 );

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


		} while (m_qty < 0 || m_qty > m_qtyNeeded );

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
		if (m_status.operator bool())
		{
			ofstr << endl
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
