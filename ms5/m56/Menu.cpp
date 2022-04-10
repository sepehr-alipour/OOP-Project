/* ------------------------------------------------------
Projcet MS5
Module: N/A
Filename: Menu.cpp
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
#include "Menu.h"
#include "Utils.h"
using namespace std;
namespace sdds {
	Menu::Menu(const char* menuContent, int optionNumbers) {

		setOptions(menuContent, optionNumbers);
	}
	void Menu::setOptions(const char* menuContent, int optionNumbers) {

		if (menuContent || optionNumbers < 15) {
			ut.alocpy(m_optionList, menuContent);
			m_availableOptions = optionNumbers;
		}
		else {
			m_optionList = nullptr;
			m_availableOptions = 0;

		}
	}

	Menu::Menu() {}
	int Menu::run()const {
		cout << m_optionList << endl;
		cout << "0- Exit" << endl;
		int option = ut.getint(0, m_availableOptions, "> ", "Invalid Integer");
		return option;
	}

	Menu::~Menu()
	{
		delete[] m_optionList;
		m_optionList = nullptr;
	}
}