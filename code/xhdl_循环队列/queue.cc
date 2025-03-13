#include "common.h"

template <typename T>
class Queue
{
public:
	Queue(int length = 5)
	:_head(0)
	 ,_tail(0)
	 ,_length(length)
	{
		// 这里必须使用 resize 而不能使用 reserve
		_buff.resize(_length);
	}

	~Queue(){}

	bool isEmpty()
	{
		if (_head == _tail) return true;

		return false;
	}

	bool isFull()
	{
		if ((_tail + 1) % _length == _head) return true;

		return false;
	}

	int push(const T& value)
	{
		if (isFull())	return -1; 

		_buff[_tail] = value;
		_tail = (_tail + 1) % _length;

		cout << "入栈后 _tail = " << _tail << endl;

		return 0;
	}

	int pop()
	{
		if (isEmpty())	return -1;

		_head = (_head + 1) % _length;
		cout << "退栈后 _head = " << _head << endl;

		return 0;
	}

private:
	vector<T> _buff;
	int _head;
	int _tail;
	int _length;
};

int main()
{
	Queue<int> que(3);
	if (0 != que.push(1)) 	cout << "r1失败" << endl;
	if (0 != que.push(2)) 	cout << "r2失败" << endl;
	if (0 != que.push(3)) 	cout << "r3失败" << endl;

	if (0 != que.pop()) 	cout << "c1失败" << endl;
	if (0 != que.pop()) 	cout << "c2失败" << endl;
	if (0 != que.pop()) 	cout << "c3败" << endl;

	return 0;
}
