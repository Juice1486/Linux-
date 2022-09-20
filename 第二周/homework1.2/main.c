#include<stdio.h>
#include"sub1.h"
#include"sub2.h"

int main()
{
   int a =1,b =2;
   int c = add(a,b);
   int d = minus(a,b);
   printf("%d\n",c);
   printf("%d\n",d);
   return 0;
}

