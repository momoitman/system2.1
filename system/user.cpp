#define _CRT_SECURE_NO_WARNINGS
#include"user.h"
#include<iostream>
using namespace std;
bool check_again1(const vector<User>& all_user,const string&name1) {
	bool again = false;
	int size1 = all_user.size();
	for (int index = 0; index < size1; index++) {
		if (all_user[index].name==name1) {
			again = true; break;
		}
	}
	return again;
}
void id_change(string& real_id1, int id_int) {
	char real_id[10];
	real_id[0] = 'U';
	real_id[1] = id_int / 100 + '0';
	real_id[2] = (id_int / 10) % 10 + '0';
	real_id[3] = id_int % 10 + '0';
	real_id[4] = '\0';
	real_id1 = real_id;
}
void user_register(vector<User>& all_user) {
	User user1;
	string name1;
	printf("请输入用户名：");
	cin >> name1;
	if (check_again1(all_user, name1)) {
		printf("该用户名已注册！返回上一级！\n");
		return;
	}
	user1.name = name1;
	printf("请输入密码：");
	cin >> user1.key;
	printf("注册成功！\n");
	if (all_user.size() == 0) {
		user1.id_int = 1;
	}
	else { 
		int size = all_user.size(); user1.id_int = size + 1;
	}
	id_change(user1.id, user1.id_int);
	user1.remain = true;
	all_user.push_back(user1);
}
void all_user_output(const vector<User>& all_user) {
	printf("*****************************************************************\n");
	printf("用户ID      用户名      联系方式          地址          钱包余额\n");
	for (const User& u : all_user) {
		cout << u.id << "        " << u.name << "      " << u.phone_num << "      " << u.address << "       " << flush;
		printf("%.2f\n", u.deposit);
	}
	printf("*****************************************************************\n");
}
bool user_signin(const vector<User>& all_user,string name1) {//此处string不可改成引用类型！
	bool has = false;
	User want;
	for (const User& user1 : all_user) {
		if (user1.name == name1) { has = true; want = user1; break; }
	}
	if (!has) { printf("用户名不存在！\n"); return false; }
	printf("请输入密码：");
	cin >> name1;
	bool success = false;
	if (name1 == want.key) {
		if (!want.remain) { printf("该账号已被封禁！！！\n"); return false; }
		printf("------登录成功！------\n");
		return true;
	}
	else {
		printf("密码不正确！您还可以再输入一次:");
		cin >> name1;
		if (name1 == want.key) {
			if (!want.remain) { printf("该账号已被封禁！！！\n"); return false; }
			printf("-----登录成功！------\n");
			return true;
		}
		else {
			printf("-----密码错误，登录失败。------\n");
			return false;
		}
	}
	return false;
}