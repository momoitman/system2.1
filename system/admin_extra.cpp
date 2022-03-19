#include"admin_extra.h"
void admin_interface(Data& all_data) {
	printf("请输入管理员姓名：");
	string temp; cin >> temp;
	if (temp != "admin") { cout << "管理员姓名输入错误。" << endl; return; }
	printf("请输入密码："); cin >> temp;
	if (temp != "123456") { cout << "密码输入错误。" << endl; return; }
	printf("\n-----登录成功！-----\n\n");
	while (true) {
		printf("====================================================================================\n");
		printf("1.查看所有商品 2.搜索商品 3.下架商品 4.查看所有订单 5.查看所有用户 6.封禁用户 7.注销\n");
		printf("====================================================================================\n\n");
		printf("输入操作：");
		cin >> temp;
		if (temp == "7")break;
		else if (temp == "1") {
			string result = "SELECT * FROM commodity\n";
			all_data.all_command.push_back(result);
			Command c(result, true, false, false,"admin");
			c.operate(all_data);
		}
		else if (temp == "2") {
			printf("请输入商品名称：");
			string name1; cin >> name1;
			string result = "SELECT * FROM commodity WHERE 名称 CONTAINS ";
			result = result + name1 + "\n";
			all_data.all_command.push_back(result);
			Command c(result, true, false, false, "admin");
			c.operate(all_data);
		}
		else if (temp == "3") {
			printf("请输入要下架的商品ID："); string id_temp; cin >> id_temp;
			string result = "UPDATE commodity SET 商品状态 = 已下架 WHERE 商品ID = ";
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
			printf("请输入要封禁的用户ID："); string id_input; cin >> id_input;
			string result1 = "UPDATE commodity SET 商品状态 = 已下架 WHERE 卖家ID = ";
			string result2 = "UPDATE user SET 用户状态 = 封禁 WHERE 用户ID = ";
			result1 = result1 + id_input + "\n", result2 = result2 + id_input + "\n";
			all_data.all_command.push_back(result1);
			all_data.all_command.push_back(result2);
			bool not_find = true;
			for (const User& temp : all_data.all_user) {
				if (temp.id == id_input) {
					not_find = false;
					if (!temp.remain) { printf("该用户已被封禁！\n\n"); continue; }
					printf("确定封禁该用户吗？\n");
					printf("*****************************************************************************\n");
					printf("用户ID  用户名    联系方式         地址            钱包余额     用户状态\n");
					cout << temp.id << "    " << temp.name << "    " << temp.phone_num << "      " << temp.address << "    ";
					printf("%.1f      ", temp.deposit);
					cout << (temp.remain ? "正常" : "封禁") << endl;
					printf("*****************************************************************************\n");
					printf("请选择(y/n)：");
					bool destroy = false;
					while (true) {
						string buffer; cin >> buffer;
						if (buffer == "n") { printf("取消成功！\n"); break; }
						else if (buffer == "y") { printf("封禁成功！\n\n"); destroy = true; break; }
						else printf("输入错误！请重新输入！\n");

					}
					if(destroy){
						Command c(result1, true, false, false, "admin"), d(result2, true, false, false, "admin");
						c.operate(all_data); d.operate(all_data);
					}
					break;
				}
			}
			if (not_find)printf("未能找到该用户ID对应的用户！\n");
		}
		else printf("输入错误。\n");
	}
}