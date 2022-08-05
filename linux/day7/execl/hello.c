#include <func.h>

int main(int argc, char* argv[])
{
    printf("hello, how are you\n");
    printf("参数数量为:%d\n", argc);

    for(int i = 0;i <argc; i++){
        printf("%s ", argv[i]);
    }
    printf("\n");
}
