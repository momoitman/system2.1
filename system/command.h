#pragma once
#include"all_data.h"
using namespace std;
//class Command {
//public:
//	string origin;
//	vector<string> split_string;
//	int select;
//	int from;
//	int where;
//	int contains;
//	int update;
//	int set;
//	int insert;
//	int values;
//	vector<string> split(string a, char k);
//	Command(string input,Data& all_data) {
//		select = -1, from = -1, where = -1, contains = -1, update = -1, set = -1, insert = -1, values = -1;
//		split_string = split(input, ' ');
//		int size = split_string.size();
//		for (int i = 0; i < size;i++) {
//			if (split_string[i] == "SELECT")select = i; if (split_string[i] == "FROM")from = i;
//			if (split_string[i] == "WHERE")where = i; if (split_string[i] == "CONTAINS")contains = i;
//			if (split_string[i] == "UPDATE")update = i; if (split_string[i] == "SET")set = i;
//			if (split_string[i] == "INSERT")insert = i; if (split_string[i] == "VALUES")values = i;
//		}
//	}
//};
//class Command_buyer :public Command {
//public:
//	Command_buyer(string input, Data& all_data,User& buyer):Command(input,all_data) {
//		select = 1;
//	}
//};
//class Command_sellor :public Command {
//public:
//	Command_sellor(string input, Data& all_data, User& sellor) :Command(input, all_data) {
//		;
//	}
//};
class Command {
public:
	string origin;
	string User_id;
	vector<string> split_string;
	int select;int from;
	int where;
	int contains;
	int update;
	int set;
	int insert;
	int values;
	bool manager;
	bool buyer;
	bool sellor;
	vector<string> split(string a, char k);
	string gettime();
	Command(string input, bool m, bool b, bool s,string idid) {
		input.pop_back();
		origin = input;
		select = -1, from = -1, where = -1, contains = -1, update = -1, set = -1, insert = -1, values = -1;
		manager = m, buyer = b, sellor = s; User_id = idid;
		split_string = split(input, ' ');
		int size = split_string.size();
		for (int i = 0; i < size; i++) {
			if (split_string[i] == "SELECT")select = i; if (split_string[i] == "FROM")from = i;
			if (split_string[i] == "WHERE")where = i; if (split_string[i] == "CONTAINS")contains = i;
			if (split_string[i] == "UPDATE")update = i; if (split_string[i] == "SET")set = i;
			if (split_string[i] == "INSERT")insert = i; if (split_string[i] == "VALUES")values = i;
		}
	}
	void operate(Data& all_data);
};