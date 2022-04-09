/* ------------------------------------------------------
Projcet MS5
Module: N/A
Filename: Date.cpp
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
#include "Date.h"
#include "Utils.h"
using namespace std;
namespace sdds {
	Utils utils;

	bool Date::validate() {
		if (m_year<2022 || m_year>maximumYear) {

			m_state = "Invalid year in date";
			m_state = 1;
			return false;


		}
		if (m_month < 1 || m_month>12) {
			m_state = "Invalid month in date";
			m_state = 2;
			return false;

		}
		if (m_day < 1 || m_day>utils.daysOfMon(m_month, m_year)) {
			m_state = "Invalid day in date";
			m_state = 3;
			return false;
		}
		else {

			m_state.clear();
			return true;
		}

	}
	int Date::uniqDate(Date& date) {
		return date.m_year * 372 + date.m_month * 31 + date.m_day;

	}
	Date::Date(const int year, const int month, const  int day) {
		m_year = year;
		m_month = month;
		m_day = day;
		m_formatted = true;

		validate();
	}
	Date::Date() {
		utils.testMode(true);
		utils.getSystemDate(&m_year, &m_month, &m_day);
		m_formatted = true;
		validate();
	}



	bool  operator ==(Date& firsDate, Date& secDate) {

		if (firsDate.uniqDate(firsDate) == firsDate.uniqDate(secDate))
			return true;

		return false;

	}
	bool  operator >=(Date& firsDate, Date& secDate) {

		if (firsDate.uniqDate(firsDate) >= firsDate.uniqDate(secDate))
			return true;

		return false;

	}
	bool  operator <=(Date& firsDate, Date& secDate) {

		if (firsDate.uniqDate(firsDate) <= firsDate.uniqDate(secDate))
			return true;

		return false;

	}
	bool  operator <(Date& firsDate, Date& secDate) {

		if (firsDate.uniqDate(firsDate) < firsDate.uniqDate(secDate))
			return true;

		return false;

	}
	bool  operator >(Date& firsDate, Date& secDate) {

		if (firsDate.uniqDate(firsDate) > firsDate.uniqDate(secDate))
			return true;

		return false;

	}
	bool  operator !=(Date& firsDate, Date& secDate) {

		if (firsDate.uniqDate(firsDate) != firsDate.uniqDate(secDate))
			return true;

		return false;

	}
	Status& Date::state() const {
		return (Status&)m_state;
	}
	Date& Date::formatted(bool isFormatted) {
		m_formatted = isFormatted;
		return *this;

	}

	Date::operator bool() const {
		if (m_state.operator bool())
			return true;
		return false;
	}

	std::ostream& Date::write(std::ostream& os)const {

		if (m_formatted) {

			os << m_year << "/";
			if (m_month < 10)
				os << "0";
			os << m_month;
			os << "/" << m_day;
		}
		else {
			os << m_year - 2000;
			if (m_month < 10)
				os << "0";
			os << m_month << m_day;
		}

		return os;
	}
	std::istream& Date::read(std::istream& is) {

		m_day = 0;
		m_month = 0;
		m_year = 0;
		int num;
		int year;
		int month;
		int day;


		is >> num;
		if (num == 0) {
			m_state = "Invalid date value";

			return is;
		}
		year = num / 10000;


		if (year == 0) {
			ut.getSystemDate(&year, 0, 0);
			num %= 10000;

			month = num / 100;
			day = num % 100;
		}
		else {
			num %= 10000;
			year += 2000;
			month = num / 100;
			day = num % 100;
		}

		m_day = day;
		m_month = month;
		m_year = year;
		if (!validate())
			is.setstate(ios::badbit);
		return is;
	}

	std::istream& operator>>(std::istream& istr, Date& name) {

		name.read(istr);
		return istr;

	}
	std::ostream& operator<<(std::ostream& ostr, const Date& date) {
		if (!date.operator bool())
			ostr << "Bad Name";
		else date.write(ostr);
		return ostr;
	}

	Date& Date::operator=(const Date& date) {


		if (date.operator bool()) {
			m_year = date.m_year;
			m_month = date.m_month;
			m_day = date.m_day;
		}

		return *this;

	}
}