#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void test1()
{
    int a = 1;
    double b = 2;
    string str = "abc";
    stringstream ss;

    ss << a <<" "<< b << " "<< str;

    cout<< ss.str();

   int a1; 
   double b1;
   string str1;
   string str2;
   ss >> a1 >> b1 >> str1;
   cout<< "a1 ->" << a1<<endl
       << "b1 ->" << b1 <<endl
       << "str1 ->"<< str1 <<endl;
}

int main()
{
    test1();

    return 0;
}

