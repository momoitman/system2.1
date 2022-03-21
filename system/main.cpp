#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"all_data.h"
#include"user_extra.h"
#include"admin_extra.h"
#include"calculate.h"
using namespace std;
vector<string> my_split(string a, char k) {
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
void initial_all() {
	FILE* p1 = fopen("commodity.txt", "w");
	FILE* p2 = fopen("user.txt", "w");
	FILE* p3 = fopen("order.txt", "w");
	FILE* p4 = fopen("calculate.txt", "w");
	FILE* p5 = fopen("commands.txt", "w");
	FILE* p6 = fopen("recharge.txt", "w");
	FILE* p7 = fopen("message.txt", "w");
	fprintf(p1, "��ƷID,����,�۸�,����,����,����ID,�ϼ�ʱ��,��Ʒ״̬\n");
	fprintf(p3, "����ID,��ƷID,���׵���,����,����ʱ��,����ID,���ID\n");
	fprintf(p2, "�û�ID,�û���,����,��ϵ��ʽ,��ַ,Ǯ�����,�û�״̬\n");
	fclose(p1); fclose(p2); fclose(p3); fclose(p4); fclose(p5); fclose(p6); fclose(p7);
}
void take(vector<Goods>&all_good) { 
	string buffer; char temp[500] = "123";
	FILE* p1 = fopen("commodity.txt", "r");
	if (fscanf(p1, "%s", temp) != 1) { cerr << "��ȡ�쳣" << endl; exit(-1); }
	while (!feof(p1)) {
		if (fscanf(p1, "%s", temp) == 1) {
			buffer = temp; Goods newgood;
			vector<string>temp1 = my_split(buffer, ',');
			newgood.id = temp1[0]; newgood.name = temp1[1];
			newgood.price = atof(temp1[2].c_str()); newgood.num_remain = atoi(temp1[3].c_str());
			newgood.description = temp1[4]; newgood.sellor_id = temp1[5];
			newgood.time = temp1[6]; newgood.state = (temp1[7] == "������") ? 1 : 2;
			all_good.push_back(newgood);
		}
	}
}
void take(vector<User>& all_user) {
	string buffer;
	char temp[500] = "231";
	FILE* p1 = fopen("user.txt", "r");
	if (fscanf(p1, "%s", temp) != 1) { cerr << "��ȡ�쳣"; exit(-1); };
	while (!feof(p1)) {
		if (fscanf(p1, "%s", temp) == 1) {
			buffer = temp;User newuser;
			vector<string>temp1 = my_split(buffer, ',');
			newuser.id = temp1[0];newuser.name = temp1[1];
			newuser.key = temp1[2]; newuser.phone_num = temp1[3];
			newuser.address = temp1[4]; newuser.deposit = atof(temp1[5].c_str());
			newuser.remain = (temp1[6] == "����") ? true : false;
			all_user.push_back(newuser);
		}
	}
}
void take(vector<Order>& all_order) { 
	string buffer;
	char temp[500] = "hahaha";
	FILE* p1 = fopen("order.txt", "r");
	if (fscanf(p1, "%s", temp) != 1) { cerr << "��ȡ�쳣"; exit(-1); };
	while (!feof(p1)) {
		if (fscanf(p1, "%s", temp) == 1) {
			buffer = temp; Order neworder;
			vector<string>temp1 = my_split(buffer, ',');
			neworder.id = temp1[0]; neworder.good_id = temp1[1];
			neworder.price = atof(temp1[2].c_str());
			neworder.num = atoi(temp1[3].c_str());
			neworder.time = temp1[4];
			neworder.sellor_id = temp1[5];
			neworder.buyer_id = temp1[6];
			all_order.push_back(neworder);
		}
	}
}
void take(vector<string>& all_recharge) {
	char buffer1[150] = "2", buffer2[150] = "2";
	FILE* fp = fopen("recharge.txt", "r");
	while (!feof(fp)) {
		if (fscanf(fp, "%s%s", buffer1, buffer2) == 2) {
			string a = buffer1, b = buffer2;
			a = a + " " + b;
			all_recharge.push_back(a);
		}
	}
}
void take(vector<string>& all_command,int) { 
	char buffer2[500];
	FILE* fp = fopen("commands.txt", "r");
	while (!feof(fp)) {
		if (fgets(buffer2, 250, fp) != NULL) {
			string a = buffer2;
			all_command.push_back(a);
		}
	}
}
void take(vector<Message>& all_message) {
	FILE* p1 = fopen("message.txt", "r");
	if (p1 == NULL) { cerr << "�����ļ���ȡ�쳣��\n"; return; }
	char temp[300];
	while (!feof(p1)) {
		if (fgets(temp, 290, p1) != NULL) {
			Message m;
			m.sender_id = temp;
			m.sender_id.pop_back();
			fgets(temp, 290, p1);
			m.sender_name = temp;
			m.sender_name.pop_back();
			fgets(temp, 290, p1);
			m.receiver_id = temp;
			m.receiver_id.pop_back();
			fgets(temp, 290, p1);
			m.receiver_name = temp;
			m.receiver_name.pop_back();
			fgets(temp, 290, p1);
			m.message = temp;
			m.message.pop_back();
			all_message.push_back(m);
		}
	}
}
void take_all(Data&all_data) { 
	//��ȡUser
	take(all_data.all_user);
	take(all_data.all_recharge);
	take(all_data.all_goods);
	take(all_data.all_command,1);
	take(all_data.all_order);
	take(all_data.all_message);
}
void update_data(const Data& all_data) {
	FILE* p1 = fopen("commodity.txt", "w"); FILE* p2 = fopen("user.txt", "w");
	FILE* p3 = fopen("order.txt", "w"); FILE* p4 = fopen("calculate.txt", "w");
	FILE* p5 = fopen("commands.txt", "w"); FILE* p6 = fopen("recharge.txt", "w");
	FILE* p7 = fopen("message.txt", "w");
	fprintf(p1, "��ƷID,����,�۸�,����,����,����ID,�ϼ�ʱ��,��Ʒ״̬\n");
	fprintf(p2, "�û�ID,�û���,����,��ϵ��ʽ,��ַ,Ǯ�����,�û�״̬\n");
	fprintf(p3, "����ID,��ƷID,���׵���,����,����ʱ��,����ID,���ID\n");
	for (const User& temp : all_data.all_user) {
		string aa; aa = temp.remain == true ? "����" : "���";
		fprintf(p2, "%s,%s,%s,%s,%s,%.lf,%s\n", temp.id.c_str(), temp.name.c_str(), temp.key.c_str(), temp.phone_num.c_str(), temp.address.c_str(), temp.deposit, aa.c_str());
	}
	for (const Goods& temp : all_data.all_goods) {
		string aa; aa = temp.state == 1 ? "������" : "���¼�";
		fprintf(p1, "%s,%s,%.1f,%d,%s,%s,%s,%s\n", temp.id.c_str(), temp.name.c_str(), temp.price, temp.num_remain, temp.description.c_str(), temp.sellor_id.c_str(), temp.time.c_str(), aa.c_str());
	}
	for (const Order& temp : all_data.all_order) {
		fprintf(p3, "%s,%s,%.1f,%d,%s,%s,%s\n", temp.id.c_str(), temp.good_id.c_str(), temp.price, temp.num, temp.time.c_str(), temp.sellor_id.c_str(), temp.buyer_id.c_str());
	}
	for (const string& temp : all_data.all_command) {
		fprintf(p5, "%s", temp.c_str());
	}
	for (const string& temp : all_data.all_recharge) {
		fprintf(p6, "%s\n", temp.c_str());
	}
	for (const Message& temp : all_data.all_message) {
		fprintf(p7, "%s\n%s\n%s\n%s\n%s\n", temp.sender_id.c_str(),temp.sender_name.c_str(), temp.receiver_id.c_str(), temp.receiver_name.c_str(),temp.message.c_str());
	}
	fclose(p1); fclose(p2); fclose(p3); fclose(p4); fclose(p5); fclose(p6); fclose(p7);
}
int main() {
	FILE* fp21 = fopen("commodity.txt", "r");
	if (fp21 == NULL)initial_all();
	if(fp21!=NULL)fclose(fp21);
	Data all_data;
	take_all(all_data);
	printf("***������ѧ���ʽ���Ҽ���Ĺ��ܽ����û��鿴��Ϣʱ���֡�***\n");
	printf("��һ�����л�����.txt�ļ����벻Ҫ����ɾ�����е�һ��������ᵼ�³����ȶ�����ɾ��commodity.txt�ᵼ������ϵͳ����!��\n");
	printf("*****ʹ�ó��������������˳�������ٹرմ��ڣ�����ᷢ�����ݶ�ʧ��*****\n");
	printf("=====��ӭ���붬�¼���Ʒ����ƽ̨��=====\n\n");
	printf("======������������000000��������ƽ̨��======\n");
	printf("====== ����Աadmin  ����123456 =============\n");
	bool init__ = false;
	while (true) {
		bool break__ = false;
		printf("===============================================================\n");
		printf("1.����Ա��¼ 2.�û�ע�� 3.�û���¼ 4.�˳����� 5.���������ô���\n");
		printf("===============================================================\n\n");
		printf("�����������");
		char input_1[40] = {};
		while (strcmp(input_1, "1") != 0 && strcmp(input_1, "2") != 0 && strcmp(input_1, "3") != 0 && strcmp(input_1, "4") != 0&&strcmp(input_1,"000000")!=0) {
			cin >> input_1;
			if (strcmp(input_1, "1") == 0)admin_interface(all_data);
			else if (strcmp(input_1, "2") == 0)user_register(all_data.all_user);
			else if (strcmp(input_1, "3") == 0)user_interface(all_data);
			else if (strcmp(input_1, "4") == 0) { break__ = true; break; }
			else if (strcmp(input_1, "000000") == 0)initial_all(), init__ = true;
			else if (strcmp(input_1, "5") == 0) {
				printf("���������ʽ��");
				string input22; cin >> input22;
				cal cal1(input22);
				cal1.calcu();
				printf("\n===============================================================\n");
				printf("1.����Ա��¼ 2.�û�ע�� 3.�û���¼ 4.�˳����� 5.���������ô���\n");
				printf("===============================================================\n\n");
				printf("�����������");
			}
			else printf("-----����������������룡-----\n");
		}
		if (break__)break;
		if (init__) { printf("=====���óɹ��������´�ƽ̨��=====\n"); break; }
	}
	if(not init__)update_data(all_data);
	return 0;
}