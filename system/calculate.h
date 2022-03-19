#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stack>
#include<vector>
#include<string>
#include<iostream>
using namespace std;
class cal {
private:
    string origin;
    string correct_;
public:
	bool is_num(char c);
	string non_space(const string& k);
	bool legal_kuonum(const string& s);
	bool legal_char(const string& s);
	bool legal_allinput(const string& s);
    vector<string> hou(string& s);
    cal(string s) {
        origin = s;
        correct_ = non_space(s);
    }
    string calcu();
    string calcu_hou(const vector<string>& a);
    void append_zero(string& s);
    int legal_logic();
};