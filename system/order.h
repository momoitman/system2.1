#pragma once
#include<string>
#include<vector>
using namespace std;
class Order {
public:
	int id_int;
	int num;
	double price;
	string id;
	string time;
	string good_id;
	string sellor_id;
	string buyer_id;
	Order() { id_int = 0, num = 0, price = 0;
	id = ""; time = ""; sellor_id = ""; buyer_id = ""; good_id = "";
	}
};