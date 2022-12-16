#include"iostream"
#include<ctime>
using namespace std;

class Date1 {
private:
	int ngay;
	int thang;
	int nam;

public:
	Date1();
	Date1(int, int, int);
	Date1(const Date1&);

	bool compare_date(const Date1&, bool);
	void copy_date(const Date1&);
	friend void update_date(Date1&, int, int, int);
	friend ostream& operator<<(ostream&, const Date1&);
	string store_string_date();

	int get_ngay_thue();
	int get_thang_thue();
	int get_nam_thue();
	int get_tinh_tien();
};