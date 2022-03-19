#include"calculate.h"
bool cal::is_num(char c) {
	if (c >= '0' || c <= '9')return true;
	else return false;
}
string cal::non_space(const string& k) {
	string result;
	for (char a : k) {
		if (a != ' ')result.push_back(a);
	}
	return result;
}
bool cal::legal_kuonum(const string& s) {
	int left = 0, right = 0;
	for (char c : s) {
		if (c == '(')left++;
		if (c == ')')right++;
		if (left < right)return false;
	}
	if (left != right)return false;
	else return true;
}
bool cal::legal_char(const string& s) {
	bool result = true;
	for (char c : s) {
		bool current = false;
		current = current || (c == '0') ? true : false;
		current = current || (c == '1') ? true : false;
		current = current || (c == '2') ? true : false;
		current = current || (c == '3') ? true : false;
		current = current || (c == '4') ? true : false;
		current = current || (c == '5') ? true : false;
		current = current || (c == '6') ? true : false;
		current = current || (c == '7') ? true : false;
		current = current || (c == '8') ? true : false;
		current = current || (c == '9') ? true : false;
		current = current || (c == '(') ? true : false;
		current = current || (c == ')') ? true : false;
		current = current || (c == '+') ? true : false;
		current = current || (c == '-') ? true : false;
		current = current || (c == '*') ? true : false;
		current = current || (c == '/') ? true : false;
		current = current || (c == '.') ? true : false;
		result = result && current;
	}
	return result;
}
bool cal::legal_allinput(const string& s) {
	return true;
}
string cal::calcu() {
	if (!legal_char(correct_)) {
		cout << "有非法字符输入！" << endl;
		return "wrong";
	}
	if (!legal_kuonum(correct_)) {
		cout << "左右括号未对齐！" << endl;
		return "wrong";
	}
	vector<string> h = hou(correct_);
	if (!h.empty()) {
		if (h[0] == "小数点使用非法！\n") {
			cout << "小数点使用非法！\n" << endl;
			return "wrong";
		}
		if (h[0] == "数字输入非法！\n") {
			cout << "数字输入非法!" << endl;
			return "wrong";
		}
	}
	int judge = legal_logic();
	if (judge == -1) {
		cout << "括号使用有误！\n" << endl;
		return "wrong";
	}
	if (judge == -2) {
		cout << "运算符或小数点使用有误\n" << endl;
		return "wrong";
	}
	if (judge == -3) {
		cout << "首位不能是小数点！\n" << endl;
		return "wrong";
	}
	string result = calcu_hou(h);
	cout << result;
	if (result == "除数不能为0\n")return "wrong";
	return result;
}
vector<string> cal::hou(string& s) {
	append_zero(s);
	stack<char> stack1;
	vector<string> result;
	int size = s.size();
	string temp;
	for (int i = 0; i < size; i++) {
		if (s[i] == '.') {
			if (i == size - 1) { vector<string> wrong = { "小数点使用非法！\n" }; return wrong; }
			if (temp.empty() || temp.find('.') != string::npos) { vector<string> wrong = { "小数点使用非法！\n" }; return wrong; }
			temp.push_back('.');
		}
		else if (s[i] >= '0' && s[i] <= '9') {
			if (temp == "0") { vector<string> wrong = { "数字输入非法！\n" }; return wrong; }
			temp.push_back(s[i]);
		}
		else if (s[i] == '(') {
			if (!temp.empty()) {
				result.push_back(temp);
				temp = string();
			}
			stack1.push('(');
		}
		else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
			if (!temp.empty()) {
				result.push_back(temp);
				temp = string();
			}
			if (s[i] == '*' || s[i] == '/') {
				stack1.push(s[i]);
			}
			else {
				while (!stack1.empty()) {
					if (stack1.top() != '(') {
						string temp11(1, stack1.top());
						result.push_back(temp11);
						stack1.pop();
					}
					else break;
				}
				stack1.push(s[i]);
			}
		}
		else if (s[i] == ')') {
			if (!temp.empty()) {
				result.push_back(temp);
				temp = string();
			}
			while (!stack1.empty()) {
				if (stack1.top() == '(') {
					stack1.pop();
					break;
				}
				else {
					string temp123(1, stack1.top());
					result.push_back(temp123);
					stack1.pop();
				}
			}
		}
	}
	if (!temp.empty())result.push_back(temp);
	while (!stack1.empty()) {
		string temp123(1, stack1.top());
		result.push_back(temp123);
		stack1.pop();
	}
	return result;
}
string cal::calcu_hou(const vector<string>& a) {
	stack<double> buffer;
	int size = a.size();
	for (int i = 0; i < size; i++) {
		if (a[i] != "+" && a[i] != "-" && a[i] != "*" && a[i] != "/") {
			buffer.push(atof(a[i].c_str()));
		}
		else {
			if (a[i] == "+") {
				if (buffer.size() <= 1) {
					return "语法错误！\n";
				}
				double a = 0, b = 0;
				b = buffer.top(); buffer.pop();
				a = buffer.top(); buffer.pop();
				a = a + b; buffer.push(a);
			}
			else if (a[i] == "-") {
				if (buffer.size() == 0) {
					return "语法错误！\n";
				}
				else if (buffer.size() == 1) {
					double a = buffer.top();
					buffer.top() = -a;
				}
				else {
					double a = 0, b = 0;
					b = buffer.top(); buffer.pop();
					a = buffer.top(); buffer.pop();
					a = a - b; buffer.push(a);
				}
			}
			else if (a[i] == "*") {
				if (buffer.size() <= 1) {
					return "运算故障\n";
				}
				else {
					double a = 0, b = 0;
					b = buffer.top(); buffer.pop();
					a = buffer.top(); buffer.pop();
					a = a * b; buffer.push(a);
				}
			}
			else if (a[i] == "/") {
				if (buffer.size() <= 1) {
					return "除法运算故障\n";
				}
				else if (fabs(buffer.top()) <= 0.00000001) {
					return "除数不能为0\n";
				}
				else {
					double a = 0, b = 0;
					b = buffer.top(); buffer.pop();
					a = buffer.top(); buffer.pop();
					a = a / b; buffer.push(a);
				}
			}
		}
	}
	if (buffer.size() != 1) {
		return "操作数数量和操作符数量不匹配！\n";
	}
	char result[100];
	double aaaaa = buffer.top();
	sprintf(result, "%.1f", aaaaa);
	string result1 = result;
	return result1;
}
void cal::append_zero(string& s) {
	int size = s.size();
	for (int i = 0; i < size; i++) {
		if (s[i] == '-') {
			if (i == 0) {
				s.insert(0, "0");
				i++;
			}
			else {
				if (s[i - 1] == '(') {
					s.insert(i, "0");
					i++;
				}
			}
		}
	}
}
int cal::legal_logic() {
	//-1 括号 -2操作符或者小数点错误 -3小数点错误
	int size = correct_.size();
	for (int i = 0; i < size; i++) {
		if (i == 0) {
			if (correct_[i] == ')')return -1;
			if (correct_[i] == '.')return -3;
			if (correct_[i] == '(') {
				if (size == 1|| correct_[i + 1] == ')')return -1;
				else if (correct_[i + 1] == '+' || correct_[i + 1] == '*' || correct_[i + 1] == '/'||correct_[i+1]=='.')return -2;
			}
			if (correct_[i] == '+' || correct_[i] == '*' || correct_[i] == '/')return -2;
			if (correct_[i] == '-') {
				if (size == 1 || correct_[i + 1] == '+' || correct_[i + 1] == '*' || correct_[i + 1] == '/' || correct_[i] == '-')return -2;
				if (correct_[i + 1] == ')')return -1;
			}
			if (correct_[i] >= '0' || correct_[i] <= '9') {
				if (size == 1)return 1;
				if (correct_[i + 1] == '(' || correct_[i + 1] == ')') {
					return -1;
				}
			}
		}
		else if (i < size - 1) {
			if (correct_[i] == '+' || correct_[i] == '-' || correct_[i] == '/' || correct_[i] == '*') {
				if (correct_[i + 1] == '+' || correct_[i + 1] == '-' || correct_[i + 1] == '/' || correct_[i + 1] == '*')return -2;
				if (correct_[i + 1] == ')')return -1;
			}
			if (correct_[i] == '(') {
				if (correct_[i + 1] == '+' || correct_[i + 1] == '*' || correct_[i + 1] == '/' || correct_[i + 1] == '.')return -2;
				if (correct_[i + 1] == ')')return -1;
			}
			if (correct_[i] <= '9' && correct_[i] >= '0') {
				if (correct_[i + 1] == '(') {
					return -1;
				}
			}
		}
		if (i == size - 1) {
			if (correct_[i] == '+' || correct_[i] == '*' || correct_[i] == '/' || correct_[i] == '.' || correct_[i] == '-')return -2;
			if (correct_[i] == '(')return -1;
		}
	}
	return 1;
}