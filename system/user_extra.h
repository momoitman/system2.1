#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"all_data.h"
using namespace std;
void user_interface(Data&);
void user_information(User& user,Data&);
void buyer_interface(Data&,User&);
void sellor_interface(Data&,User&);
string generate_deposite(const Data& all_data,const User& user);