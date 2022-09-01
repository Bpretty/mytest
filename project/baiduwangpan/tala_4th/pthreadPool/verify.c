#include "head.h"

int verifyPassword(MYSQL *conn,const char *username,const char *ciphertext)
{
    char *q1 = "select *from user where username ='";
    char *q2 = "' and ciphertext='";
    char query[255] = {0};
    sprintf(query,"%s%s%s%s%s",q1,username,q2,ciphertext,"';");
    MYSQL_RES *res = selectSql(conn,query);
    MYSQL_ROW row;
    row = mysql_fetch_row(res);
    if(NULL == row)
    {
        printf("no such user\n");
        return -1;
    }
   /* for(unsigned int i = 0;i < mysql_num_fields(res);i++)
    {
         printf("%8s ",row[i]);
    }
    printf("\n");*/
    mysql_free_result(res);
    return 0;
}
int verifyToken(MYSQL *conn,const char *username,const char *userToken)
{
    char *q1 = "select *from token where username ='";
    char *q2 = "' and user_token='";
    char query[255] = {0};
    sprintf(query,"%s%s%s%s%s",q1,username,q2,userToken,"';");
    MYSQL_RES *res = selectSql(conn,query);
    MYSQL_ROW row;
    row = mysql_fetch_row(res);
    if(NULL == row)
    {
        printf("invalid token\n");
        return -1;
    }
    /*for(unsigned int i = 0;i < mysql_num_fields(res);i++)
    {
         printf("%8s ",row[i]);
    }
    printf("\n");*/
    mysql_free_result(res);
    return 0;
}
int verifyPath(MYSQL *conn,const char *username,const char *ciphertext)
{
    char *q1 = "select *from user where username ='";
    char *q2 = "' and ciphertext='";
    char query[255] = {0};
    sprintf(query,"%s%s%s%s%s",q1,username,q2,ciphertext,"';");
    MYSQL_RES *res = selectSql(conn,query);
    MYSQL_ROW row;
    row = mysql_fetch_row(res);
    if(NULL == row)
    {
        printf("no such user\n");
        return -1;
    }
    for(unsigned int i = 0;i < mysql_num_fields(res);i++)
    {
         printf("%8s ",row[i]);
    }
    printf("\n");
    mysql_free_result(res);
    return 0;
}
char *getSalt(MYSQL *conn,const char *username)
{
    char *q1 = "select salt from user where username ='";
    char query[255] = {0};
    char *salt;
    sprintf(query,"%s%s%s",q1,username,"';");
    MYSQL_RES *res = selectSql(conn,query);
    MYSQL_ROW row;
    row = mysql_fetch_row(res);
    if(NULL == row)
    {
        printf("no such user\n");
        return NULL;
    }
    salt = (char *)calloc(strlen(row[0])+1,sizeof(char));
    for(unsigned long i = 0;i < strlen(row[0]);i++)
    {
        salt[i] = row[0][i];
    }
    mysql_free_result(res);
    return salt;

}
/*int main()
{
    char username[30] = {0};
    char password[30] = {0};
    char *salt;
    char *ciphertext;
    MYSQL *conn = mysqlConnInit();
    int ret;
    while(1)
    {
        scanf("%s",username);
        salt = getSalt(conn,username);
        if(!salt)
        {
            printf("enter again~bro\n");
            continue;
        }
        printf("salt = %s\n",salt);
        scanf("%s",password);
        ciphertext = crypt(password,salt);
        ret = verify(conn,username,ciphertext);
        free(salt);
        salt = NULL;
    }
    return 0;
}*/

