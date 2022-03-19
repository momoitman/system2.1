#pragma once
#include<vector>
#include<string>
#include"goods.h"
#include"order.h"
#include"user.h"
#include"admin.h"
using namespace std;
class Data {
public:
	vector<Order> all_order;
	vector<Goods> all_goods;
	vector<User> all_user;
	vector<string> all_command;
	vector<string> all_recharge;
};