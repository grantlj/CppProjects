/*
Author      :     Grant Liu
Organization:     CQUPT
Student   ID:     2013210294
E-Mail      :     393444163@qq.com

The C Programming Language Exercise 3-1:
Rewrite the Binary Search in a MORE EFFICIENT WAY.
*/
#include <stdio.h>
#define COUNTS 10
int nums[COUNTS];

//Qsort.
void QSort(int a,int b)
{
    int i=a,j=b,x=nums[i],t;
    while (i!=j)
    {
        while ((nums[j]>=x) && (j>i))
            j--;
        if (j>i)
        {
            t=nums[i];
            nums[i]=nums[j];
            nums[j]=t;
        }

       while ((nums[i]<=x) && (j>i))
            i++;
        if (j>i)
        {
            t=nums[i];
            nums[i]=nums[j];
            nums[j]=t;
        }

    }
    nums[i]=x;
    i++;j--;
    if (a<j) QSort(a,j);
    if (i<b) QSort(i,b);

}

//Generate Value by random.
void GenerateValueByRnd()
{
  int i;
  srand(time(NULL));
  for (i=0;i<COUNTS;i++)
        nums[i]=(int) rand()%100+10;
}

//Print out the value.
void PrintValue()
{
    int i;
    for (i=0;i<COUNTS;i++)
        printf("%d ",nums[i]);
    printf("\n");
}

int BinarySearch(int head,int tail,int val)
{
   printf("%d\t%d\t%d\n",head,tail,(head+tail)/2);
   if (head>tail) return -1;
   else
   {
     if (val<nums[p])
        return BinarySearch(head,p-1,val);
     if (val>nums[p])
        return BinarySearch(p+1,tail,val);
     if (val==nums[p])
          return p;

   }
}

int main()
{

    GenerateValueByRnd();
    QSort(0,COUNTS-1);
    PrintValue();
    printf("Enter the value you want to search:");
    int val;
    scanf("%d",&val);
    printf("Find %d at postion:%d\n",val,BinarySearch(0,COUNTS-1,val));
    return 0;
}
