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
	time(&t);//获取Unix时间戳。
	lt = localtime(&t);//转为时间结构。
	char result[15];
	sprintf(result, "%d-%d-%d", lt->tm_year + 1900, lt->tm_mon, lt->tm_mday);
	string real = result;
	return real;
}
void Command::operate(Data& all_data) {
	if (origin[0] == 'S' && origin[origin.size() - 1] == 'y') {
		if (manager) {
			printf("************************************************************************\n");
			printf("商品ID  名称      价格      上架时间      卖家ID     数量	商品状态\n");
			for (const Goods& k : all_data.all_goods) {
				cout << k.id << " " << k.name << " ";
				printf("%d   ", (int)k.price);
				cout << k.time << "   " << k.sellor_id << "    " << k.num_remain << "     ";
				cout << (k.state == 1 ? "销售中" : "已下架") << endl;
			}
			printf("************************************************************************\n");
		}
		else if (buyer) {
			printf("************************************************************************\n");
			printf("商品ID  名称      价格      上架时间      卖家ID     数量	商品状态\n");
			for (const Goods& k : all_data.all_goods) {
				if (k.state == 1) {
					cout << k.id << " " << k.name << " " << k.price << "   " << k.time << "   " << k.sellor_id << "    " << k.num_remain << "     ";
					cout << (k.state == 1 ? "销售中" : "已下架") << endl;
				}
			}
			printf("************************************************************************\n");
		}
		else if (sellor) {
			printf("************************************************************************\n");
			printf("商品ID  名称      价格      上架时间      卖家ID     数量	商品状态\n");
			for (const Goods& k : all_data.all_goods) {
				if (k.sellor_id == User_id) {
					cout << k.id << " " << k.name << " " << k.price << "   " << k.time << "   " << k.sellor_id << "    " << k.num_remain << "     ";
					cout << (k.state == 1 ? "销售中" : "已下架") << endl;
				}
			}
			printf("************************************************************************\n");
		}
	}//输出所有商品
	else if (split_string[0] == "SELECT" && split_string[split_string.size() - 1] == "order") {
		printf("***********************************************************\n");
		printf("订单ID  商品ID  交易单价 数量   交易时间   卖家ID   买家ID\n");
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
	else if (split_string[0] == "UPDATE" && split_string[1] == "commodity" && split_string[3] == "数量") {
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
		printf("订单ID  商品ID  交易单价  数量   交易时间  卖家ID  买家ID\n");
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
		printf("用户ID  用户名    联系方式         地址            钱包余额     用户状态\n");
		for (const User& temp : all_data.all_user) {
			cout << temp.id << "    " << temp.name << "    " << temp.phone_num << "      " << temp.address << "    ";
			printf("%.1f      ", temp.deposit);
			cout << (temp.remain ? "正常" : "封禁") << endl;
		}
		printf("**************************************************************************\n");
	}
	else if (split_string[0] == "INSERT" && split_string[2] == "commodity") {
		string kkk = split_string[4].substr(1);
		kkk.pop_back();
		vector<string> new_split = split(kkk, ',');
		printf("请确认发表的商品信息无误！\n");
		printf("************************************\n");
		printf("商品名称："); cout << new_split[0] << endl;
		printf("商品价格：%.1f\n", atof(new_split[1].c_str()));
		printf("商品数量：%d\n", atoi(new_split[2].c_str()));
		cout << "商品描述：" << new_split[3] << endl;
		printf("************************************\n");
		while (true) {
			printf("您确定要发布该商品吗？(y/n)");
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
				printf("发布商品成功！\n\n");
				break;
			}
			else if (input3 == "n") { printf("取消成功！\n\n"); break; }
			else printf("输入有误，请重新输入！\n");
		}
	}
	else if (split_string[0] == "UPDATE" && split_string[1] == "commodity" && split_string[3] == "商品状态"&&split_string[7]=="商品ID") {
	bool not_find = true; int size = split_string.size();
		for (Goods& k : all_data.all_goods) {
			if (k.id == split_string[size - 1]) {
				not_find = false;
				if (sellor && User_id != k.sellor_id) {
					printf("您未发布过该商品ID对应的商品！\n");
					break;
				}
				else if (k.state != 1) {
					printf("该商品已经下架。\n");
					break;
				}
				else {
					if (User_id != "admin_") {
						printf("确定要下架该商品吗？\n");
						printf("************************************************************************\n");
						printf("商品ID  名称      价格      上架时间      卖家ID     数量	商品状态\n");
						cout << k.id << " " << k.name << " ";
						printf("%d   ", (int)k.price);
						cout << k.time << "   " << k.sellor_id << "    " << k.num_remain << "     ";
						cout << (k.state == 1 ? "销售中" : "已下架") << endl;
						printf("************************************************************************\n");
						printf("请选择y/n：");
						string input_1; cin >> input_1;
						while (true) {
							if (input_1 == "y") { k.state = 2; printf("下架成功！\n"); break; }
							else if (input_1 == "n") { printf("取消成功！\n"); break; }
							else printf("输入错误，请重新输入！\n");
						}
						break;
					}
					else if(User_id=="admin_") {
						k.state = 2;
					}
				}
			}
		}
		if (not_find&&manager)printf("未查询到该商品ID对应的商品！\n");
		if (not_find && sellor)printf("您未发布过该商品ID对应的商品！\n");
	}
	else if (split_string[0] == "SELECT" && split_string[3] == "commodity" && split_string[4] == "WHERE" && split_string[5] == "名称") {
		printf("************************************************************************\n");
		printf("商品ID  名称      价格      上架时间      卖家ID     数量	商品状态\n");
		for (const Goods& k : all_data.all_goods) {
			string::size_type idx;
			idx = k.name.find(split_string[7]);
			if (idx != k.name.npos) {
				if (manager || (buyer && k.state == 1)) {
					cout << k.id << " " << k.name << " " << k.price << "   " << k.time << "   " << k.sellor_id << "    " << k.num_remain << "     ";
					cout << (k.state == 1 ? "销售中" : "已下架") << endl;
				}
			}
		}
		printf("************************************************************************\n");
	}
	else if (split_string[0] == "SELECT" && split_string[3] == "commodity" && split_string[4] == "WHERE" && split_string[5] == "商品ID") {
		bool not_find = true;
		for (const Goods& k : all_data.all_goods) {
			if (k.id == split_string[7]) {
				not_find = false;
				if (k.state != 1) { printf("未找到该商品或者您没有查看该商品信息的权限！\n"); break; }
				printf("************************************\n");
				printf("商品ID：%s\n", k.id.c_str());
				printf("商品价格：%.1f\n", k.price);
				printf("上架时间：%s\n", k.time.c_str());
				printf("商品描述：%s\n", k.description.c_str());
				printf("商品卖家：%s\n", k.sellor_id.c_str());
				printf("************************************\n");
				break;
			}
		}
		if(not_find)printf("未找到该商品或者您没有查看该商品信息的权限！\n");
	}
	else if (split_string[0] == "UPDATE" && split_string[1] == "commodity" && split_string[2] == "SET" && (split_string[3]=="价格"||split_string[3]=="描述")) {
		bool not_find = true;
		for (Goods& k : all_data.all_goods) {
			if (k.id == split_string[9]) {
				not_find = false;
				if (k.sellor_id != User_id) { printf("未找到该商品或者你没有修改该商品的权限！\n"); break; }
				if (split_string[3] == "价格") { k.price = atof(split_string[5].c_str()); printf("修改成功！\n"); break; }
				if (split_string[3] == "描述") { k.description = split_string[5]; printf("修改成功！\n"); break; }
				else { printf("系统出错！！！！！！请返回主界面退出并联系开发者。\n"); break; }
			}
		}
		if(not_find)printf("未找到该商品或者你没有修改该商品的权限！\n");
	}
	else if (split_string[0] == "UPDATE" && split_string[1] == "commodity" && split_string[2] == "SET" && split_string[3] == "商品状态" && split_string[7] == "卖家ID") {
		for (Goods& k : all_data.all_goods) {
			if (k.sellor_id == split_string[9])k.state = 2;
		}
	}
	else if (split_string[0] == "UPDATE" && split_string[1] == "user" && split_string[2] == "SET" && split_string[3] == "用户状态" && split_string[7] == "用户ID") {
		for (User& k : all_data.all_user) {
			if (k.id == split_string[9]) { 
				k.remain = false;
			}
		}
	}
}