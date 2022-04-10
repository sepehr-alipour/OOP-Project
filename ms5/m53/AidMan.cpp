/* ------------------------------------------------------
Projcet MS5
Module: N/A
Filename: AidMan.cpp
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
#include <iostream>
#include <iomanip>

#include <ctime>
#include <fstream>
#include "AidMan.h"
#include "Utils.h"
#include "Date.h"
#include "Perishable.h"

using namespace std;
namespace sdds {
	template<typename Base, typename T>
	inline bool instanceof(const T*) {
		return std::is_base_of<Base, T>::value;
	}
	int AidMan::menu() {
		int year, month, day;
		ut.getSystemDate(&year, &month, &day);

		cout << "Aid Management System" << endl;
		cout << "Date: ";
		cout << year;
		cout << "/";
		if (month < 10)
			cout << "0";
		cout << month;
		cout << "/";
		cout << day << endl;
		cout << "Data file: " << (!m_fileName ? "No file" : m_fileName) << endl;
		cout << "---------------------------------" << endl;


		return m_menu.run();

	}

	AidMan::AidMan() {
		m_fileName = nullptr;
		m_menu.setOptions("1- List Items\n"
			"2- Add Item\n"
			"3- Remove Item\n"
			"4- Update Quantity\n"
			"5- Sort\n"
			"6- Ship Items\n"
			"7- New/Open Aid Database\n"
			"---------------------------------", 7);

	}
	void AidMan::deallocate() {


		for (int i = 0; i < m_product_length; i++)
		{
			delete m_products[i];

		}
		m_product_length = 0;

	}
	AidMan::~AidMan() {
		delete[] m_fileName;
		m_fileName = nullptr;

		for (int i = 0; i < m_product_length; i++)
		{
			delete m_products[i];

		}
		m_product_length = 0;
	}

	void AidMan::run() {
		int option;
		int listItems;
		int rowItem = 0;
		Menu addMenu;

		do {
			option = menu();
			if (option != 0 && option != 7 && !m_fileName)
				option = 7;
			switch (option)
			{
			case 1:
				if (m_product_length > 0) {
					cout << endl << "****List Items****" << endl;

					listItems = list();

					if (listItems > 1) {
						cout << "Enter row number to display details or <ENTER> to continue:" << endl;
						cout << "> ";
						cin.ignore(1000, '\n');
						rowItem = cin.get();
						if (rowItem == '\n') {
							cout << endl;
							break;
						}
						rowItem -= 48;
						if (rowItem > m_product_length || rowItem == 0)
						{
							cout << "The list is emtpy!" << endl;
							break;
						}

						m_products[rowItem - 1]->linear(false);
						cout << *m_products[rowItem - 1] << endl;
					}
				}
				else {
					cout << "The list is emtpy!" << endl;
				}

				break;
			case 2:
				cout << endl << "****Add Item****" << endl;
				if (m_product_length == sdds_max_num_items)
				{
					cout << "Database full!";
					break;
				}
				int option;
				addMenu.setOptions("1- Perishable\n2- Non-Perishable\n-----------------", 2);
				option = addMenu.run();
				iProduct* product;
				int sku;
				if (option == 1)
				{
					product = new Perishable;

				}
				else if (option == 2) {
					product = new Item;

				}

				else {
					cout << "Aborted\n";
					break;
				}

				sku = product->readSku(cin);
				if (search(sku) != -1) {
					cout << "Sku: " << sku << " is already in the system, try updating quantity instead." << endl << endl;
					delete product;
				}
				else {
					cin >> *product;
					cout << endl;
					if (product) {
						m_products[m_product_length] = product;
						m_product_length += 1;
					}
				}

				break;
			case 3:
				cout << endl << "****Remove Item****" << endl << endl;
				break;
			case 4:
				cout << endl << "****Update Quantity****" << endl << endl;
				break;
			case 5:
				cout << endl << "****Sort****" << endl << endl;
				break;
			case 6:
				cout << endl << "****Ship Items****" << endl << endl;
				break;
			case 7:
				cout << endl << "****New/Open Aid Database****" << endl;
				cout << "Enter file name: ";
				string filename;
				cin >> filename;
				ut.alocpy(m_fileName, filename.c_str());
				if (load() > 0)
					cout << m_product_length << " records loaded!" << endl << endl;
				break;

			}
		} while (option != 0);
		save();
		cout << "Exiting Program!" << endl;
	}

	void AidMan::save()
	{
		if (m_fileName && m_product_length > 0) {
			ofstream ofstr;
			ofstr.open(m_fileName, ios::out);

			for (int i = 0; i < m_product_length; i++)
			{
				m_products[i]->save(ofstr);
				ofstr << endl;

			}
			ofstr.close();
		}

	}
	bool AidMan::load()
	{
		int option;

		save();
		deallocate();
		ifstream ifstr;
		ifstr.open(m_fileName, ios::in);
		if (ifstr.fail()) {

			Menu confirmMenu;
			cout << "Failed to open FN for reading!" << endl
				<< "Would you like to create a new data file?" << endl;
			confirmMenu.setOptions("1- Yes!", 1);

			option = confirmMenu.run();
			if (option == 1)
			{
				cout << "new data file: " << m_fileName;
				save();

			}
			else {
				deallocate();
				delete[] m_fileName;
				m_fileName = nullptr;
				return false;
			}


		}
		else {
			while (!ifstr.fail()) {
				int sku;
				sku = ifstr.peek() - 48;

				if (sku < 4 && sku >0)
				{
					m_products[m_product_length] = new Perishable;

				}
				else if (sku < 10 && sku >3) {

					m_products[m_product_length] = new Item;
				}
				else {
					ifstr.setstate(ios::failbit);
					continue;
				}
				if (m_products[m_product_length]) {
					m_products[m_product_length]->load(ifstr);
					m_product_length += 1;
				}
			}

		}
		if (m_product_length > 0)
			return true;
		return false;

	}

	int AidMan::list(const char* sub_desc)
	{
		cout << setw(5) << left << " ROW " << "|"
			<< "  SKU  "
			<< "|" << left << setw(37) << setfill(' ') << " Description"
			<< "|" << " Have "
			<< "|" << " Need "
			<< "|" << "  Price  "
			<< "|" << " Expiry"
			<< endl;
		cout << right << setw(6) << setfill('-') << "+"
			<< right << setw(8) << setfill('-') << "+"
			<< right << setw(38) << setfill('-') << "+"
			<< right << setw(7) << setfill('-') << "+"
			<< right << setw(7) << setfill('-') << "+"
			<< right << setw(10) << setfill('-') << "+"
			<< right << setw(11) << setfill('-') << "" << endl;
		if (sub_desc)
		{
			int i, counter = 0;
			for (i = 0; i < m_product_length; i++)
			{
				if (m_products[i]->operator == (sub_desc))
				{
					if (m_products[i]->operator==(sub_desc))
						m_products[i]->linear(true);
					counter += 1;
				}

			}

			return counter;
		}
		else
		{
			int i;
			for (i = 0; i < m_product_length; i++)
			{
				m_products[i]->linear(true);
				cout << right << setw(4) << setfill(' ') << i + 1 << " | " << *m_products[i] << endl;

			}

		}

		cout << right << setw(6) << setfill('-') << "+"
			<< right << setw(8) << setfill('-') << "+"
			<< right << setw(38) << setfill('-') << "+"
			<< right << setw(7) << setfill('-') << "+"
			<< right << setw(7) << setfill('-') << "+"
			<< right << setw(10) << setfill('-') << "+"
			<< right << setw(11) << setfill('-') << "" << endl;
		return m_product_length;

	}

	int AidMan::search(int sku) const {
		for (int i = 0; i < m_product_length; i++)
		{
			if (m_products[i]->operator==(sku))
				return i;
		}
		return -1;
	}



}