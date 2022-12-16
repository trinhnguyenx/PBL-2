
#include"Room.h"
#include<string>
#include<fstream>
#include<sstream>
class List1 {
public:
	Room* first;
	Room* last;

	List1();
	List1(Room&); // add first Room to the list.
	List1(const List1&);
	~List1();

	void read_file(string);
	void write_file();
	void append_file(Room&);

	int size_of_list();

	void display_list();
	void add_Room_at_first();
	void add_Room_at_last();
	void add_Room_at_last(Room&);
	void add_Room_at_specific_pos(int k); // k : position to add.
	bool update_Room_info(string);
	void delete_Room_at_first();
	void delete_Room_at_last();
	bool delete_Room_at_specific_pos(int pos);
	bool delete_Room(string);
	bool delete_Room_by_name(string);
	Room& search_Room_by_full_id(string);
	void search_and_print(int choice, string info);
	void print_statistics();


	bool check_if_contain(string id);
	bool check_if_contain_name(string name);
	bool check_if_contain_trang_thai_phong(string lien_lac);
	bool check_if_contain_loai_phong(string loai_phong);
	bool check_if_contain_full_id(string id);

	friend void swap(Room*, Room*);
	friend Room* partition1(Room*, Room*, bool);
	friend Room* partition2(Room*, Room*, bool);
	void position_sort(Room*, Room*, bool);

	void run();
};