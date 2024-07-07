#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
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

class Test
{
    friend bool operator<(const Test& t, const Test& other);
    friend bool operator>(const Test& t, const Test& other);
    friend ostream& operator<<(ostream& os, const Test& t);
    friend class Comp;
public:
    Test(int a = 0)
    :_a(a)
    {
    }

    ~Test()
    {
    }
private:
    int _a;
};

bool operator<(const Test& t, const Test& other)
{
    return t._a < other._a;
}

bool operator>(const Test& t, const Test& other)
{
    return t._a > other._a;
}

ostream& operator<<(ostream& os, const Test& t)
{
    os<< "_a = " << t._a << endl;

    return os;
}

//set测试
void t1()
{
    //默认按照升序排序,内部存放元素不同

    //初始化1，使用大括号
#if 0
    set<int> numbers{5,4,3,2,1};
    display(numbers);
#endif

    //初始化2，使用迭代器范围内元素
#if 1
    int arr[] = {5,4,3,2,1};
    //set<int> numbers(arr, arr+5);
    set<int, std::greater<int>> numbers(arr, arr+5);
    display(numbers);
#endif

    //查找
    //1.使用count
    int one = 10;
    printf("元素出现的次数为：%ld\n", numbers.count(one));
    //2.使用find
    set<int>::iterator it = numbers.find(one);
    if(it != numbers.end())
        cout<< "找到了" <<endl;
    else
        cout<< "没找到" <<endl;

    //添加元素
    std::pair<set<int>::iterator, bool> ret = numbers.insert(1);
    if(ret.second)
        cout<< "添加元素成功"<<endl;
    else
        cout<< "添加元素失败"<<endl;
}

struct Comp
{
    bool operator()(const Test& lhs, const Test& rhs)
    {
        return lhs._a < rhs._a;
    }
};

void t11()
{
#if 0
    set<Test, std::greater<Test>> numbers{5,4,3,2,1};
    display(numbers);
#endif

    set<Test, Comp> numbers2{5,4,3,2,1};
    display(numbers2);
}

//map测试
void t2()
{
    //默认按照升序排序，不能存放关键字相同的元素
    
    map<int, string> citis{
        pair<int, string>(1, "北京"),
        pair<int, string>(2, "上海"),
        pair<int, string>(3, "广州"),

        std::make_pair(6, "深圳"),
        std::make_pair(5, "珠海")
    };

    // 支持下标访问运算符，时间复杂度是 O(log N)
    cout<< citis[1]<<endl;

    //如果对应的关键字不存在，则会以该关键字创建一个元素
    
    //查找,使用find
    pair<map<int, string>::iterator, bool> ret = citis.insert(make_pair(5, "白云"));
    if (ret.second){
        cout<< "成功" <<endl;
    }else{
        cout<< "失败" <<endl;
    }

    //查找,使用count
    size_t cnt = citis.count(1);
    cout<< "map中查找到的元素数量是："<< cnt <<endl;
}

bool func(int a)
{
    return a<=2;
}

bool func1(const pair<int, int>& a)
{
    return a.first<=2;
}

//remove_if使用
void t3()
{
//测试vector
#if 0
    vector<int>  vec{1,2,3,2,2,5};
    vec.erase(remove_if(vec.begin(), vec.end(), func), vec.end());

    display(vec);
    cout<< "vector的size = " << vec.size()
        <<" ,capacity = " << vec.capacity();
#endif

//测试map中删除指定元素的操作
#if 1
    map<int, int> m{
        make_pair(1,10),
        make_pair(2,20),
        make_pair(3,30),
        make_pair(4,40),
        make_pair(5,50)
    };
    //m.erase(remove_if(m.begin(), m.end(), func1), m.end()); //erro

    for(auto c = m.begin(); c != m.end(); ) 
    {
        //cout<< "("<<i.first
        //    <<","<<i.second
        //    <<")"<<endl;
        
        if (c->first <= 2)
        {
            c = m.erase(c);
        }else{
            c++;
        }
    }

    for(auto &v:m)
    {
        cout<< "("<<v.first
            <<","<<v.second
            <<")"<<endl;
    }
#endif
}

struct Info
{
    int _a;
    int _b;
};

ostream& operator<<(ostream& os, Info info)
{
    cout<< "("
        << info._a
        <<","
        <<info._b
        <<")"
        <<endl;

    return os;
}

void t4()
{
    map<string, Info> info;

    info["s1"] = {1, 2};
    info["s2"] = {2, 2};
    info["s3"] = {3, 2};

    for(auto it = info.begin(); it != info.end(); it++)
    {
        cout<< it->first<<endl
            << it->second<<endl;
    }
}

int main()
{
    //t1();
    //t11();
    //t2();
    //t3();
    t4();

    return 0;
}

