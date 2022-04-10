/* ------------------------------------------------------
Projcet MS5
Module: N/A
Filename: Status.h
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
#ifndef STATUS_H
#define STATUS_H
namespace sdds {

    class Status {
        int m_statusCode;
        char* m_errorDesc{};
    public:
        ~Status();

        Status();
        Status(char* errorDesc);
        Status(const Status& status);

        Status& clear();
        operator bool() const;
        operator char* () const;
        operator int() const;
        Status& operator=(const Status& status);
        Status& operator=(const char* desc);
        Status& operator=(const int statusCode);

    };
    std::ostream& operator<<(std::ostream& ostr, const Status& status);
}

#endif 
