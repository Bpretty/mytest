#include "common.h"

void test(int&& x) { cout << "Rvalue" << endl; }
void test(int& x) { cout << "Rvalue" << endl; }

int main()
{
	int a = 1;
	test(std::move(a));

	return 0;
}
