/* ------------------------------------------------------
Projcet MS1
Module: N/A
Filename: Status.cpp
Version 1
Author	Sepehr Alipour
Email   salipour2@myseneca.ca
StudentID 107296212
Revision History
-----------------------------------------------------------
Date       13/03/2022
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include "Status.h"
#include "Utils.h"
using namespace std;
namespace sdds {
	Utils utils;
	Status::Status(char* errorDesc) {
		if (errorDesc) {
			utils.alocpy(m_errorDesc, errorDesc);
		}
		else {
			m_errorDesc = nullptr;
		}
		m_statusCode = 0;

	}
	Status::Status(const Status& status) {

		//if (status.operator bool()) {
		//	clear();
		*this = status;
		//}



	}
	Status::Status() {
		Status(nullptr);

	}

	Status& Status::clear() {

		delete[] m_errorDesc;
		m_errorDesc = nullptr;
		m_statusCode = 0;
		return *this;
	}

	std::ostream& operator<<(std::ostream& ostr, const Status& status) {
		if (status.operator int() != 0)
			ostr << "ERR#" << status.operator int() << ": ";
		ostr << status.operator char* ();
		return ostr;
	}
	Status::operator bool() const {
		if (m_errorDesc == nullptr)
			return true;
		return false;
	}

	Status:: operator char* () const {
		return (char*)m_errorDesc;
	}
	Status:: operator int() const {
		return m_statusCode;
	}
	Status& Status::operator=(const Status& status) {


		if (&status != this) {
			m_errorDesc = nullptr;
			utils.alocpy(m_errorDesc, status.m_errorDesc);
			m_statusCode = status.m_statusCode;
			//Status
		}

		return *this;

	}
	Status& Status::operator=(const char* desc) {
		if (desc)
		{
			ut.alocpy(m_errorDesc, desc);
		}
		return *this;

	}
	Status& Status::operator=(const int statusCode) {

		m_statusCode = statusCode;
		return *this;

	}




}