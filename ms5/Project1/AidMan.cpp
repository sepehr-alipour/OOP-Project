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
#include <ctime>
#include "AidMan.h"
#include "Utils.h"
#include "Date.h"
using namespace std;
namespace sdds {

	int AidMan::menu() {
		int year, month, day;
		ut.getSystemDate(&year, &month, &day);

		if (!m_fileName)
			ut.alocpy(m_fileName, "No file");

		cout << "Aid Management System Version 0.1" << endl;
		cout << "Date: ";
		cout << year;
		cout << "/";
		if (month < 10)
			cout << "0";
		cout << month;
		cout << "/";
		cout << day << endl;
		cout << "Data file: " << m_fileName << endl;
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
	AidMan::~AidMan() {
		delete[] m_fileName;
		m_fileName = nullptr;
	}

	void AidMan::run() {
		int option;
		do {
			option = menu();
			switch (option)
			{
			case 1:
				cout << endl << "****List Items****" << endl << endl;
				break;
			case 2:
				cout << endl << "****Add Item****" << endl << endl;
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
				cout << endl << "****New/Open Aid Database****" << endl << endl;
				break;

			default:
				break;
			}
		} while (option != 0);
		cout << "Exiting Program!" << endl;
	}





}