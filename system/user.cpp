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
	printf("�������û�����");
	cin >> name1;
	if (check_again1(all_user, name1)) {
		printf("���û�����ע�ᣡ������һ����\n");
		return;
	}
	user1.name = name1;
	printf("���������룺");
	cin >> user1.key;
	printf("ע��ɹ���\n");
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
	printf("�û�ID      �û���      ��ϵ��ʽ          ��ַ          Ǯ�����\n");
	for (const User& u : all_user) {
		cout << u.id << "        " << u.name << "      " << u.phone_num << "      " << u.address << "       " << flush;
		printf("%.2f\n", u.deposit);
	}
	printf("*****************************************************************\n");
}
bool user_signin(const vector<User>& all_user,string name1) {//�˴�string���ɸĳ��������ͣ�
	bool has = false;
	User want;
	for (const User& user1 : all_user) {
		if (user1.name == name1) { has = true; want = user1; break; }
	}
	if (!has) { printf("�û��������ڣ�\n"); return false; }
	printf("���������룺");
	cin >> name1;
	bool success = false;
	if (name1 == want.key) {
		if (!want.remain) { printf("���˺��ѱ����������\n"); return false; }
		printf("------��¼�ɹ���------\n");
		return true;
	}
	else {
		printf("���벻��ȷ����������������һ��:");
		cin >> name1;
		if (name1 == want.key) {
			if (!want.remain) { printf("���˺��ѱ����������\n"); return false; }
			printf("-----��¼�ɹ���------\n");
			return true;
		}
		else {
			printf("-----������󣬵�¼ʧ�ܡ�------\n");
			return false;
		}
	}
	return false;
}