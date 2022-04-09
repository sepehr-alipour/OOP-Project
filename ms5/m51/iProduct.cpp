
/* ------------------------------------------------------
Projcet MS4
Module: N/A
Filename: iProduct.cpp
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



#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Utils.h"
#include "Status.h"
#include "iProduct.h"
using namespace std;
namespace sdds {

	istream& operator>>(istream& istr, iProduct& iProduct)
	{
		iProduct.read(istr);
		return istr;
	}

	ostream& operator<<(ostream& ostr, iProduct& iProduct)
	{
		iProduct.display(ostr);
		return ostr;
	}


}