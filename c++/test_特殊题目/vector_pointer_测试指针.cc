#include "common.h"

// 是否崩溃看vector的扩容策略
int main()
{
	vector<int> vec = {1,2,3,4};

	int* p = &vec[2];
	vec.push_back(5);

	cout << *p << endl;

	return 0;
}
