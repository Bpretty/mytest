#include <func.h>

int main()
{
    FILE* f = popen("./add", "w");

    if (NULL == f){
        printf("创建标准流管道错误\n");
        return -1;
    }

    char buf[128]= {"3 4\n"};
    fputs( buf, f);

    fclose(f);
}
