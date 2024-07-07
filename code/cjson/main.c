#include "cJSON.h"
#include <stdio.h>

void test0()
{
    cJSON* pJson = cJSON_CreateObject();
    cJSON_AddStringToObject(pJson, "k1", "hello");
    cJSON_AddNumberToObject(pJson, "age", 11);

    char* pStr = cJSON_Print(pJson);
    char* pStr1 = cJSON_PrintUnformatted(pJson);
    
    printf("date：%s\n", pStr);
    printf("date：%s\n", pStr1);

    char* str = cJSON_GetStringValue(pJson);
    printf("get：%s\n", str);

    //最后释放cjson数据
    cJSON_Delete(pJson);
}

int main()
{
    test0();

    return 0;
}

