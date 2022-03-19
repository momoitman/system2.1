#pragma once
#include<string>
#include<vector>
using namespace std;
class User {
public:
	bool remain;
	int id_int;
	double deposit;
	string id;
	string name;
	string key;
	string phone_num;
	string address;
	User() { remain = true; id_int = 0; deposit = 0; id = ""; key = ""; phone_num = "ÔÝÎÞ"; address = "ÔÝÎÞ"; }
};
void user_register(vector<User>&);
bool check_again1(const vector<User>&,const string&);
void id_change(string&, int);
void all_user_output(const vector<User>&);
bool user_signin(const vector<User>&,string);