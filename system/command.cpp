#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"command.h"
using namespace std;
vector<string> Command::split(string a, char k) {
	vector<string> result;
	int last = 0, current = 0, size = a.size();
	for (int i = 0; i < size; i++) {
		if (a[i] == k) {
			last = current; current = i + 1;
			string temp = a.substr(last, i - last);
			result.push_back(temp);
		}
	}
	string temp = a.substr(current);
	result.push_back(temp);
	return result;
}
string Command::gettime() {
	time_t t;
	struct tm* lt;
	time(&t);//��ȡUnixʱ�����
	lt = localtime(&t);//תΪʱ��ṹ��
	char result[15];
	sprintf(result, "%d-%d-%d", lt->tm_year + 1900, lt->tm_mon, lt->tm_mday);
	string real = result;
	return real;
}
void Command::operate(Data& all_data) {
	if (origin[0] == 'S' && origin[origin.size() - 1] == 'y') {
		if (manager) {
			printf("************************************************************************\n");
			printf("��ƷID  ����      �۸�      �ϼ�ʱ��      ����ID     ����	��Ʒ״̬\n");
			for (const Goods& k : all_data.all_goods) {
				cout << k.id << " " << k.name << " ";
				printf("%d   ", (int)k.price);
				cout << k.time << "   " << k.sellor_id << "    " << k.num_remain << "     ";
				cout << (k.state == 1 ? "������" : "���¼�") << endl;
			}
			printf("************************************************************************\n");
		}
		else if (buyer) {
			printf("************************************************************************\n");
			printf("��ƷID  ����      �۸�      �ϼ�ʱ��      ����ID     ����	��Ʒ״̬\n");
			for (const Goods& k : all_data.all_goods) {
				if (k.state == 1) {
					cout << k.id << " " << k.name << " " << k.price << "   " << k.time << "   " << k.sellor_id << "    " << k.num_remain << "     ";
					cout << (k.state == 1 ? "������" : "���¼�") << endl;
				}
			}
			printf("************************************************************************\n");
		}
		else if (sellor) {
			printf("************************************************************************\n");
			printf("��ƷID  ����      �۸�      �ϼ�ʱ��      ����ID     ����	��Ʒ״̬\n");
			for (const Goods& k : all_data.all_goods) {
				if (k.sellor_id == User_id) {
					cout << k.id << " " << k.name << " " << k.price << "   " << k.time << "   " << k.sellor_id << "    " << k.num_remain << "     ";
					cout << (k.state == 1 ? "������" : "���¼�") << endl;
				}
			}
			printf("************************************************************************\n");
		}
	}//���������Ʒ
	else if (split_string[0] == "SELECT" && split_string[split_string.size() - 1] == "order") {
		printf("***********************************************************\n");
		printf("����ID  ��ƷID  ���׵��� ����   ����ʱ��   ����ID   ���ID\n");
		for (const Order& temp : all_data.all_order) {
			bool legal = manager;
			legal = legal || (buyer && User_id == temp.buyer_id);
			legal = legal || (sellor && User_id == temp.sellor_id);
			if (legal) {
				cout << temp.id << "   " << temp.good_id << "   " << temp.price << "  " << temp.time << "    ";
				cout << temp.num << "      " << temp.sellor_id << "     " << temp.buyer_id << endl;
			}
		}
		printf("**********************************************************\n");
	}
	else if (split_string[0] == "UPDATE" && split_string[1] == "commodity" && split_string[3] == "����") {
		for (Goods& k : all_data.all_goods) {
			if (k.id == split_string[9]) {
				int num = atoi(split_string[5].c_str());
				k.num_remain = num;
			}
		}
	}
	else if (split_string[0] == "INSERT" && split_string[2] == "order" && split_string[3] == "VALUES") {
		string kuohao = split_string[4];
		kuohao.pop_back();
		kuohao = kuohao.substr(1);
		vector<string> container = split(kuohao, ',');
		Order new_order;
		new_order.id = container[0]; new_order.good_id = container[1];
		new_order.price = atof(container[2].c_str()); new_order.num = atoi(container[3].c_str());
		new_order.time = container[4]; new_order.sellor_id = container[5]; new_order.buyer_id = container[6];
		all_data.all_order.push_back(new_order);
		for (User& temp : all_data.all_user) {
			if (temp.id == new_order.sellor_id) {
				temp.deposit += new_order.price * new_order.num;
			}
			if (temp.id == new_order.buyer_id) {
				temp.deposit -= new_order.price * new_order.num;
			}
		}
	}
	else if (split_string[0] == "SELECT" && split_string[3] == "order") {
		printf("***************************************************************\n");
		printf("����ID  ��ƷID  ���׵���  ����   ����ʱ��  ����ID  ���ID\n");
		for (const Order& k : all_data.all_order) {
			if (manager || (buyer && User_id == k.buyer_id) || (sellor && User_id == k.sellor_id)) {
				cout << k.id << "     " << k.good_id << "    " << flush;
				printf("%.1f   ", k.price);
				printf("%d    ", k.num);
				cout << k.time << "  " << k.sellor_id << "    " << k.buyer_id << endl;
			}
		}
		printf("***************************************************************\n");
	}
	else if (split_string[0] == "SELECT" && split_string[split_string.size() - 1] == "user") {
		printf("*************************************************************************\n");
		printf("�û�ID  �û���    ��ϵ��ʽ         ��ַ            Ǯ�����     �û�״̬\n");
		for (const User& temp : all_data.all_user) {
			cout << temp.id << "    " << temp.name << "    " << temp.phone_num << "      " << temp.address << "    ";
			printf("%.1f      ", temp.deposit);
			cout << (temp.remain ? "����" : "���") << endl;
		}
		printf("**************************************************************************\n");
	}
	else if (split_string[0] == "INSERT" && split_string[2] == "commodity") {
		string kkk = split_string[4].substr(1);
		kkk.pop_back();
		vector<string> new_split = split(kkk, ',');
		printf("��ȷ�Ϸ������Ʒ��Ϣ����\n");
		printf("************************************\n");
		printf("��Ʒ���ƣ�"); cout << new_split[0] << endl;
		printf("��Ʒ�۸�%.1f\n", atof(new_split[1].c_str()));
		printf("��Ʒ������%d\n", atoi(new_split[2].c_str()));
		cout << "��Ʒ������" << new_split[3] << endl;
		printf("************************************\n");
		while (true) {
			printf("��ȷ��Ҫ��������Ʒ��(y/n)");
			string input3; cin >> input3;
			if (input3 == "y") { 
				Goods append1;
				append1.description = new_split[3];
				int size = all_data.all_goods.size();
				append1.id_int = size + 1;
				char real_id[10];
				real_id[0] = 'M';
				real_id[1] = append1.id_int / 100 + '0';
				real_id[2] = (append1.id_int / 10) % 10 + '0';
				real_id[3] = append1.id_int % 10 + '0';
				real_id[4] = '\0';
				append1.id = real_id;
				append1.name = new_split[0];
				append1.num_remain = atoi(new_split[2].c_str());
				append1.price = atof(new_split[1].c_str());
				append1.sellor_id = User_id;
				append1.state = 1;
				append1.time = gettime();
				all_data.all_goods.push_back(append1);
				printf("������Ʒ�ɹ���\n\n");
				break;
			}
			else if (input3 == "n") { printf("ȡ���ɹ���\n\n"); break; }
			else printf("�����������������룡\n");
		}
	}
	else if (split_string[0] == "UPDATE" && split_string[1] == "commodity" && split_string[3] == "��Ʒ״̬"&&split_string[7]=="��ƷID") {
	bool not_find = true; int size = split_string.size();
		for (Goods& k : all_data.all_goods) {
			if (k.id == split_string[size - 1]) {
				not_find = false;
				if (sellor && User_id != k.sellor_id) {
					printf("��δ����������ƷID��Ӧ����Ʒ��\n");
					break;
				}
				else if (k.state != 1) {
					printf("����Ʒ�Ѿ��¼ܡ�\n");
					break;
				}
				else {
					if (User_id != "admin_") {
						printf("ȷ��Ҫ�¼ܸ���Ʒ��\n");
						printf("************************************************************************\n");
						printf("��ƷID  ����      �۸�      �ϼ�ʱ��      ����ID     ����	��Ʒ״̬\n");
						cout << k.id << " " << k.name << " ";
						printf("%d   ", (int)k.price);
						cout << k.time << "   " << k.sellor_id << "    " << k.num_remain << "     ";
						cout << (k.state == 1 ? "������" : "���¼�") << endl;
						printf("************************************************************************\n");
						printf("��ѡ��y/n��");
						string input_1; cin >> input_1;
						while (true) {
							if (input_1 == "y") { k.state = 2; printf("�¼ܳɹ���\n"); break; }
							else if (input_1 == "n") { printf("ȡ���ɹ���\n"); break; }
							else printf("����������������룡\n");
						}
						break;
					}
					else if(User_id=="admin_") {
						k.state = 2;
					}
				}
			}
		}
		if (not_find&&manager)printf("δ��ѯ������ƷID��Ӧ����Ʒ��\n");
		if (not_find && sellor)printf("��δ����������ƷID��Ӧ����Ʒ��\n");
	}
	else if (split_string[0] == "SELECT" && split_string[3] == "commodity" && split_string[4] == "WHERE" && split_string[5] == "����") {
		printf("************************************************************************\n");
		printf("��ƷID  ����      �۸�      �ϼ�ʱ��      ����ID     ����	��Ʒ״̬\n");
		for (const Goods& k : all_data.all_goods) {
			string::size_type idx;
			idx = k.name.find(split_string[7]);
			if (idx != k.name.npos) {
				if (manager || (buyer && k.state == 1)) {
					cout << k.id << " " << k.name << " " << k.price << "   " << k.time << "   " << k.sellor_id << "    " << k.num_remain << "     ";
					cout << (k.state == 1 ? "������" : "���¼�") << endl;
				}
			}
		}
		printf("************************************************************************\n");
	}
	else if (split_string[0] == "SELECT" && split_string[3] == "commodity" && split_string[4] == "WHERE" && split_string[5] == "��ƷID") {
		bool not_find = true;
		for (const Goods& k : all_data.all_goods) {
			if (k.id == split_string[7]) {
				not_find = false;
				if (k.state != 1) { printf("δ�ҵ�����Ʒ������û�в鿴����Ʒ��Ϣ��Ȩ�ޣ�\n"); break; }
				printf("************************************\n");
				printf("��ƷID��%s\n", k.id.c_str());
				printf("��Ʒ�۸�%.1f\n", k.price);
				printf("�ϼ�ʱ�䣺%s\n", k.time.c_str());
				printf("��Ʒ������%s\n", k.description.c_str());
				printf("��Ʒ���ң�%s\n", k.sellor_id.c_str());
				printf("************************************\n");
				break;
			}
		}
		if(not_find)printf("δ�ҵ�����Ʒ������û�в鿴����Ʒ��Ϣ��Ȩ�ޣ�\n");
	}
	else if (split_string[0] == "UPDATE" && split_string[1] == "commodity" && split_string[2] == "SET" && (split_string[3]=="�۸�"||split_string[3]=="����")) {
		bool not_find = true;
		for (Goods& k : all_data.all_goods) {
			if (k.id == split_string[9]) {
				not_find = false;
				if (k.sellor_id != User_id) { printf("δ�ҵ�����Ʒ������û���޸ĸ���Ʒ��Ȩ�ޣ�\n"); break; }
				if (split_string[3] == "�۸�") { k.price = atof(split_string[5].c_str()); printf("�޸ĳɹ���\n"); break; }
				if (split_string[3] == "����") { k.description = split_string[5]; printf("�޸ĳɹ���\n"); break; }
				else { printf("ϵͳ���������������뷵���������˳�����ϵ�����ߡ�\n"); break; }
			}
		}
		if(not_find)printf("δ�ҵ�����Ʒ������û���޸ĸ���Ʒ��Ȩ�ޣ�\n");
	}
	else if (split_string[0] == "UPDATE" && split_string[1] == "commodity" && split_string[2] == "SET" && split_string[3] == "��Ʒ״̬" && split_string[7] == "����ID") {
		for (Goods& k : all_data.all_goods) {
			if (k.sellor_id == split_string[9])k.state = 2;
		}
	}
	else if (split_string[0] == "UPDATE" && split_string[1] == "user" && split_string[2] == "SET" && split_string[3] == "�û�״̬" && split_string[7] == "�û�ID") {
		for (User& k : all_data.all_user) {
			if (k.id == split_string[9]) { 
				k.remain = false;
			}
		}
	}
}