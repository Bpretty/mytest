#include <func.h>

int main()
{
    FILE* f = popen("./print", "r");

    if (NULL == f){
        printf("创建标准流管道错误\n");
        return -1;
    }

    char buf[128]= {0};
    fgets( buf, sizeof(buf), f);

    printf("buf = %s\n", buf);

    fclose(f);
}
