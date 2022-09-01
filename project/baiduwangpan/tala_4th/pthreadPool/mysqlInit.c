#include"mysqlInit.h"

MYSQL * mysqlConnInit()
{
    MYSQL *conn;
    char *server ="localhost";
    char *user = "root";
    char *password = "123";
    char *database = "netdisk";
    ////初始化句柄
    conn = mysql_init(NULL);
    //连接
    if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
    {
        printf("Error connecting to database\n");
        return NULL;
    }else{
        printf("Connect success\n");
        return conn;
    }
}
MYSQL_RES * selectSql(MYSQL *conn,const char *query)
{
    int ret = mysql_query(conn,query);
    if(ret)
    {
        printf("Error making query\n");
        //printf("Error making query:%s\n",mysql_error(conn));
        return NULL;
    }else{
        MYSQL_RES *res = mysql_store_result(conn);
        if(res)
        {
            // printf("~~~~~~~~~~~~~~~ret = %d\n",ret);
            return res;
        }else{
            printf("Not find data");
            return NULL;
        }    
    }
}
int insertSql(MYSQL *conn,const char *query)
{
    int ret = mysql_query(conn,query);
    if(ret)
    {
        printf("Error making query:%s\n",mysql_error(conn));
    }else{
        printf("Query succcess\n");    
    }
    return ret;
}

