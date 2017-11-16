#include <iostream>
#include <string>

class DateImp {
    protected:
        int day;
        int month;
        int year;

    public:
        DateImp(int day, int month, int year) {
            this->day = day;
            this->month = month;
            this->year = year;
        }

        virtual void print() {
            std::cout << "Date is " << month << "." << day << "." << year << std::endl;
        }
};

class AmericanDateImp : public DateImp {
    public:
        AmericanDateImp(int day, int month, int year) : DateImp(day, month, year) {}

        void print() {
            std::cout << "Date is " << month << "." << day << "." << year << std::endl;
        }
};

class EuropeanDateImp : public DateImp {
    public:
        EuropeanDateImp(int day, int month, int year) : DateImp(day, month, year) {}

        void print() {
            std::cout << "Date is " << day << "." << month << "." << year << std::endl;
        }
};

class Date {
    protected:
        DateImp *imp;

    public:
        Date() {}
        Date(int day, int month, int year) {
            imp = new DateImp(day, month, year);
        }

        virtual void print() {
            imp->print();
        }
};


class AmericanDate : public Date {
    public:
        AmericanDate(int day, int month, int year) {
            imp = new AmericanDateImp(day, month, year);
        }
};

class EuropeanDate : public Date {
    public:
        EuropeanDate(int day, int month, int year) {
            imp = new EuropeanDateImp(day, month, year);
        }
};

int main() {
    Date *eu_date = new EuropeanDate(9, 11, 2001);
    Date *usa_date = new AmericanDate(9, 11, 2001);

    eu_date->print();
    usa_date->print();

    return 0;
}
