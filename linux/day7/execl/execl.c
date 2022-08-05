#include <func.h>

int main()
{
   printf("this is execl func test\n"); 

   execl("./hello", "参数0", "参数1", NULL);

   printf("you can't seee me\n");
}
