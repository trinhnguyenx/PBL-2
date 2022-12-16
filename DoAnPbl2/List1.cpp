#include "List1.h"
#include <iomanip>
#include <stdlib.h>
using namespace std;

// Constructor & Destructor
List1::List1() : first(nullptr), last(nullptr) {}
List1::List1(Room& room) : first(&room), last(&room) {
	room.next = nullptr;
	room.previous = nullptr;
}
List1::List1(const List1& list) : first(list.first), last(list.last) {}
List1::~List1() {
	Room* room = this->first;
	Room* next_room;

	while (room != nullptr) {
		next_room = room->next;

		delete room; // next and previous became nullptr pointer
		room = next_room;
	}
}
// Constructor & Destructor

int List1::size_of_list() {
	Room* current_room = this->first;
	int list_size = 0;

	while (current_room != nullptr) {
		list_size++;
		current_room = current_room->next;
	}
	return list_size;
}
void List1::display_list() {
	if (first == nullptr) { // list empty
		cout << endl << setw(70) << "" << "> ERROR: Khong co gi de hien thi!" << endl;
		return; // do nothing
	}
	Room* current_room = this->first;
	cout << endl << endl << setw(128) << "DANH SACH PHONG" << endl << endl;
	cout << setw(50) << "" << "------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << setw(50) << "" << "|" << setw(8) << " | " << setw(17) << " | " << setw(33) << " | " << setw(13) << " | " << setw(18) << " | " << setw(18) << " | " << setw(17) << "|" << setw(7) << " |" << endl;
	cout << setw(50) << "" << "|" << setw(5) << "STT" << " | " << setw(14) << "MA PHONG" << " | " << setw(30) << "HO VA TEN KH" << " | " << setw(10) << "SDT" << " | " << setw(15) << "TRANG THAI PHONG" << " | " << setw(15) << "LOAI PHONG" << " | " << setw(15) << "NGAY THUE" << " |" << setw(5) << "SO NGAY" << " |" << endl;
	cout << setw(50) << "" << "|" << setw(8) << " | " << setw(17) << " | " << setw(33) << " | " << setw(13) << " | " << setw(18) << " | " << setw(18) << " | " << setw(17) << "|" << setw(7) << " |" << endl;
	cout << setw(50) << "" << "------------------------------------------------------------------------------------------------------------------------------------" << endl;
	int stt = 1;
	while (current_room != nullptr) {
		cout << setw(50) << "" << "| " << setw(5) << stt;
		current_room->show();
		current_room = current_room->next;
		stt++;
	}
}

void List1::add_Room_at_first() {
	Room* new_room = new Room();
	cin >> *new_room;

	if (check_if_contain_full_id(new_room->get_ma_phong()) == true) {
		system("cls");
		this->display_list();
		cout << endl << setw(50) << "" << "> ERROR: DA TON TAI PHONG CO MA PHONG NAY!" << endl << endl;
		return;
	}

	if (this->first == nullptr) {
		this->last = new_room;
	}
	else {
		this->first->previous = new_room;
	}

	new_room->previous = nullptr;
	new_room->next = this->first;
	this->first = new_room;
	system("cls");
	this->display_list();
	cout << endl << setw(50) << "" << "DA THEM PHONG!" << endl << endl;
	append_file(*new_room); // save new_Room to file.
}
void List1::add_Room_at_last() {
	Room* new_room = new Room();
	cin >> *new_room;

	if (check_if_contain_full_id(new_room->get_ma_phong()) == true) {
		system("cls");
		this->display_list();
		cout << endl << setw(50) << "" << "> ERROR: DA TON TAI PHONG CO MA PHONG NAY!" << endl << endl;
		return;
	}

	if (this->first == nullptr) {
		this->first = new_room;
	}
	else {
		this->last->next = new_room;
	}

	new_room->previous = this->last;
	new_room->next = nullptr;
	this->last = new_room;
	system("cls");
	this->display_list();
	cout << endl << setw(50) << "" << "DA THEM PHONG!" << endl << endl;
	append_file(*new_room); // save new_Room to file.
}
void List1::add_Room_at_last(Room& room) {
	Room* new_room = &room;

	if (check_if_contain_full_id(new_room->get_ma_phong()) == true) {
		cout << "Da ton tai phong co ma phong nay" << endl;
		return;
	}

	if (this->first == nullptr) {
		this->first = new_room;
	}
	else {
		this->last->next = new_room;
	}

	new_room->previous = this->last;
	new_room->next = nullptr;
	this->last = new_room;
}
void List1::add_Room_at_specific_pos(int pos) {
	Room* present_room = this->first;
	int index = 0; // to find where to add new Room
	int k = pos - 1;

	while (present_room != nullptr) {
		if (index != k) {
			present_room = present_room->next;
			index++;
		}
		else {
			break; // index == k
		}
	}

	if (present_room == nullptr) {
		if (k == this->size_of_list()) { // case k == list's size, so insert Room at the bottom of the list
			this->add_Room_at_last(); // call add last
		}
		else { // case out of list's size + 1
			system("cls");
			cout << endl << setw(70) << "" << "> ERROR: Khong the them o vi tri nay!" << endl;
		}
	}
	else if (present_room == first) {
		this->add_Room_at_first(); // call add first
		system("cls");
		this->display_list();
		cout << endl << setw(50) << "" << "DA THEM PHONG!" << endl << endl;
	}
	else { // case present_Room having previous and next != nullptr
		Room* new_room = new Room();
		cin >> *new_room;

		if (check_if_contain_full_id(new_room->get_ma_phong()) == true) {
			system("cls");
			this->display_list();
			cout << endl << setw(50) << "" << "> ERROR: DA TON TAI PHONG CO MA PHONG NAY!" << endl << endl;
			return;
		}

		present_room->previous->next = new_room;
		new_room->previous = present_room->previous;
		present_room->previous = new_room;
		new_room->next = present_room;
		system("cls");
		this->display_list();
		cout << endl << setw(50) << "" << "DA THEM PHONG!" << endl << endl;
		append_file(*new_room); // save new_Room to file.
	}
}

Room& List1::search_Room_by_full_id(string id) {
	Room* current_room = this->first;

	while (current_room != nullptr && current_room->compare_full_id(id) == false) { // search for the correct Room in the list 
		current_room = current_room->next;
	}

	return *current_room; // return NULL if its not found otherwise return correct Room
}
void List1::search_and_print(int choice, string info) {
	Room* current_room = this->first;

	int stt = 1;
	while (current_room != nullptr) { // search for the correct Room in the list
		if (choice == 1) {
			if (current_room->compare_id(info) == true) {
				cout << setw(50) << "" << "| " << setw(5) << stt;
				current_room->show();
				stt++;
			}
		}
		if (choice == 2) {
			if (current_room->compare_name(info) == true) {
				cout << setw(50) << "" << "| " << setw(5) << stt;
				current_room->show();
				stt++;
			}
		}
		else if (choice == 3) {
			if (current_room->compare_trang_thai_phong(info) == true) {
				cout << setw(50) << "" << "| " << setw(5) << stt;
				current_room->show();
				stt++;
			}
		}
		else if (choice == 4) {
			if (current_room->compare_loai_phong(info) == true) {
				cout << setw(50) << "" << "| " << setw(5) << stt;
				current_room->show();
				stt++;
			}
		}

		current_room = current_room->next;
	}
}

void List1::print_statistics() {
	if (first == nullptr) { // list empty
		return; // do nothing
	}

	Room* current_room = this->first;
	int male = 0, female = 0;
	double tong_thuc_linh = 0;

	while (current_room != nullptr) {
		//if (current_room->get_gioi_tinh() == "NAM")
		//	male++;
		//else
		//	female++;
		tong_thuc_linh += current_room->thuc_linh();
		current_room = current_room->next;
	}
	cout << endl << endl;
	cout << setw(50) << "" << "----SO LIEU THONG KE----" << endl << endl;
	//cout << setw(50) << "" << "So luong PHONG: " << male + female << endl;
	//cout << setw(50) << "" << "So luong PHONG nam: " << male << endl;
	//cout << setw(50) << "" << "So luong PHONG nu: " << female << endl;
	cout << setw(50) << "" << "Tong thuc linh: " << tong_thuc_linh << endl;
}

void List1::delete_Room_at_first() {
	if (first == nullptr) { // case list empty
		return; // do nothing and return
	}
	else if (this->first == this->last) { // case list only have 1 Room
		delete first;
		first = nullptr;
		last = nullptr;
	}
	else {
		Room* current_room = this->first;
		this->first = this->first->next;
		this->first->previous = nullptr;

		delete current_room;
	}
}
void List1::delete_Room_at_last() {
	if (last == nullptr) { // case list empty
		return; // do nothing and return
	}
	else if (this->first == this->last) { // case list only have 1 Room
		delete last;
		first = nullptr;
		last = nullptr;
	}
	else {
		Room* current_room = this->last;
		this->last = this->first->previous;
		this->last->next = nullptr;

		delete current_room;
	}
}
bool List1::delete_Room_at_specific_pos(int pos) { // k: positon to remove Room
	Room* room = this->first;
	int index = 0; // to find where to add new Room
	int k = pos - 1;

	while (room != nullptr) {
		if (index != k) {
			room = room->next;
			index++;
		}
		else {
			break; // index == k
		}
	}

	if (index >= this->size_of_list()) {
		return false;
	}

	if (room != nullptr && this->size_of_list() != 1) {
		if (room == this->first) {
			this->first = room->next;
			room->next->previous = nullptr;
			delete room;
		}
		else if (room == this->last) {
			this->last = room->previous;
			room->previous->next = nullptr;
			delete room;
		}
		else {
			room->previous->next = room->next;
			room->next->previous = room->previous;
			delete room;
		}
	}
	else if (room != nullptr && this->size_of_list() == 1) {
		this->delete_Room_at_first();
	}
	return true;
}

int List_year_now() {
	time_t rawtime = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &rawtime);
	return 1900 + timeinfo.tm_year;
}
void Upper_case(string& str) {
	for (char& c : str) {
		if (int(c) >= 97 && int(c) <= 122) {
			c -= 32;
		}
	}
}
bool List1::delete_Room(string ma_phong) {
	if (first == NULL) {
		return false;
	}

	Room* room = first;
	while ((room != NULL) && (room->get_ma_phong() != ma_phong)) {
		room = room->next;
	}

	if (room != nullptr && this->size_of_list() != 1) {
		if (room == this->first) {
			this->first = room->next;
			room->next->previous = nullptr;
			delete room;
		}
		else if (room == this->last) {
			this->last = room->previous;
			room->previous->next = nullptr;
			delete room;
		}
		else {
			room->previous->next = room->next;
			room->next->previous = room->previous;
			delete room;
		}
	}
	else if (room != nullptr && this->size_of_list() == 1) {
		this->delete_Room_at_first();
	}
	else { // Room == nullptr
		return false;
	}
	return true;
}
bool List1::delete_Room_by_name(string ten) {
	if (this->first == nullptr)
		return false;

	Room* room = this->first;
	bool check = false;
	Upper_case(ten);

	while (room != nullptr) {
		if (room->get_ten() == ten) {
			if (this->size_of_list() == 1) {
				this->delete_Room_at_first();
				return true;
			}
			else {
				if (room == this->first) {
					this->first = room->next;
					room->next->previous = nullptr;
					delete room;
					room = this->first;
				}
				else if (room == this->last) {
					this->last = room->previous;
					room->previous->next = nullptr;
					delete room;
					room = this->last;
				}
				else {
					Room* t = room->previous;
					room->previous->next = room->next;
					room->next->previous = room->previous;
					delete room;
					room = t;
				}
				check = true;
			}
		}
		room = room->next;
	}

	return check;
}

bool List1::update_Room_info(string id) {
	Room* room = &search_Room_by_full_id(id);

	if (room == nullptr) {
		system("cls");
		this->display_list();
		cout << endl << setw(50) << "" << "> ERROR: Khong tim thay phong nay!" << endl;
		return false;
	}

	Room* temp = new Room();
	cin >> *temp;
	if (check_if_contain_full_id(temp->get_ma_phong()) == true) {
		if (temp->get_ma_phong() == id) {
			room->copy_attributes(*temp);
			delete temp;
			return true;
		}
		else {
			system("cls");
			this->display_list();
			cout << endl << setw(50) << "" << "> ERROR: Da ton tai phong co ma phong nay!" << endl;
			delete temp;
			return false;
		}
	}
	else {
		room->copy_attributes(*temp);
		delete temp;
		return true;
	}
}

bool List1::check_if_contain(string id) {
	Room* current_room = this->first;

	while (current_room != nullptr) {
		if (current_room->compare_id(id) == true) {
			return true;
		}
		current_room = current_room->next;
	}

	return false; // current_Room == nullptr 
}
bool List1::check_if_contain_name(string name) {
	Room* current_room = this->first;

	while (current_room != nullptr) {
		if (current_room->compare_name(name) == true) {
			return true;
		}
		current_room = current_room->next;
	}

	return false; // current_Room == nullptr 
}
bool List1::check_if_contain_trang_thai_phong(string trang_thai_phong)
{
	Room* current_room = this->first;

	while (current_room != nullptr) {
		if (current_room->compare_trang_thai_phong(trang_thai_phong) == true) {
			return true;
		}
		current_room = current_room->next;
	}

	return false; // current_Room == nullptr 
}
bool List1::check_if_contain_loai_phong(string loai_phong) {
	Room* current_room = this->first;

	while (current_room != nullptr) {
		if (current_room->compare_loai_phong(loai_phong) == true) {
			return true;
		}
		current_room = current_room->next;
	}

	return false; // current_Room == nullptr 
}
bool List1::check_if_contain_full_id(string id) {
	Room* current_room = this->first;

	while (current_room != nullptr) {
		if (current_room->get_ma_phong() == id) {
			return true;
		}
		current_room = current_room->next;
	}

	return false; // current_room == nullptr 
}

// sort related
void swap(Room* left, Room* right) {
	Room* temp = new Room();
	temp->copy_info(*left);

	left->copy_info(*right);
	right->copy_info(*temp);

	delete temp;
}
Room* partition1(Room* left, Room* right, bool check) {
	Room* i = left->previous;
	Room* j = left;

	while (j != right->next) {
		if (j->compare_age(*right, check) == true) {
			if (i == nullptr)
				i = left;
			else
				i = i->next;
			swap(i, j);
		}
		j = j->next;
	}

	if (i == nullptr)
		i = left;
	return i;
}
Room* partition2(Room* left, Room* right, bool check) {
	Room* i = left->previous;
	Room* j = left;

	while (j != right->next) {
		if (j->compare_position(*right, check) == true) {
			if (i == nullptr)
				i = left;
			else
				i = i->next;
			swap(i, j);
		}
		j = j->next;
	}

	if (i == nullptr)
		i = left;
	return i;
}
void List1::position_sort(Room* left, Room* right, bool check) {
	if (left != right && left != nullptr && right != nullptr) {
		Room* q = partition2(left, right, check);
		if (q->previous != nullptr && q != left->previous) {
			position_sort(left, q->previous, check);
		}
		if (q->next != nullptr && q != left->previous) {
			position_sort(q->next, right, check);
		}
	}
}

void tinh_hsg(const string& loai_phong, int& hsg) {
	if (loai_phong == "A")
		hsg = 1;
	else if (loai_phong == "B")
		hsg = 2;
	else if (loai_phong == "C")
		hsg = 3;
	else if (loai_phong == "D")
		hsg = 4;
	else if (loai_phong == "E")
		hsg = 5;
	else
		hsg = 1;
}
void List1::read_file(string file) {
	int i = 0;
	string hoTen, maPhong, gioiTinhStr;
	string trangthaiphong, loaiPhong, SDT;

	ifstream reader(file);
	if (!reader) {
		cout << "Error opening input file" << endl;
		return;
	}

	while (!reader.eof()) {
		// lay thong tin tu file
		if (i == 0)
			getline(reader, hoTen, '\t');
		else if (i == 1)
			getline(reader, maPhong, '\t');
		else if (i == 2) {
			getline(reader, SDT, '\t');
		}
		else if (i == 3)
			getline(reader, trangthaiphong, '\t');
		else if (i == 4) {
			getline(reader, loaiPhong, '\t');
		}
		else if (i == 5) {
			string ngay_str, thang_str, nam_str;
			int ngay, thang, nam;
			int hsg;

			getline(reader, ngay_str, '\t');
			getline(reader, thang_str, '\t');
			getline(reader, nam_str, '\n');
			tinh_hsg(loaiPhong, hsg);

			stringstream converter;

			converter.str(ngay_str);
			converter >> ngay;
			converter.clear();
			converter.str(thang_str);
			converter >> thang;
			converter.clear();
			converter.str(nam_str);
			converter >> nam;
			converter.clear();

			Room* room_new = new Room(maPhong, hoTen, trangthaiphong, loaiPhong, SDT, hsg, ngay, thang, nam);
			this->add_Room_at_last(*room_new);
			i = 0;
			continue;
		}
		i++;
	}
	reader.close();
}
void List1::write_file() {
	ofstream writer("records19.txt");
	if (!writer) {
		cout << "error opening file for output" << endl;
		return;
	}
	Room* currentnode = this->first;
	for (currentnode; currentnode != nullptr; currentnode = currentnode->next) {
		string info = currentnode->get_ten() + "\t" + currentnode->get_ma_phong() + "\t";
		info += currentnode->get_SDT() + "\t" + currentnode->get_trang_thai_phong() + "\t";
		info += currentnode->get_loai_phong() + "\t" + currentnode->get_string_date();

		//info = to_upper_case(info);

		writer << info << endl;
	}
	writer.close();
}
void List1::append_file(Room& e) {
	ofstream writer("records19.txt", ios::app);
	string info = e.get_ten() + "\t" + e.get_ma_phong() + "\t";
	info += e.get_SDT() + "\t" + e.get_trang_thai_phong() + "\t";
	info += e.get_loai_phong() + "\t" + e.get_string_date();

	//info = to_upper_case(info);

	writer << info << endl;
}

// run func supporter
void Clear_input_list() {
	cin.clear();
	cin.ignore(10000, '\n');  // skips 10000 characters to the next newline
}
void Menu() {
	cout << setw(70) << "" << "----------------------------------------------------------------------------------";
	cout << endl << setw(71) << "|" << setw(81) << "|" << endl << setw(71) << "|" << setw(55) << "CHUONG TRINH QUAN LY PHONG" << setw(26) << "|" << endl << setw(71) << "|" << setw(81) << "|" << endl;
	cout << setw(70) << "" << "|--------------------------------------------------------------------------------|" << endl << setw(71) << "|" << setw(81) << "|" << endl;
	cout << setw(71) << "|" << setw(30) << "Danh sach cac lua chon:" << setw(51) << "|" << endl;
	cout << setw(71) << "|" << setw(30) << "" << "1. Hien thi danh sach phong" << setw(24) << "|" << endl;
	cout << setw(71) << "|" << setw(30) << "" << "2. Them phong" << setw(38) << "|" << endl;
	cout << setw(71) << "|" << setw(30) << "" << "3. Cap nhat thong tin phong" << setw(24) << "|" << endl;
	//	cout << setw(71) << "|" << setw(30) << "" << "4. Xoa phong" << setw(39) << "|" << endl;
	cout << setw(71) << "|" << setw(30) << "" << "4. Tim kiem phong" << setw(34) << "|" << endl;
	//  cout << setw(71) << "|" << setw(30) << "" << "6. Sap xep danh sach phong" << setw(25) << "|" << endl;
	cout << setw(71) << "|" << setw(30) << "" << "5. Luu thay doi vao file" << setw(27) << "|" << endl;
	cout << setw(71) << "|" << setw(30) << "" << "6. Exit" << setw(44) << "|" << endl;
	cout << setw(70) << "" << "----------------------------------------------------------------------------------" << endl << endl;
}
void add_Room(List1& list, int i) {
	if (i == 0) {
		system("CLS");
		return;
	}
	if (i == 1) {
		system("CLS");
		list.add_Room_at_first();
	}
	else if (i == 2) {
		system("CLS");
		list.add_Room_at_last();
	}
	else if (i == 3) {
		int position_to_add = 0;
		cout << endl << setw(70) << "" << "Nhap vi tri muon them: ";
		cin >> position_to_add;

		cin.ignore();
		system("cls");
		list.add_Room_at_specific_pos(position_to_add);
	}
	else {
		system("cls");
		cout << endl << setw(70) << "" << "> ERROR: Lua chon khong ton tai!" << endl << endl;
	}
}
//void handle_delete_Room(List1& list, int i) {
//	if (i == 0) {
//		system("CLS");
//		return;
//	}
//	else if (i == 1) {
//		string id;
//
//		cout << endl << setw(70) << "" << "Nhap ma phong can xoa: ";
//		cin.ignore();
//		getline(cin, id);
//		Upper_case(id);

//		if (list.delete_Room(id) == true) {
//			system("cls");
//			list.display_list();
//		cout << endl << setw(50) << "" << "DA XOA THANH CONG!" << endl << endl;
//		}
//		else {
//			system("cls");
//			list.display_list();
//			cout << endl << setw(50) << "" << "> ERROR: KHONG TIM THAY PHONG CO MA PHONG NAY!" << endl << endl;
//		}
//	}
//	else if (i == 2) {
//		int position_to_remove = 0;
//		cout << endl << setw(70) << "" << "Nhap vi tri muon xoa: ";
//		cin >> position_to_remove;

//		if (list.delete_Room_at_specific_pos(position_to_remove) == true) {
//			system("cls");
//			list.display_list();
//			cout << endl << setw(50) << "" << "DA XOA THANH CONG!" << endl << endl;
//		}
//		else {
//			system("cls");
//			list.display_list();
//			cout << endl << setw(50) << "" << "> ERROR: KHONG TON TAI VI TRI NAY!" << endl << endl;
//		}
//	}
//	else {
//		system("cls");
//		cout << endl << setw(70) << "" << "ERROR: Lua chon khong ton tai!" << endl << endl;
//	}
//}
void print_Menu_danh_sach() {
	cout << endl << endl << setw(128) << "DANH SACH PHONG" << endl << endl;
	cout << setw(50) << "" << "------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << setw(50) << "" << "|" << setw(8) << " | " << setw(17) << " | " << setw(33) << " | " << setw(13) << " | " << setw(18) << " | " << setw(18) << " | " << setw(17) << "|" << setw(7) << " |" << endl;
	cout << setw(50) << "" << "|" << setw(5) << "STT" << " | " << setw(14) << "MA PHONG" << " | " << setw(30) << "HO VA TEN KH" << " | " << setw(10) << "SDT" << " | " << setw(15) << "TRANG THAI PHONG" << " | " << setw(15) << "LOAI PHONG" << " | " << setw(15) << "NGAY THUE" << " |" << setw(5) << "SO NGAY" << " |" << endl;
	cout << setw(50) << "" << "|" << setw(8) << " | " << setw(17) << " | " << setw(33) << " | " << setw(13) << " | " << setw(18) << " | " << setw(18) << " | " << setw(17) << "|" << setw(7) << " |" << endl;
	cout << setw(50) << "" << "------------------------------------------------------------------------------------------------------------------------------------" << endl;
}
void handle_search_Room(List1& list, int i) {//TIM KIEM 
	string search;
	if (i == 0) {
		system("CLS");
		return;
	}
	if (i < 0 || i > 5) {
		system("cls");
		cout << endl << setw(70) << "" << "> ERROR: Lua chon khong ton tai!" << endl << endl;
		return;
	}
	system("cls");
	list.display_list();
	if (i == 1) {
		cout << setw(50) << "" << "Nhap ma phong muon tim: ";
		getline(cin, search);
		Upper_case(search);
		if (list.check_if_contain(search) == true) {
			system("cls");
			print_Menu_danh_sach();
			list.search_and_print(1, search); // 1: ma PHONG
			cout << endl << endl;
		}
		else {
			system("cls");
			cout << endl << setw(70) << "" << "> ERROR: Khong tim thay phong!" << endl;
		}
	}
	else if (i == 2) {
		cout << setw(50) << "" << "Nhap ten khach hang muon tim: ";
		getline(cin, search);
		Upper_case(search);
		if (list.check_if_contain_name(search) == true) {
			system("cls");
			print_Menu_danh_sach();
			list.search_and_print(2, search); // 2: ten khach hang
			cout << endl << endl;
		}
		else {
			system("cls");
			cout << endl << setw(70) << "" << "> ERROR: Khong tim thay phong!" << endl;
		}
	}
	else if (i == 3) {
		cout << setw(50) << "" << "Nhap tinh trang phong muon tim: ";
		getline(cin, search);
		Upper_case(search);
		if (list.check_if_contain_trang_thai_phong(search) == true) {
			system("cls");
			print_Menu_danh_sach();
			list.search_and_print(3, search); // 3: trang thai phiong
		}
		else {
			system("cls");
			cout << endl << setw(70) << "" << "> ERROR: Khong tim thay phong!" << endl;
		}
	}
	else if (i == 4) {
		cout << setw(50) << "" << "Nhap loai phong muon tim: ";
		getline(cin, search);
		Upper_case(search);
		if (list.check_if_contain_loai_phong(search) == true) {
			system("cls");
			print_Menu_danh_sach();
			list.search_and_print(4, search); // 4: loai
		}
		else {
			system("cls");
			cout << endl << setw(70) << "" << "> ERROR: Khong tim thay phong!" << endl;
		}
	}

}
//void handle_sort_Room(List1& list, int i) {
//	bool check;
//	if (i == 0) {
//		system("CLS");
//		return;
//	}
//	else if (i == 1) {
//		system("cls");
//		cout << endl << endl << endl << setw(70) << "" << "----------------------------------------------------------------------------------";
//		cout << endl << setw(71) << "|" << setw(81) << "|" << endl << setw(71) << "|" << setw(54) << "SAP XEP PHONG THEO TUOI" << setw(27) << "|" << endl << setw(71) << "|" << setw(81) << "|" << endl;
//		cout << setw(70) << "" << "|--------------------------------------------------------------------------------|" << endl << setw(71) << "|" << setw(81) << "|" << endl;
//		cout << setw(71) << "|" << setw(30) << "Danh sach cac lua chon:" << setw(51) << "|" << endl;
//		cout << setw(71) << "|" << setw(30) << "" << "0. Sap xep tang dan theo ngay thue" << setw(22) << "|" << endl;
//		cout << setw(71) << "|" << setw(30) << "" << "1. Sap xep giam dan theo ngay thue" << setw(22) << "|" << endl;
//		cout << setw(70) << "" << "----------------------------------------------------------------------------------" << endl << endl;
//		cout << setw(103) << "> ";
//		cin >> check;
//		fflush(stdin);
//		system("CLS");
//		list.display_list();
//		cout << endl << setw(50) << "" << "DANH SACH PHONG DA DUOC SAP XEP!" << endl;
//	}//  chưa sửa
//	else if (i == 2) {
//		system("cls");
//		cout << endl << endl << endl << setw(70) << "" << "----------------------------------------------------------------------------------";
//		cout << endl << setw(71) << "|" << setw(81) << "|" << endl << setw(71) << "|" << setw(57) << "SAP XEP PHONG THEO CHUC VU" << setw(24) << "|" << endl << setw(71) << "|" << setw(81) << "|" << endl;
//		cout << setw(70) << "" << "|--------------------------------------------------------------------------------|" << endl << setw(71) << "|" << setw(81) << "|" << endl;
//		cout << setw(71) << "|" << setw(30) << "Danh sach cac lua chon:" << setw(51) << "|" << endl;
//		cout << setw(71) << "|" << setw(30) << "" << "0. Sap xep tang dan theo loai phong" << setw(19) << "|" << endl;
//		cout << setw(71) << "|" << setw(30) << "" << "1. Sap xep giam dan theo loai phong" << setw(19) << "|" << endl;
//	cout << setw(70) << "" << "----------------------------------------------------------------------------------" << endl << endl;
//		cout << setw(103) << "> ";
//		cin >> check;
//		fflush(stdin);
//		list.position_sort(list.first, list.last, check);
//		system("CLS");
//		list.display_list();
//		cout << endl << setw(50) << "" << "DANH SACH PHONG DA DUOC SAP XEP!" << endl;
//	}
//	else {
//		system("cls");
//		cout << endl << setw(70) << "" << "> ERROR: Lua chon khong ton tai!" << endl << endl;
//	}
//}
void List1::run() {
	int choice;
	while (true) {
		Menu();
		cout << setw(103) << "> ";
		cin >> choice;
		Clear_input_list();
		if (cin.fail()) {
			system("cls");
			cout << endl << setw(70) << "" << "> ERROR: Lua chon khong ton tai!" << endl << endl;
			Clear_input_list();
		}
		else if (choice == 1)
		{
			system("CLS");
			this->display_list();
			this->print_statistics();
		}
		else if (choice == 2)
		{
			system("CLS");
			int add_Room_choice = 0;
			this->display_list();
			cout << endl << endl << endl << setw(70) << "" << "----------------------------------------------------------------------------------";
			cout << endl << setw(71) << "|" << setw(81) << "|" << endl << setw(71) << "|" << setw(45) << "THEM PHONG" << setw(36) << "|" << endl << setw(71) << "|" << setw(81) << "|" << endl;
			cout << setw(70) << "" << "|--------------------------------------------------------------------------------|" << endl << setw(71) << "|" << setw(81) << "|" << endl;
			cout << setw(71) << "|" << setw(30) << "Danh sach cac lua chon:" << setw(51) << "|" << endl;
			cout << setw(71) << "|" << setw(30) << "" << "1. Them vao dau danh sach" << setw(26) << "|" << endl;
			cout << setw(71) << "|" << setw(30) << "" << "2. Them vao cuoi danh sach" << setw(25) << "|" << endl;
			cout << setw(71) << "|" << setw(30) << "" << "3. Them vao vi tri k trong danh sach" << setw(15) << "|" << endl;
			cout << setw(71) << "|" << setw(30) << "" << "0. Quay tro lai menu chinh" << setw(25) << "|" << endl;
			cout << setw(70) << "" << "----------------------------------------------------------------------------------" << endl << endl;
			cout << setw(103) << "> ";

			cin >> add_Room_choice;
			Clear_input_list();

			if (cin.fail()) {
				cout << endl << setw(70) << "" << "> ERROR: Lua chon khong ton tai!" << endl << endl;
				Clear_input_list();
				continue;
			}
			add_Room(*this, add_Room_choice);
		}
		else if (choice == 3)
		{
			system("CLS");
			this->display_list();
			string update_id;
			//cin.ignore();
			cout << endl << endl << setw(50) << "" << "----OPTION: CAP NHAT PHONG----" << endl;
			cout << setw(50) << "" << "Nhap ma phong muon cap nhat: ";
			getline(cin, update_id);
			Upper_case(update_id);

			if (this->update_Room_info(update_id) == true) {
				system("cls");
				this->display_list();
				cout << endl << setw(50) << "" << "CAP NHAT THONG TIN THANH CONG!" << endl;
			}
			write_file(); // save changes
		}
		//else if (choice == 4)
		//{
		//	system("CLS");
		//	int delete_Room_choice = 0;
		//	this->display_list();
		//	cout << endl << endl << endl << setw(70) << "" << "----------------------------------------------------------------------------------";
		//	cout << endl << setw(71) << "|" << setw(81) << "|" << endl << setw(71) << "|" << setw(45) << "XOA PHONG" << setw(36) << "|" << endl << setw(71) << "|" << setw(81) << "|" << endl;
		//	cout << setw(70) << "" << "|--------------------------------------------------------------------------------|" << endl << setw(71) << "|" << setw(81) << "|" << endl;
		//	cout << setw(71) << "|" << setw(30) << "Danh sach cac lua chon:" << setw(51) << "|" << endl;
		//	cout << setw(71) << "|" << setw(30) << "" << "1. Xoa theo ma PHONG" << setw(27) << "|" << endl;
		//	cout << setw(71) << "|" << setw(30) << "" << "2. Xoa o vi tri k trong danh sach" << setw(18) << "|" << endl;
		//	cout << setw(71) << "|" << setw(30) << "" << "0. Quay tro lai menu chinh" << setw(25) << "|" << endl;
		//	cout << setw(70) << "" << "----------------------------------------------------------------------------------" << endl << endl;
		//	cout << setw(103) << "> ";

		//	cin >> delete_Room_choice;
		//	handle_delete_Room(*this, delete_Room_choice);
		//	write_file(); // save changes
		//}
		else if (choice == 4)
		{
			system("CLS");
			int search_choice = 0;
			this->display_list();
			cout << endl << endl << endl << setw(70) << "" << "----------------------------------------------------------------------------------";
			cout << endl << setw(71) << "|" << setw(81) << "|" << endl << setw(71) << "|" << setw(50) << "TIM KIEM PHONG" << setw(31) << "|" << endl << setw(71) << "|" << setw(81) << "|" << endl;
			cout << setw(70) << "" << "|--------------------------------------------------------------------------------|" << endl << setw(71) << "|" << setw(81) << "|" << endl;
			cout << setw(71) << "|" << setw(30) << "Danh sach cac lua chon:" << setw(51) << "|" << endl;
			cout << setw(71) << "|" << setw(30) << "" << "1. Tim kiem theo ma phong" << setw(22) << "|" << endl;
			cout << setw(71) << "|" << setw(30) << "" << "2. Tim kiem theo ten khach hang" << setw(21) << "|" << endl;
			cout << setw(71) << "|" << setw(30) << "" << "3. Tim kiem theo tinh trang phong" << setw(10) << "|" << endl;
			cout << setw(71) << "|" << setw(30) << "" << "4. Tim kiem theo loai phong" << setw(18) << "|" << endl;
			cout << setw(71) << "|" << setw(30) << "" << "0. Quay tro lai menu chinh" << setw(25) << "|" << endl;
			cout << setw(70) << "" << "----------------------------------------------------------------------------------" << endl << endl;
			cout << setw(103) << "> ";
			cin >> search_choice;
			Clear_input_list();
			handle_search_Room(*this, search_choice);
		}
		//else if (choice == 6)
		//{
		//	system("CLS");
		//	int sort_choice = 0;
		//
		//	this->display_list();
		//	cout << endl << endl << endl << setw(70) << "" << "----------------------------------------------------------------------------------";
		//	cout << endl << setw(71) << "|" << setw(81) << "|" << endl << setw(71) << "|" << setw(60) << "SAP XEP DANH SACH PHONG" << setw(21) << "|" << endl << setw(71) << "|" << setw(81) << "|" << endl;
		//	cout << setw(70) << "" << "|--------------------------------------------------------------------------------|" << endl << setw(71) << "|" << setw(81) << "|" << endl;
		//	cout << setw(71) << "|" << setw(30) << "Danh sach cac lua chon:" << setw(51) << "|" << endl;
		//	cout << setw(71) << "|" << setw(30) << "" << "1. Sap xep theo ngay thue" << setw(31) << "|" << endl;
		//	cout << setw(71) << "|" << setw(30) << "" << "2. Sap xep theo loai phong" << setw(28) << "|" << endl;
		//	cout << setw(71) << "|" << setw(30) << "" << "0. Quay tro lai menu chinh" << setw(25) << "|" << endl;
		//	cout << setw(70) << "" << "----------------------------------------------------------------------------------" << endl << endl;
		//	cout << setw(103) << "> ";
		//	cin >> sort_choice;
		//	Clear_input_list();
		//	handle_sort_Room(*this, sort_choice);
		//}
		else if (choice == 5)
		{
			system("CLS");
			this->write_file();
			cout << endl << setw(70) << "" << "Da luu thay doi vao file!" << endl;
		}
		else if (choice == 6)
		{
			break;
		}
		else {
			system("cls");
			cout << endl << setw(70) << "" << "ERROR: Lua chon khong ton tai!" << endl << endl;
		}
		cout << endl;
	}
}