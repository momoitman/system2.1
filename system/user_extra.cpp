#include"user_extra.h"
#include"command.h"
#include"calculate.h"
void user_information(User& user,Data& all_data) {
	while (true) {
		printf("==============================================\n");
		printf("1.�鿴��Ϣ 2.�޸���Ϣ 3.��ֵ 4.�����û�������\n");
		printf("==============================================\n");
		printf("��������Ĳ���:");
		string buffer; cin >> buffer;
		if (buffer == "4")break;
		else if (buffer == "3") {
			printf("�������ֵ��");
			char b[100] = "0"; cin >> b;
			double a = atof(b);
			if (a <= 0) { printf("�������Ƿ���\n\n"); continue; }
			user.deposit += a;
			char buffer[100];
			sprintf(buffer, "%s %.1f", user.id.c_str(), a);
			string buffer1 = buffer;
			all_data.all_recharge.push_back(buffer1);
			printf("��ֵ�ɹ�����ǰ��%.1f\n\n", user.deposit);
		}
		else if (buffer == "1") {
			printf("******************\n");
			cout << "�û�ID:" << user.id << endl;
			cout << "�û�����" << user.name << endl;
			cout << "��ϵ��ʽ��" << user.phone_num << endl;
			cout << "��ַ��" << user.address << endl;
			printf("Ǯ����%.1f\n", user.deposit);
			printf("******************\n\n\n");
			printf("******************************������ʾ*************************************************************************\n");
			string shi = generate_deposite(all_data, user);
			cout << "���û����н��׼�¼�ı��ʽΪ��" << shi << endl;
			cal r(shi);
			printf("������������Ϊ��");
			r.calcu(); printf("\n");
			printf("***************************************************************************************************************\n\n\n");
		}
		else if (buffer == "2") {
			printf("��ѡ���޸ĵ����ԣ�1.�û��� 2.��ϵ��ʽ 3.��ַ����");
			string buffer2; cin >> buffer2;
			if (buffer2 == "2") {
				printf("�������޸ĺ����ϵ��ʽ��");
				cin >> user.phone_num;
			}
			else if (buffer2 == "3") {
				printf("�������޸ĺ�ĵ�ַ��");
				cin >> user.address;
			}
			else if (buffer2 == "1") {
				printf("�������޸ĺ���û�����");
				string name_; cin >> name_;
				bool success = true;
				for (User temp : all_data.all_user) {
					if (user.id != temp.id && name_ == temp.name) { printf("���û����ѱ�����ע�ᣡ\n"); success = false; }
				}
				if (success)user.name = name_;
			}
			else printf("��������\n");
		}
		else printf("�������\n");
	}
}
void user_interface(Data& all_data) {
	string name1;
	printf("�������û�����");
	cin >> name1;
	bool result1 = user_signin(all_data.all_user,name1);
	if (!result1)return;
	int size = all_data.all_user.size();
	int i = 0;
	for (; i < size; i++) {
		if (all_data.all_user[i].name == name1)break;
	}
	if (i == size) { cerr << "��Ѱ����\n"; exit(-1); }
	User& user = all_data.all_user[i];
	while (true) {
		printf("===============================================\n");
		printf("1.������� 2.�������� 3.������Ϣ���� 4.ע����¼\n");
		printf("===============================================\n");
		printf("��������Ĳ�����");
		string buffer; cin >> buffer;
		if (buffer == "4")break;
		else if (buffer == "3") user_information(user, all_data);
		else if (buffer == "2") sellor_interface(all_data, user);
		else if (buffer == "1")buyer_interface(all_data, user);
		else printf("��������\n\n");
	}
}
void buyer_interface(Data& all_data,User& buyer) { 
	while (true) {
		printf("========================================================================================\n");
		printf("1.�鿴��Ʒ�б� 2.������Ʒ 3.������Ʒ 4.�鿴��ʷ���� 5.�鿴��Ʒ��ϸ��Ϣ 6.�����û�������\n");
		printf("========================================================================================\n\n");
		printf("�����������"); string input; cin >> input;
		if (input == "6")break;
		else if (input == "1") {
			string result = "SELECT * FROM commodity\n";
			all_data.all_command.push_back(result);
			Command c(result, false, true, false, buyer.id);
			c.operate(all_data);
		}
		else if (input == "2") {
			printf("��������ƷID��");
			string id_good; cin >> id_good;
			int index2 = 0; int size = all_data.all_goods.size();
			bool not_find = true;
			for (; index2 < size; index2++) {
				if (all_data.all_goods[index2].id == id_good) {
					not_find = false;
					break;
				}
			}
			if (not_find) {
				printf("δ��ƥ�䵽����ƷID��Ӧ����Ʒ��\n\n");
				continue;
			}
			Goods& want = all_data.all_goods[index2];
			printf("������������");
			double num; cin >> num;
			if (num != (int)num || num <= 0) { printf("����Ƿ�\n\n"); }
			else {
				
				char buffer12[300] = "2";
				time_t t;
				struct tm* lt;
				time(&t);//��ȡUnixʱ�����
				lt = localtime(&t);//תΪʱ��ṹ��
				char result1[15];
				sprintf(result1, "%d-%d-%d", lt->tm_year + 1900, lt->tm_mon, lt->tm_mday);
				int id_int = all_data.all_order.size(); id_int += 1;
				char real_id[10];
				real_id[0] = 'T';
				real_id[1] = id_int / 100 + '0';
				real_id[2] = (id_int / 10) % 10 + '0';
				real_id[3] = id_int % 10 + '0';
				real_id[4] = '\0';
				sprintf(buffer12, "INSERT INTO order VALUES (%s,%s,%.1f,%d,%s,%s,%s)\n", real_id, id_good.c_str(), want.price, (int)num, result1, want.sellor_id.c_str(), buyer.id.c_str());
				string result2 = buffer12;
				all_data.all_command.push_back(result2);
				if ((int)num > want.num_remain) { printf("��Ʒ�������㣡\n\n"); continue; }
				if (num * want.price > buyer.deposit) { printf("���㣡�޷�����\n"); continue; }
				char buffer[300];
				int remaining = want.num_remain - (int)num;
				sprintf(buffer, "UPDATE commodity SET ���� = %d WHERE ��ƷID = %s\n", remaining, id_good.c_str());
				string result = buffer;
				all_data.all_command.push_back(result);
				Command c(result, false, true, false, buyer.id);
				Command d(result2, false, true, false, buyer.id);
				c.operate(all_data);
				d.operate(all_data);
				printf("***************************\n");
				printf("�������ѣ�\n");
				printf("����ʱ�䣺"); cout << result1 << endl;
				printf("���׵���%.1f\n", want.price);
				printf("����������%d\n", (int)num);
				printf("����״̬���ɹ�\n");
				printf("������"); cout << buyer.deposit << endl;
				printf("***************************\n\n\n");
				if (remaining == 0) {
					string result4 = "UPDATE commodity SET ��Ʒ״̬ = ���¼� WHERE ��ƷID = ";
					result4 = result4 + want.id + "\n";
					Command e(result4, true, false, false, "admin_");
					e.operate(all_data);
				}
			}
		}
		else if (input == "3") {
			printf("��������Ʒ���ƣ�"); string input; cin >> input;
			string result = "SELECT * FROM commodity WHERE ���� CONTAINS ";
			result = result + input + "\n";
			all_data.all_command.push_back(result);
			Command c(result, false, true, false, buyer.id); c.operate(all_data);
		}
		else if (input == "4") {
			string result = "SELECT * FROM order\n";
			all_data.all_command.push_back(result);
			Command c(result, false, true, false, buyer.id);
			c.operate(all_data);
		}
		else if (input == "5") {
			printf("����������Ҫ�鿴����ƷID��"); string result = "SELECT * FROM commodity WHERE ��ƷID CONTAINS ";
			string input; cin >> input;
			result = result + input + "\n";
			all_data.all_command.push_back(result);
			Command c(result, false, true, false, buyer.id); 
			c.operate(all_data);
		}
		else printf("�����������������롣\n");
	}
}
void sellor_interface(Data& all_data,User& sellor) { 
	while (true) {
		printf("====================================================================================\n");
		printf("1.������Ʒ 2.�鿴������Ʒ 3.�޸���Ʒ��Ϣ 4.�¼���Ʒ 5.�鿴��ʷ���� 6.�����û�������\n");
		printf("====================================================================================\n\n");
		printf("�����������"); string input; cin >> input;
		if (input == "6")break;
		else if (input == "1") {
			string good_name, good_description;
			printf("��������Ʒ���ƣ�"); cin >> good_name;
			double price = 0, num;
			printf("��������Ʒ�۸񣨴������С��������������"); cin >> price;
			if (price <= 0) { printf("����Ƿ���\n"); break; }
			printf("��������Ʒ���������������������"); cin >> num;
			if (num <= 0 || num != (int)num) { printf("����Ƿ���\n"); break; }
			printf("��������Ʒ������"); cin >> good_description;
			char buffer[220];
			sprintf(buffer, "INSERT INTO commodity VALUES (%s,%.1f,%d,%s)\n", good_name.c_str(), price, (int)num, good_description.c_str());
			string result = buffer;
			all_data.all_command.push_back(result);
			Command c(result, false, false, true, sellor.id); 
			c.operate(all_data);
		}
		else if (input == "2") {
			string result = "SELECT * FROM commodity\n";
			all_data.all_command.push_back(result);
			Command temp(result, false, false, true, sellor.id);
			temp.operate(all_data);
		}
		else if (input == "4") {
			printf("������Ҫ�¼ܵ���ƷID��"); string input; cin >> input;
			string result = "UPDATE commodity SET ��Ʒ״̬ = ���¼� WHERE ��ƷID = ";
			result = result + input + "\n";
			all_data.all_command.push_back(result);
			Command c(result, false, false, true, sellor.id);
			c.operate(all_data);
		}
		else if (input == "5") {
			string result = "SELECT * FROM order\n";
			all_data.all_command.push_back(result);
			Command c(result, false, false, true, sellor.id);
			c.operate(all_data);
		}
		else if (input == "3") {
			string id_input="", attribute_input="";
			string attribute;
			double price;
			printf("�����뱻�޸ĵ���ƷID��"); cin >> id_input;
			printf("�����뱻�޸ĵ���Ʒ���ԣ�1.�۸� 2.��������"); cin >> attribute_input;
			if (attribute_input != "1" && attribute_input != "2") { printf("��������\n"); continue; }
			if (attribute_input == "1") {
				printf("�����뱻�޸ĵ���Ʒ�۸�"); cin >> price;
				if (price <= 0) { printf("�۸�����Ƿ���\n"); continue; }
			}
			if (attribute_input == "2") {
				printf("�����뱻�޸ĵ���Ʒ������"); cin >> attribute;
			}
			char buffer[250] = "";
			if (attribute_input == "1")sprintf(buffer, "UPDATE commodity SET �۸� = %.1f WHERE ��ƷID = %s\n", price, id_input.c_str());
			if (attribute_input == "2")sprintf(buffer, "UPDATE commodity SET ���� = %s WHERE ��ƷID = %s\n",attribute.c_str(),id_input.c_str());
			string result = buffer;
			all_data.all_command.push_back(result);
			Command c(result, false, false, true, sellor.id); 
			c.operate(all_data);
		}
		else printf("�����������������롣\n");
	}
}
string generate_deposite(const Data& all_data,const User& user) {
	string result;
	for (const string& k : all_data.all_recharge) {
		if (user.id == k.substr(0, 4)) {
			if (result.empty()) {
				result+=k.substr(5);
			}
			else {
				result += "+" + k.substr(5);
			}
		}
	}
	for (const Order& k : all_data.all_order) {
		if (k.sellor_id == user.id) {
			if (result.empty()) {
				char temp22[20];
				sprintf(temp22, "%.1f", k.price);
				result += to_string(k.num) + "*" + string(temp22);
			}
			else {
				char temp22[20];
				sprintf(temp22, "%.1f", k.price);
				result += "+" + to_string(k.num) + "*" + string(temp22);
			}
		}
		if (k.buyer_id == user.id) {
			char temp22[20];
			sprintf(temp22, "%.1f", k.price);
			result += "-" + to_string(k.num) + "*" + string(temp22);
		
		}
	}
	return result;
}