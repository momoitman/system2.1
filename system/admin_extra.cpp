#include"admin_extra.h"
void admin_interface(Data& all_data) {
	printf("���������Ա������");
	string temp; cin >> temp;
	if (temp != "admin") { cout << "����Ա�����������" << endl; return; }
	printf("���������룺"); cin >> temp;
	if (temp != "123456") { cout << "�����������" << endl; return; }
	printf("\n-----��¼�ɹ���-----\n\n");
	while (true) {
		printf("====================================================================================\n");
		printf("1.�鿴������Ʒ 2.������Ʒ 3.�¼���Ʒ 4.�鿴���ж��� 5.�鿴�����û� 6.����û� 7.ע��\n");
		printf("====================================================================================\n\n");
		printf("���������");
		cin >> temp;
		if (temp == "7")break;
		else if (temp == "1") {
			string result = "SELECT * FROM commodity\n";
			all_data.all_command.push_back(result);
			Command c(result, true, false, false,"admin");
			c.operate(all_data);
		}
		else if (temp == "2") {
			printf("��������Ʒ���ƣ�");
			string name1; cin >> name1;
			string result = "SELECT * FROM commodity WHERE ���� CONTAINS ";
			result = result + name1 + "\n";
			all_data.all_command.push_back(result);
			Command c(result, true, false, false, "admin");
			c.operate(all_data);
		}
		else if (temp == "3") {
			printf("������Ҫ�¼ܵ���ƷID��"); string id_temp; cin >> id_temp;
			string result = "UPDATE commodity SET ��Ʒ״̬ = ���¼� WHERE ��ƷID = ";
			result = result + id_temp + "\n";
			all_data.all_command.push_back(result);
			Command c(result, true, false, false, "admin");
			c.operate(all_data);
		}
		else if (temp == "4") {
			string result = "SELECT * FROM order\n";
			all_data.all_command.push_back(result);
			Command c(result, true, false, false, "admin"); c.operate(all_data);
		}
		else if (temp == "5") {
			string result = "SELECT * FROM user\n";
			all_data.all_command.push_back(result);
			Command c(result, true, false, false,"admin"); c.operate(all_data);
		}
		else if (temp == "6") {
			printf("������Ҫ������û�ID��"); string id_input; cin >> id_input;
			string result1 = "UPDATE commodity SET ��Ʒ״̬ = ���¼� WHERE ����ID = ";
			string result2 = "UPDATE user SET �û�״̬ = ��� WHERE �û�ID = ";
			result1 = result1 + id_input + "\n", result2 = result2 + id_input + "\n";
			all_data.all_command.push_back(result1);
			all_data.all_command.push_back(result2);
			bool not_find = true;
			for (const User& temp : all_data.all_user) {
				if (temp.id == id_input) {
					not_find = false;
					if (!temp.remain) { printf("���û��ѱ������\n\n"); continue; }
					printf("ȷ��������û���\n");
					printf("*****************************************************************************\n");
					printf("�û�ID  �û���    ��ϵ��ʽ         ��ַ            Ǯ�����     �û�״̬\n");
					cout << temp.id << "    " << temp.name << "    " << temp.phone_num << "      " << temp.address << "    ";
					printf("%.1f      ", temp.deposit);
					cout << (temp.remain ? "����" : "���") << endl;
					printf("*****************************************************************************\n");
					printf("��ѡ��(y/n)��");
					bool destroy = false;
					while (true) {
						string buffer; cin >> buffer;
						if (buffer == "n") { printf("ȡ���ɹ���\n"); break; }
						else if (buffer == "y") { printf("����ɹ���\n\n"); destroy = true; break; }
						else printf("����������������룡\n");

					}
					if(destroy){
						Command c(result1, true, false, false, "admin"), d(result2, true, false, false, "admin");
						c.operate(all_data); d.operate(all_data);
					}
					break;
				}
			}
			if (not_find)printf("δ���ҵ����û�ID��Ӧ���û���\n");
		}
		else printf("�������\n");
	}
}