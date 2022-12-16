#include<iostream>
#include"List1.h"
using namespace std;

int main() {
	cout << "--------------------" << "Vui long nhan phim de chon chuc nang: " << "----------------------" << endl;
	//cout << "-----------------------------" << "1. Quan Ly Nhan Vien" << "-----------------------------------" << endl;
	cout << "-----------------------------" << "2. Quan Ly Khach Hang" << "-----------------------------------" << endl;
	List1 list1;
	list1.read_file("records19.txt");
	list1.run();
	return 0;
}
