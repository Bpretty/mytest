#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//测试读取
void t0(const char* pName)
{
    FILE* p = fopen(pName, "r");
    if (NULL == p)
    {
        perror("fopen");
        goto Error;
    }
    
    char c = '\0';
    while( (c = fgetc(p)) != EOF) 
    {
        //printf("下一个读取的字符是：%s\n", p->_cnt);
        putchar(c);
    }

    fclose(p);
    return;

Error:
    printf("test fail\n");

    fclose(p);
}

//测试 wb+写入
void t1(const char* pName)
{

    //int i = 10;
    char ch[] = "hello\nworld";
    FILE* p = fopen(pName, "wb+");
    if (NULL == p)
    {
        perror("fopen");
        return;
    }

    //int ret = fwrite(ch, sizeof(char), strlen(ch), p); //这里写入的是11个字节
    int ret = fwrite(ch, sizeof(ch), 1, p); //这里写入的是12个字节
    printf("写入结果：%d\n", ret);

    fclose(p);
}

//测试 rb+读取
void t2(const char* pName)
{

    //int i = 0;
    char ch[100] = {0};
    FILE* p = fopen(pName, "rb+");
    if (NULL == p)
    {
        perror("fopen");
        return;
    }

    //int ret = fread(&i, sizeof(i), 1, p);
    //printf("读取结果：%d, 得到的值是：%d\n", ret, i);
    int ret = fread(ch, sizeof(ch), 1, p);
    printf("读取结果：%d, 得到的值是：%s\n", ret, ch);

    fclose(p);
}

//测试fseek
void t3()
{
    FILE* p = fopen("file.txt", "rb+");
    if (NULL == p)
    {
        perror("fopen");
        return;
    }

    int ret = fseek(p, 5, SEEK_SET);
    if (0 != ret)
    {
        perror("fseek");
    }

    char buf[100] = {0};
    //ret = fread(buf, sizeof(buf), 1, p );
    ret = fread(buf, sizeof(char), sizeof(buf), p );
    //if(ret <= 0)
    //{
    //    perror("fread");
    //    return;
    //}
    //printf("get: %s\n", buf);
    puts(buf);

    fclose(p);
}

int main(int argc, char* argv[])
{
#if 0
    //t0(argv[1]);
#endif

#if 0
    t1(argv[1]);
#endif

#if 0
    t2(argv[1]);
#endif

#if 1
    t3();
#endif
    return 0;
}

