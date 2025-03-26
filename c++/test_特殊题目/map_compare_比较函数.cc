#include "common.h"

struct Compare
{
	bool operator()(const int& a, const int& b) const
	{
		// 注意！这里是错误示范！比较要求严格弱序列，不满足会导致结果未定义，可能导致栈溢出
		return a >= b;
	}
};

int main()
{
	map<int, int, Compare> m;
	m[1] = 10;
	m[1] = 20;

	cout << m.size() << endl; //输出结果为2

	return 0;
}

