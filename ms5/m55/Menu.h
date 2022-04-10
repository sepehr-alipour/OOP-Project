/* ------------------------------------------------------
Projcet MS5
Module: N/A
Filename:  Menu.h
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

#ifndef MENU_H
#define MENU_H
namespace sdds {

	class Menu {
		int m_availableOptions;
		char* m_optionList{};
	public:
		Menu(const char* menuContent, int optionNumbers);
		int run()const;
		Menu();
		~Menu();
		Menu& operator=(const Menu& menu) = delete;
		Menu(const Menu& menu) = delete;
		void setOptions(const char* menuContent, int optionNumbers);
	};
}

#endif
