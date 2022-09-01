#include "head.h"

void logInFunc()
{
    system("clear");
    printf("Please enter your ID: ");
    scanf("%s",tmpInf.username);
    printf("Please enter your password: ");
    scanf("%s",tmpInf.passwd);
    
}
void exitFunc()
{
    exit(0);
}
void registerFunc()
{

}
void menu()
{
    system("clear");
    printf("--------press the right button skip to the corresponding page\n");
    printf("1.log in\n");
    printf("2.register\n");
    printf("0.exit\n");
    char c;

    scanf("%c",&c);
    switch(c)
    {
        case'0':exitFunc();break;
        case'1':logInFunc();break;
        case'2':registerFunc();break;
        default:menu();
    }
}

