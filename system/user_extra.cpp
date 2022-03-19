#include"user_extra.h"
#include"command.h"
#include"calculate.h"
void user_information(User& user,Data& all_data) {
	while (true) {
		printf("==============================================\n");
		printf("1.查看信息 2.修改信息 3.充值 4.返回用户主界面\n");
		printf("==============================================\n");
		printf("请输入你的操作:");
		string buffer; cin >> buffer;
		if (buffer == "4")break;
		else if (buffer == "3") {
			printf("请输入充值金额：");
			char b[100] = "0"; cin >> b;
			double a = atof(b);
			if (a <= 0) { printf("金额输入非法！\n\n"); continue; }
			user.deposit += a;
			char buffer[100];
			sprintf(buffer, "%s %.1f", user.id.c_str(), a);
			string buffer1 = buffer;
			all_data.all_recharge.push_back(buffer1);
			printf("充值成功，当前余额：%.1f\n\n", user.deposit);
		}
		else if (buffer == "1") {
			printf("******************\n");
			cout << "用户ID:" << user.id << endl;
			cout << "用户名：" << user.name << endl;
			cout << "联系方式：" << user.phone_num << endl;
			cout << "地址：" << user.address << endl;
			printf("钱包余额：%.1f\n", user.deposit);
			printf("******************\n\n\n");
			printf("******************************额外显示*************************************************************************\n");
			string shi = generate_deposite(all_data, user);
			cout << "该用户所有交易记录的表达式为：" << shi << endl;
			cal r(shi);
			printf("计算器计算结果为：");
			r.calcu(); printf("\n");
			printf("***************************************************************************************************************\n\n\n");
		}
		else if (buffer == "2") {
			printf("请选择修改的属性（1.用户名 2.联系方式 3.地址）：");
			string buffer2; cin >> buffer2;
			if (buffer2 == "2") {
				printf("请输入修改后的联系方式：");
				cin >> user.phone_num;
			}
			else if (buffer2 == "3") {
				printf("请输入修改后的地址：");
				cin >> user.address;
			}
			else if (buffer2 == "1") {
				printf("请输入修改后的用户名：");
				string name_; cin >> name_;
				bool success = true;
				for (User temp : all_data.all_user) {
					if (user.id != temp.id && name_ == temp.name) { printf("该用户名已被他人注册！\n"); success = false; }
				}
				if (success)user.name = name_;
			}
			else printf("输入有误！\n");
		}
		else printf("输入错误！\n");
	}
}
void user_interface(Data& all_data) {
	string name1;
	printf("请输入用户名：");
	cin >> name1;
	bool result1 = user_signin(all_data.all_user,name1);
	if (!result1)return;
	int size = all_data.all_user.size();
	int i = 0;
	for (; i < size; i++) {
		if (all_data.all_user[i].name == name1)break;
	}
	if (i == size) { cerr << "搜寻出错！\n"; exit(-1); }
	User& user = all_data.all_user[i];
	while (true) {
		printf("===============================================\n");
		printf("1.我是买家 2.我是卖家 3.个人信息管理 4.注销登录\n");
		printf("===============================================\n");
		printf("请输入你的操作：");
		string buffer; cin >> buffer;
		if (buffer == "4")break;
		else if (buffer == "3") user_information(user, all_data);
		else if (buffer == "2") sellor_interface(all_data, user);
		else if (buffer == "1")buyer_interface(all_data, user);
		else printf("输入有误！\n\n");
	}
}
void buyer_interface(Data& all_data,User& buyer) { 
	while (true) {
		printf("========================================================================================\n");
		printf("1.查看商品列表 2.购买商品 3.搜索商品 4.查看历史订单 5.查看商品详细信息 6.返回用户主界面\n");
		printf("========================================================================================\n\n");
		printf("请输入操作："); string input; cin >> input;
		if (input == "6")break;
		else if (input == "1") {
			string result = "SELECT * FROM commodity\n";
			all_data.all_command.push_back(result);
			Command c(result, false, true, false, buyer.id);
			c.operate(all_data);
		}
		else if (input == "2") {
			printf("请输入商品ID：");
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
				printf("未能匹配到该商品ID对应的商品。\n\n");
				continue;
			}
			Goods& want = all_data.all_goods[index2];
			printf("请输入数量：");
			double num; cin >> num;
			if (num != (int)num || num <= 0) { printf("输入非法\n\n"); }
			else {
				
				char buffer12[300] = "2";
				time_t t;
				struct tm* lt;
				time(&t);//获取Unix时间戳。
				lt = localtime(&t);//转为时间结构。
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
				if ((int)num > want.num_remain) { printf("商品数量不足！\n\n"); continue; }
				if (num * want.price > buyer.deposit) { printf("余额不足！无法购买！\n"); continue; }
				char buffer[300];
				int remaining = want.num_remain - (int)num;
				sprintf(buffer, "UPDATE commodity SET 数量 = %d WHERE 商品ID = %s\n", remaining, id_good.c_str());
				string result = buffer;
				all_data.all_command.push_back(result);
				Command c(result, false, true, false, buyer.id);
				Command d(result2, false, true, false, buyer.id);
				c.operate(all_data);
				d.operate(all_data);
				printf("***************************\n");
				printf("交易提醒！\n");
				printf("交易时间："); cout << result1 << endl;
				printf("交易单价%.1f\n", want.price);
				printf("交易数量：%d\n", (int)num);
				printf("交易状态：成功\n");
				printf("您的余额："); cout << buyer.deposit << endl;
				printf("***************************\n\n\n");
				if (remaining == 0) {
					string result4 = "UPDATE commodity SET 商品状态 = 已下架 WHERE 商品ID = ";
					result4 = result4 + want.id + "\n";
					Command e(result4, true, false, false, "admin_");
					e.operate(all_data);
				}
			}
		}
		else if (input == "3") {
			printf("请输入商品名称："); string input; cin >> input;
			string result = "SELECT * FROM commodity WHERE 名称 CONTAINS ";
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
			printf("请输入您想要查看的商品ID："); string result = "SELECT * FROM commodity WHERE 商品ID CONTAINS ";
			string input; cin >> input;
			result = result + input + "\n";
			all_data.all_command.push_back(result);
			Command c(result, false, true, false, buyer.id); 
			c.operate(all_data);
		}
		else printf("输入有误，请重新输入。\n");
	}
}
void sellor_interface(Data& all_data,User& sellor) { 
	while (true) {
		printf("====================================================================================\n");
		printf("1.发布商品 2.查看发布商品 3.修改商品信息 4.下架商品 5.查看历史订单 6.返回用户主界面\n");
		printf("====================================================================================\n\n");
		printf("请输入操作："); string input; cin >> input;
		if (input == "6")break;
		else if (input == "1") {
			string good_name, good_description;
			printf("请输入商品名称："); cin >> good_name;
			double price = 0, num;
			printf("请输入商品价格（大于零的小数或者整数）："); cin >> price;
			if (price <= 0) { printf("输入非法！\n"); break; }
			printf("请输入商品数量（大于零的整数）："); cin >> num;
			if (num <= 0 || num != (int)num) { printf("输入非法！\n"); break; }
			printf("请输入商品描述："); cin >> good_description;
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
			printf("请输入要下架的商品ID："); string input; cin >> input;
			string result = "UPDATE commodity SET 商品状态 = 已下架 WHERE 商品ID = ";
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
			printf("请输入被修改的商品ID："); cin >> id_input;
			printf("请输入被修改的商品属性（1.价格 2.描述）："); cin >> attribute_input;
			if (attribute_input != "1" && attribute_input != "2") { printf("输入有误！\n"); continue; }
			if (attribute_input == "1") {
				printf("请输入被修改的商品价格："); cin >> price;
				if (price <= 0) { printf("价格输入非法！\n"); continue; }
			}
			if (attribute_input == "2") {
				printf("请输入被修改的商品描述："); cin >> attribute;
			}
			char buffer[250] = "";
			if (attribute_input == "1")sprintf(buffer, "UPDATE commodity SET 价格 = %.1f WHERE 商品ID = %s\n", price, id_input.c_str());
			if (attribute_input == "2")sprintf(buffer, "UPDATE commodity SET 描述 = %s WHERE 商品ID = %s\n",attribute.c_str(),id_input.c_str());
			string result = buffer;
			all_data.all_command.push_back(result);
			Command c(result, false, false, true, sellor.id); 
			c.operate(all_data);
		}
		else printf("输入有误，请重新输入。\n");
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