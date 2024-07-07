#include <iostream>
#include <functional>
#include <memory>
#include <vector>
using namespace std;

class Demo
{
public:
    Demo()
    {
        cout<< "Demo()"<<endl;
    }

    void print()
    {
        cout<<"print()"<<endl;
    }

};

// 测试unique_ptr
void test0()
{
    Demo* demo1 = new Demo();
    Demo* demo = new Demo();

    unique_ptr<Demo> p1(demo1);
    unique_ptr<Demo> p(demo);
    //p->print();

    //unique_ptr<Demo> p1 = p;  // erro，不能复制,但是可以执行移动语义
    unique_ptr<Demo> p2 = move(p);  
    p2 = move(p1);
    //p1 = p;                   //erro，不能赋值
}

// 测试shared_ptr
void test1()
{
    Demo* demo = new Demo();

    shared_ptr<Demo> p(demo);
    shared_ptr<Demo> p1 = p;

    p->print();
}

void test2()
{
    vector<unique_ptr<Demo>> vec;
    unique_ptr<Demo> p(new Demo());

    vec.push_back(move(p));
    vec[0]->print();

    vec.emplace_back(new Demo());
    vec[1]->print();

}

int main()
{
    //test0();
    //test1();
    test2();

    return 0;
}

