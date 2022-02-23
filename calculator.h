#pragma once
#include <string>
#include <stack>

template<class T>
class calculator {
	calculator() {};

	static T Mystoi(std::string& str, size_t& index) {
		//这个现在只适合于整数
		//因为系统的stoi需要从str的开头开始转化
		bool isNeg = false;
		if (str[index] == '-') {
			isNeg = true;
			++index;
		}
		T res = 0;
		while (index < str.size() && isdigit(str[index])) {
			res = res * 10 + str[index++] - '0';
		}
		if (isNeg)
			return -res;
		return res;
	}
public:
	static T Compute(std::string &str, size_t &index) {
		//要求输入是有效的，int范围的，且计算过程中也不能超出int范围
		//可以有负数
		if (index >= str.size()) {
			throw "输入下标超出范围";
		}
		std::stack<T> nums;
		std::stack<char> ops;
		int state = 0; //为了应对负号。0表示请求数字，1表示请求操作符
		while (index < str.size()) {
			if (str[index] == ')') {
				++index;
				break;
			}
			if (state == 1) {
				ops.push(str[index++]);
				state = 0;
			}
			else {
				if (str[index] == '(') {
					++index;
					nums.push(Compute(str, index));
				}
				else {
					nums.push(Mystoi(str, index));
				}
				if (!ops.empty()) {
					if (ops.top() == '*' || ops.top() == '/') {
						T b = nums.top(); nums.pop();
						//T a = nums.top(); nums.pop();
						if (ops.top() == '*') {
							nums.top() *= b;
						}
						else {
							nums.top() /= b;
						}
						ops.pop();
					}
				}
				state = 1;
			}
		}
		while (!ops.empty()) {
			char op = ops.top(); ops.pop();
			int b = nums.top(); nums.pop();
			//int a = nums.top(); nums.pop();
			switch (op) {
			case '+':
				nums.top() += b; break;
			case '-':
				nums.top() -= b; break;
			case '*':
				nums.top() *= b; break;
			case '/':
				nums.top() /= b; break;
			}
		}

		return nums.top();


	}
};