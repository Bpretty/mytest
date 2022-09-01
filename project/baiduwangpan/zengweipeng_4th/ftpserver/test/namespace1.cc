#include <iostream>
using std::cout;
using std::endl;
namespace A
{
int a;
void displayA();
}
namespace B
{
void displayB();
}
namespace B
{
//
void displayB()
{
A::a=10;
    cout<<"helloA"<<endl;
    A::displayA();
}
}//endof namespaceB
namespace A
{
void displayA(){
    cout<<"helloB"<<endl;
    B::displayB();
};
}//endof namespaceA
int main()
{
    A::displayA();
    return 0;
}

