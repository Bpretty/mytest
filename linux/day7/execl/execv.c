#include <func.h>

int main()
{
   printf("this is execv func test\n"); 

   char* arg[3] = {"参数0", "参数1", NULL};
   execv("./hello", arg);

   printf("you can't seee me\n");
}
