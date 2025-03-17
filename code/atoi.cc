#include "common.h"

int atoi(const char* str)
{
	assert(str != nullptr);

	while (isspace(*str))  str++;
	int nSign = 1;
	if (*str == '-') 
	{
		nSign = -1;
		str++;
	}

	int ret = 0;
	while (isdigit(*str))
	{
		//cout << "*str = " << *str << endl;
		ret = ret * 10 + (*str - '0');

		str++;
	}

	if (*str)	cout << "不是完整的数值" << endl;

	ret *= nSign;

	return ret;
}

int main()
{
	cout << atoi("-123") << endl;
	cout << atoi("	\n123") << endl;

	cout << INT_MAX << ", " << INT_MIN << endl;
	cout << LONG_MAX << ", " << LONG_MIN << endl;

	return 0;
}
