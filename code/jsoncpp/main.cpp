#include "json/json.h"
#include "json/json-forwards.h"
#include <iostream>
#include <string>
using namespace std;

// 简单json-》string
void t1()
{
    Json::Value root;
    root["age"] = 100;
    root["name"] = "ly";
    root["type"] = 1;

    Json::FastWriter fasterWrite;
    string str = fasterWrite.write(root);
    cout<< str<<endl;

    cout<<"--------------------"<<endl;
    cout<<"--------------------"<<endl;

    Json::StyledWriter styleWrite;
    string str1 = styleWrite.write(root);
    cout<< str1<<endl;

    cout<<"--------------------"<<endl;
    cout<<"--------------------"<<endl;
    str = root.toStyledString();
    cout<<str<<endl;
}

// 复杂json-》string
Json::Value t2()
{
    Json::Value root;
    for(int i = 0; i < 3; i++)
    {
        string name = "ly" + to_string(i);
        Json::Value tmp;
        tmp["name"] = name;
        tmp["age"] = 10 + i;

        root.append(tmp);
    }
    
    Json::Value printRoot;
    printRoot["rootInfo"] = root;
    printRoot["from"] = "china";
    printRoot["belong"] = "we";

    Json::FastWriter fw;
    string str = fw.write(printRoot);
    cout<<str<<endl;

    //cout<< "数组的大小是："<<printRoot.size()<<endl;


    printRoot["array"].append("t1");
    printRoot["array"].append("t2");
    printRoot["array"].append("t3");
    printRoot["array"].append("t4");
    cout<< "数组array的大小是："<<printRoot["array"].size()<<endl;
    //str = fw.write(printRoot["array"]); //可用
    //cout<< str<<endl;

    return printRoot;
}

// 解析json对象
void t3(Json::Value& str)
{
    size_t len = str["array"].size();
    for(int i = 0; i < len; i++)
    {
        string tmp = str["array"][i].asString();
        cout<< i << "->" << tmp <<endl;
    }
}

void t4()
{
    char buff[] = "{\"name\":\"ly\",\"age\":18,\"array\":[1,2,3,4]}";
    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(buff, root))
    {
        cout << "parse fail!!!" << endl;
        return;
    }
    string strName = root["name"].asString();
    int age = root["age"].asInt();
    cout << "Get Result: " << strName << ", " << age <<endl;

    for(int i = 0; i < root["array"].size(); i++)
    {
        int tmp = root["array"][i].asInt();
        cout<< "Get tmp value: " << tmp << endl;
    }
}

void t5()
{
    char str[] = "{}";
    Json::Reader reader;
    Json::Value root;
    reader.parse(str, root);

    if (root["name"].isNull())
    {
        cout<< "无该key值" <<endl;

        //cout<< "使用 asInt 获取的值为：" << root["name"].asInt() << endl;
    }

    string strRst =  root.toStyledString();
    cout<< strRst << endl;
}

// 测试isNull方法
void t6()
{
    string str = "{\"pan\":100}";

    Json::Reader reader;
    Json::Value root;

    reader.parse(str, root);
    if (root["tilt"].isNull())
    {
        cout<<"空值"<<endl;

        // 空值转为string
        string rst = root["tilt"].asString();
        cout<<rst.length()<<endl;
        cout<<rst<<endl;

        //空值转为int
        int iValue = root["tilt"].asInt();
        cout<<iValue<<endl;
    }
    if (!root["pan"].isNull())
    {
        cout<<"非空值"<<endl;
        string rst = root["pan"].asString();
        cout<<"得到结果："<<rst<<endl;
    }
}

int main()
{
    //t1();
    //Json::Value str = t2();
    //t3(str);
    //t4();
    //t5();
    t6();

    return 0;
}

