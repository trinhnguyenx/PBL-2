#include"Date.h"
using namespace std;

class Room {
private:
	string ma_phong, ten, trang_thai_phong, loai_phong, SDT;
	int he_So_gia;
	//bool gioi_tinh;
	Date1* ngay_thue;
	int gcb = 300;
	

public:
	Room* next;
	Room* previous;

	Room();
	Room(string, string, string, string, string, int, int, int, int);
	Room(const Room&);
	~Room();

	bool equals(const Room&);
	bool compare_id(string);
	bool compare_full_id(string);
	bool compare_name(string);
	bool compare_SDT(string);
	bool compare_trang_thai_phong(string);
	bool compare_loai_phong(string);
	bool compare_date_age(int, int, int);
	bool compare_age(const Room&, bool);
	bool compare_position(const Room&, bool);
	void show();
	void update_info(Room&);
	void copy_info(const Room&);
	int tinh_tien();
	double thuc_linh();
	int get_he_So_gia();
	int get_tinh_tien();


	void copy_attributes(Room& e);

	string get_ma_phong();
	string get_ten();
	string get_trang_thai_phong();
	string get_loai_phong();
	int get_ngay_thue();
	string get_SDT();
	string get_string_date();


	friend ostream& operator<<(ostream& o, const Room&);
	friend istream& operator>>(istream& in, Room&);
};