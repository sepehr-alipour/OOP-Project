/* ------------------------------------------------------
Projcet MS4
Module: N/A
Filename: Date.h
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
#ifndef DATE_H
#define DATE_H
#include "Status.h"
namespace sdds {
	class Date {
		int m_year;
		int m_month;
		int m_day;
		Status m_state;
		bool m_formatted;

	public:
		const int maximumYear = 2030;
		Date();
		Date(const int year, const int month, const int day);
		bool validate();
		int uniqDate(Date& date);

		Status& state() const;
		Date& formatted(bool isFormatted);
		operator bool() const;
		std::ostream& write(std::ostream& os)const;
		std::istream& read(std::istream& is);
		Date& operator=(const Date& status);

		friend bool operator ==(Date& firsDate, Date& secDate);
		friend bool operator >=(Date& firsDate, Date& secDate);
		friend bool operator <=(Date& firsDate, Date& secDate);
		friend bool operator <(Date& firsDate, Date& secDate);
		friend bool operator >(Date& firsDate, Date& secDate);
		friend bool operator !=(Date& firsDate, Date& secDate);


	};
	std::ostream& operator<<(std::ostream& ostr, const Date& name);
	std::istream& operator>>(std::istream& istr, Date& name);

}

#endif // !SDDS_UTILS_H
