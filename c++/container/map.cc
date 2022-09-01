#include "container.h"

// 遍历测试
void t()
{
    vector<int> vec{5,4,3,2,1};

    set<int> s( vec.begin(), vec.end() );
    print(s);

    cout<<"-------------"<<endl;

    forprint(s);
}

void t1()
{
    int num[] = {5,4,3,2,1};

    map<int,int> s;    
    for(auto &e:num)
    {
        s.insert(make_pair(e,e));
    }
    
    //print(s);
    cout<<"-----------------------"<<endl;

    auto beg = s.begin();
    auto b1 = ++s.begin() ;
    cout<<"*beg = "<< (*beg).first << endl;
    cout<<"*b1 = "<< (*b1).first << endl;
    s.erase( beg );
    cout<<"删除后 "<<endl;
    cout<< "*beg = "<<(*beg).first << endl;
    cout<< "*b1 = "<< (*b1).first <<endl;

    //此时迭代器已经失效
    cout<< (*++beg).first<<endl;

    cout<< (*++b1).first <<endl;
}

int main()
{
    t1();
    

    return 0;
}

