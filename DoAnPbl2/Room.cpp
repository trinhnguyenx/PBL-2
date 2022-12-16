#include"Room.h"
#include<iostream>
#include<string>
#include <iomanip>
#include<ctime>
using namespace std;

// --------------------------- CONSTRUCTORS & DESTRUCTOR --------------------------- //
Room::Room(string ma_phong, string ten, string trang_thai_phong, string loai_phong, string SDT, int he_So_gia, int ngay, int thang, int nam)
: ma_phong(ma_phong), ten(ten), trang_thai_phong(trang_thai_phong), loai_phong(loai_phong), SDT(SDT), he_So_gia(he_So_gia) {
	this->ngay_thue = new Date1(ngay, thang, nam);
	this->next = nullptr;
	this->previous = nullptr;
}
Room::Room(const Room& p)
	: ma_phong(p.ma_phong), ten(p.ten), trang_thai_phong(p.trang_thai_phong), loai_phong(p.loai_phong), SDT(p.SDT), he_So_gia(p.he_So_gia) {
	this->ngay_thue = new Date1(*p.ngay_thue);
	this->next = nullptr;
	this->previous = nullptr;
}
Room::Room()
	: ma_phong(""), ten(""), trang_thai_phong(""), loai_phong(""), SDT(""), he_So_gia(0) {
	this->ngay_thue = new Date1();
	this->next = nullptr;
	this->previous = nullptr;
}
Room::~Room() {
	// list's destructor will delete it, memory without pointer will be erase.
	this->next = nullptr;
	this->previous = nullptr;
	delete this->ngay_thue;
}

int day_now() {
	time_t rawtime = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &rawtime);
	return  timeinfo.tm_mday;
}/*
int month_now() {
	time_t rawtime = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &rawtime);
	return  timeinfo.tm_mon;
}
int year_now() {
	time_t rawtime = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &rawtime);
	return  timeinfo.tm_year;
}*/
void Room::show() {
	cout << "| " << setw(14) << this->ma_phong << " | " << setw(30) << this->ten << " | ";
	cout << setw(15) << this->SDT << " | ";
	cout << setw(15) << this->trang_thai_phong << " | " << setw(15) << this->loai_phong << " | " << *this->ngay_thue;
	cout << setw(5) << day_now() - this->ngay_thue->get_ngay_thue() << " |" << endl;
	cout << setw(5) << this ->he_So_gia * this -> gcb * (day_now() - this ->ngay_thue->get_ngay_thue()) << " |" << endl;
	cout << setw(50) << "" << "------------------------------------------------------------------------------------------------------------------------------------" << endl;
}
bool Room::equals(const Room& p) {
	if (this->ma_phong == p.ma_phong)
		return true;
	else
		return false;
}
bool Room::compare_id(string id) {
	if (this->ma_phong.length() < id.length())
		return false;
	for (int i = 0; i <= (this->ma_phong.length() - id.length()); i++) {
		string temp = this->ma_phong.substr(i, id.length());
		if (id == temp)
			return true;
	}
	return false;
}
bool Room::compare_full_id(string id) {
	if (this->ma_phong == id)
		return true;
	else
		return false;
}
bool Room::compare_name(string name) {
	if (this->ten.length() < name.length())
		return false;
	for (int i = 0; i <= (this->ten.length() - name.length()); i++) {
		string temp = this->ten.substr(i, name.length());
		if (name == temp)
			return true;
	}
	return false;
}
bool Room::compare_SDT(string SDT) {
	if (this->SDT.length() < SDT.length())
		return false;
	for (int i = 0; i <= (this->SDT.length() - SDT.length()); i++) {
		string temp = this->SDT.substr(i, SDT.length());
		if (SDT == temp)
			return true;
	}
	return false;
}
bool Room::compare_trang_thai_phong(string lien_lac) {
	if (this->trang_thai_phong.length() < lien_lac.length())
		return false;
	for (int i = 0; i <= (this->trang_thai_phong.length() - lien_lac.length()); i++) {
		string temp = this->trang_thai_phong.substr(i, lien_lac.length());
		if (lien_lac == temp)
			return true;
	}
	return false;
}
bool Room::compare_loai_phong(string loai_phong) {
	if (this->loai_phong.length() < loai_phong.length())
		return false;
	for (int i = 0; i <= (this->loai_phong.length() - loai_phong.length()); i++) {
		string temp = this->loai_phong.substr(i, loai_phong.length());
		if (loai_phong == temp)
			return true;
	}
	return false;
}
bool Room::compare_date_age(int day, int month, int year) {
	if (day == (day_now() - this->ngay_thue->get_ngay_thue()))
		return true;
	else
		return false;
}
bool Room::compare_age(const Room& Room, bool check) {
	return this->ngay_thue->compare_date(*Room.ngay_thue, check);
}
bool Room::compare_position(const Room& Room, bool check) {
	if (check == true)
		return this->he_So_gia >= Room.he_So_gia;
	else
		return this->he_So_gia <= Room.he_So_gia;
}

// tinh he so tinh_tien thong qua loai phong
void calc_hsg(const string& loai_phong, int& hsg) {
	if (loai_phong == "SINGLE")
		hsg = 1;
	else if (loai_phong == "DOUBLE")
		hsg = 2;
	else
		hsg = 3;
}

void Clear_input() {
	cin.clear();
	cin.ignore(10000, '\n');  // skips 10000 characters to the next newline
} // clear cin
// kiem tra xem nhap ngay co hop le khong

void Check_date(int ngay, int thang, int nam) throw(string()) {
	if (thang <= 0 || thang > 12 || nam < 0)
		throw string();

	if ((thang <= 7 && thang % 2 == 1) || (thang >= 8 && thang % 2 == 0)) {
		if (ngay <= 0 || ngay > 31)
			throw string();
	}
	else if ((thang <= 7 && thang % 2 == 0) || (thang >= 8 && thang % 2 == 1)) {
		if (thang == 2) {
			if (nam % 400 == 0 || (nam % 4 == 0 && nam % 100 != 0)) { // nam nhuan
				if (ngay <= 0 || ngay > 29)
					throw string();
			}
			else {
				if (ngay <= 0 || ngay > 28)
					throw string();
			}
		}
		else {
			if (ngay <= 0 || ngay > 30)
				throw string();
		}
	}
}

void to_Upper_case(string& str) {
	for (char& c : str) {
		if (int(c) >= 97 && int(c) <= 122) {
			c -= 32;
		}
	}
}
string to_Lower_case(string str) {
	for (char& c : str) {
		if (int(c) >= 65 && int(c) <= 90) {
			c += 32;
		}
	}
	return str;
}

// use for operator >>

ostream& operator<<(ostream& out, const Room& Room) {
	cout << "| " << setw(14) << Room.ma_phong << " | " << setw(30) << Room.ten << " | ";
	cout << setw(15) << Room.SDT << "|";
	cout << setw(15) << Room.trang_thai_phong << " | " << setw(15) << Room.loai_phong << " | " << *Room.ngay_thue;
	cout << setw(5) << day_now() - Room.ngay_thue->get_ngay_thue() << " |" << endl;
	cout << setw(5) << Room.he_So_gia * Room.gcb * (day_now() - Room.ngay_thue->get_ngay_thue()) << " |" << endl;
	cout << setw(50) << "" << "------------------------------------------------------------------------------------------------------------------------------------" << endl;
	return out;
}
istream& operator>>(istream& cin, Room& Room) {
	cout << endl << endl << setw(105) << "NHAP THONG TIN PHONG" << endl << endl;
	fflush(stdin);
	cout << setw(70) << "" << "Ma Phong: ";
	getline(cin, Room.ma_phong);
	to_Upper_case(Room.ma_phong);
	cout << endl << setw(70) << "" << "Ten KH: ";
	getline(cin, Room.ten);
	to_Upper_case(Room.ten);
	cout << endl << setw(70) << "" << "Trang thai phong: ";
	getline(cin, Room.trang_thai_phong);
	to_Upper_case(Room.trang_thai_phong);
	cout << endl << setw(70) << "" << "Loai phong (single,double,family): ";
	getline(cin, Room.loai_phong);
	to_Upper_case(Room.loai_phong);
	// input gioi_tinh (bool)
	cout << endl << setw(70) << "" << "SDT: ";
	getline(cin, Room.SDT);
	to_Upper_case(Room.SDT);
	//do {
	//	try {
	//		int gioi_tinh;
	//		cout << endl << setw(70) << "" << "Gioi tinh (0: nam, 1: nu): ";
	//		cin >> gioi_tinh;

	//		if (cin.fail() || (gioi_tinh != 0 && gioi_tinh != 1)) {
	//			throw runtime_error("");
	//		}

	//		Clear_input(); // clear o day de don dep input thua con sot lai
	//		Room.gioi_tinh = gioi_tinh;
	//		break;
	//	}
	//	catch (runtime_error e) {
	//		cout << endl << setw(71) << "> ERROR: WRONG INPUT!" << endl;
	//		Clear_input(); // clear cin
	//	}
	// while (true);
	// input Date
	do {
		try {
			int ngay, thang, nam; // for Date
			cout << endl << setw(70) << "" << "Ngay, thang, nam thue: ";
			cin >> ngay >> thang >> nam;

			if (cin.fail()) {
				throw runtime_error("");
			}

			Check_date(ngay, thang, nam); // kiem tra hop le ngay

			Clear_input(); // clear o day de don dep input thua con sot lai
			Room.ngay_thue = new Date1(ngay, thang, nam);
			break;
		}
		catch (runtime_error e) {
			cout << endl << setw(71) << "> ERROR: WRONG INPUT!" << endl;
			Clear_input();
		}
		catch (string s) {
			cout << endl << setw(87) << "> ERROR: Ngay thang nam khong hop le!" << endl;
		}
	} while (true);

	calc_hsg(Room.loai_phong, Room.he_So_gia);

	return cin;
}

void Room::update_info(Room& Room) {
	cin >> Room;
}
void Room::copy_info(const Room& e) {
	this->ma_phong = e.ma_phong;
	this->ten = e.ten;
	this->trang_thai_phong = e.trang_thai_phong;
	this->loai_phong = e.loai_phong;
	this->SDT = e.SDT;
	this->he_So_gia = e.he_So_gia;
	this->ngay_thue->copy_date(*e.ngay_thue);
}
int Room::tinh_tien() {
	return this->he_So_gia * gcb ;
}
double Room::thuc_linh() {
	return this->tinh_tien();
}


void Room::copy_attributes(Room& e) {
	this->ma_phong = e.ma_phong;
	this->ten = e.ten;
	this->trang_thai_phong = e.trang_thai_phong;
	this->loai_phong = e.loai_phong;
	this->he_So_gia = e.he_So_gia;
	this->SDT = e.SDT;
	*this->ngay_thue = *e.ngay_thue;
}

// GETTERS
string Room::get_ma_phong() {
	return this->ma_phong;
}
string Room::get_ten() {
	return this->ten;
}
string Room::get_trang_thai_phong() {
	return this->trang_thai_phong;
}
string Room::get_loai_phong() {
	return this->loai_phong;
}
string Room::get_SDT() {
	return this->SDT;
}
string Room::get_string_date() {
	return this->ngay_thue->store_string_date();
}
int Room::get_he_So_gia() {
	return this->he_So_gia;
}
int Room::get_tinh_tien() {
	return this->tinh_tien();
}
