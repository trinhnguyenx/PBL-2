#include<iostream>
#include<string>
#include <iomanip>
#include"Date.h"
using namespace std;

Date1::Date1(int ngay, int thang, int nam) : ngay(ngay), thang(thang), nam(nam) {}
Date1::Date1() : ngay(0), thang(0), nam(0) {}
Date1::Date1(const Date1& d) : ngay(d.ngay), thang(d.thang), nam(d.nam) {}

bool Date1::compare_date(const Date1& date, bool condition) {
	// condition == true : ascending, false :descending
	if (this->nam == date.nam) {
		if (this->thang == date.thang) {
			if (condition == true)
				return this->ngay <= date.ngay;
			else
				return this->ngay >= date.ngay;
		}
		else {
			if (condition == true)
				return this->thang <= date.thang;
			else
				return this->thang >= date.thang;
		}
	}
	else {
		if (condition == true)
			return this->nam <= date.nam;
		else
			return this->nam >= date.nam;
	}
}

void Date1::copy_date(const Date1& date) {
	this->ngay = date.ngay;
	this->thang = date.thang;
	this->nam = date.nam;
}

string Date1::store_string_date() {
	string s = to_string(this->ngay) + "\t" + to_string(this->thang);
	s += "\t" + to_string(this->nam);
	return s;
}

int Date1::get_ngay_thue() {
	return this->ngay;
}

ostream& operator<<(ostream& o, const Date1& date) {
	if (date.ngay / 10 == 0) {
		o << setw(6) << "0" << date.ngay << "/";
	}
	else {
		o << setw(7) << date.ngay << "/";
	}
	if (date.thang / 10 == 0) {
		o << "0";
	}
	o << date.thang << "/" << date.nam << " |";
	return o;
}