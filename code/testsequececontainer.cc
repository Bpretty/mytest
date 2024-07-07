#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
using namespace std;

template <class  T>
void display(const T& c)
{
    typename T::const_iterator it = c.begin();
    while(it != c.end())
    {
        cout<< *it<<endl;
        ++it;
    }
}


void t()
{
#if 0
    //初始化1
    vector<int> vec(10);
    vector<int>::iterator it = vec.begin();
    display(vec);

    //初始化2
    vector<int> vec1(10, 1);//一开始放了10个1
    display(vec1);

    //初始化3，通过迭代器范文初始化
    int arr[] = {1,2,3,4,5};
    vector<int> vec3(arr, arr+5);
    display(vec3);

#endif
    //初始化4，通过大括号的方式初始化
    vector<int> vec4{10,20,30};
    display(vec4);
    cout<< "--------"<<endl;

    //没有提供 push_front 和 pop_front 方法
    
    auto it1 = vec4.insert(vec4.begin(), 22);
    cout<< "*it1 = " << *it1 <<endl;
    display(vec4);
    cout<< "--------"<<endl;

    auto it2 = vec4.erase(vec4.begin());
    cout<< "*it2 = " << *it2 <<endl;
    display(vec4);
}

void t1()
{
    deque<int> numb(10);
    deque<int>::iterator it = numb.begin();

    display(numb);
}

void t2()
{
    list<int> numb(10);
    list<int>::iterator it = numb.begin();

    display(numb);
}

class Test
{
public:
    int _a;

    typedef int* _p;
};

void t3()
{
#if 0
    cout<< Test::_a <<endl;//erro，非静态成员
#endif
    Test::_p pointer;
}

void t4()
{
    //测试 erase-remove惯用法
    vector<int> numbs{1,2,3,4,5};
    auto it = numbs.erase(remove(numbs.begin(), numbs.end(), 1));
    
    //cout<< *it <<endl;
    display(numbs);
}

// 测试size和capacity的区别
void t5()
{
    vector<int> vec;
    vec.reserve(10);
    cout<< vec.size()<<endl
        << vec.capacity() <<endl<<endl;

    vec.push_back(1);
    vec.push_back(1);
    cout<< vec.size()<<endl
        << vec.capacity() <<endl<<endl;
}

//测试vector删除
void t6()
{
    vector<int> vec{5,3,2,2,1};

#if 0
    vec.erase(remove(vec.begin(), vec.end(), 2), vec.end());
#endif

#if 1
    vec.erase(vec.begin());
#endif
    
    display(vec);

    cout<< "size = " << vec.size() <<endl
        << "capacity = " << vec.capacity() <<endl;
}

struct Demo
{
    Demo(int a, int b = 0)
    :_id(a)
    ,_value(b)
    { 
        cout<< "Demo()" <<endl;
    }

    friend ostream& operator<<(ostream& os, const Demo& demo);
    friend bool operator==(const Demo& lhs, const Demo& rhs);
private:
    int _id;
    int _value;
};

ostream& operator<<(ostream& os, const Demo& demo)
{
    cout<< "( id = " 
        << demo._id
        << ","
        << demo._value
        << ")";

    return os;
}

bool operator==(const Demo& lhs, const Demo& rhs)
{
    return lhs._id == rhs._id && lhs._value == rhs._value;
}


// 测试删除自定义元素
void t7()
{
    vector<Demo> vec{1,2,3, 2,5};
    //display(vec);

#if 1
    vec.erase(remove(vec.begin(), vec.end(),2), vec.end());
    display(vec);
#endif
    
}

int main()
{
    //t();
    //t1();
    //t2();
    
    //t4();
    //t5();
    //t6();
    t7();

    return 0;
}

