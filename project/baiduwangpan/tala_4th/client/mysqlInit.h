#ifndef __MYSQLINIT_H__
#define __MYSQLINIT_H__
#include "head.h"
typedef struct{
    char *server;
    char *user;
    char *password;
    char *database;
    char query[200];
}sqlElem,*pSqlElem;

MYSQL * mysqlConnInit();
void insertSql(MYSQL *conn,const char *query);
MYSQL_RES * selectSql(MYSQL *conn,const char *query);
#endif
