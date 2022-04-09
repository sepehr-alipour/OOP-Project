/* ------------------------------------------------------
Projcet MS5
Module: N/A
Filename:  AidMan.h
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

#ifndef AIDMAN_H
#define AIDMAN_H
#include "Menu.h"
namespace sdds {

	class AidMan {
		Menu m_menu;
		char* m_fileName{};
		int menu();
	public:
		~AidMan();
		AidMan();
		void run();
		AidMan& operator=(const AidMan& menu) = delete;
		AidMan(const AidMan& menu) = delete;
	};
}

#endif
