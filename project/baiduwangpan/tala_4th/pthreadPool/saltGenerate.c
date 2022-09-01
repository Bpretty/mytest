#include "head.h"
char * saltGenerate()
{
    int i,flag;
    char *salt = (char *)calloc(SALTLEN,sizeof(char));
    srand(time(NULL));
    for(i = 0;i < SALTLEN;i++)
    {
        flag = rand()%3;
        switch(flag)
        {
            case 0:salt[i] = rand()%26 + 'a';break;
            case 1:salt[i] = rand()%26 + 'A';break;
            case 2:salt[i] = rand()%10 + '0';break;
        }
    }
    return salt;
}
