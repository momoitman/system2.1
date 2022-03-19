#pragma once
#include<string>
#include<vector>
using namespace std;
class Goods {
public:
	int id_int;
	int num_remain;
	int state;//1ÏúÊÛ 2ÏÂ¼Ü
	double price;
	string id;
	string sellor_id;
	string name;
	string time;
	string description;
	Goods() {
		id_int = 0, num_remain = 1, state = 1, price = 0;
		id = ""; sellor_id = ""; name = ""; time = ""; description = "";
	}
};
void all_goods_output();//manager
void all_goods_output(const string& id);//sellor
void find_goods(const string& name, bool manager);