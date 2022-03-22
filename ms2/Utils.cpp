#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <string.h>
#include "Utils.h"
using namespace std;
namespace sdds {
	Utils ut;
	void Utils::testMode(bool testmode) {
		m_testMode = testmode;
	}
	void Utils::getSystemDate(int* year, int* mon, int* day) {
		if (m_testMode) {
			if (day) *day = sdds_testDay;
			if (mon) *mon = sdds_testMon;
			if (year) *year = sdds_testYear;
		}
		else {
			time_t t = std::time(NULL);
			tm lt = *localtime(&t);
			if (day) *day = lt.tm_mday;
			if (mon) *mon = lt.tm_mon + 1;
			if (year) *year = lt.tm_year + 1900;
		}
	}
	int Utils::daysOfMon(int month, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int mon = (month >= 1 && month <= 12 ? month : 13) - 1;
		return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	void Utils::alocpy(char*& destination, const char* source) {


		if (source) {
			delete[] destination;
			destination = nullptr;
			destination = new (nothrow) char[strlen(source) + 1];
			strcpy(destination, source);
		}
	}

	int Utils::getint(const char* prompt) {
		int digit;
		if (prompt)
			cout << prompt;
		while (true)
		{
			cin >> digit;
			if (!cin)
			{
				cout << "Invalid Integer, retry: ";
				cin.clear();
				cin.ignore(1000, '\n');
				continue;
			}
			else
				break;
		}
		return digit;

	}
	int Utils::getint(int min, int max, const char* prompt, const char* errMes) {
		int digit;
		bool promptLoaded=false;
		while (true) {
			if (promptLoaded)
				prompt = nullptr;
			digit = getint(prompt);
			promptLoaded = true;

			if (digit<min || digit>max)
			{
				/*if (errMes) {
					cout << errMes << ", retry: ";
				}
				else {*/
					cout << "Value out of range [" << min << "<=val" << "<=" << max << "]: " ;
				//}
			}
			else
				break;
		}
		return digit;
	}




}