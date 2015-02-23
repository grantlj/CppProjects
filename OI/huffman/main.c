#include <stdio.h>
#include <stdlib.h>

struct Tnodes
{
    int val;
    int LChild;
    int RChild;
    int Par;
    int avail;
};

struct Tnodes tree[200];

int main()
{
  int n,i;
  for (i=0;i<200;i++)
  {
    tree[i].LChild=0;tree[i].RChild=0;tree[i].Par=0;
    tree[i].avail=1;
  }

  scanf("%d",&n);

  for (i=0;i<n;i++)
        scanf("%d",&tree[i].val);

  int round;
  for (round=n;round<n*2-1;round++)
  {

      int small1=100000;
      int small2=100000;

      int p1=-1;int p2=-1;

      for (i=0;i<n;i++)
      {
          if (tree[i].val<small1 && tree[i].avail==1)
          {
              small1=tree[i].val;
              p1=i;
          }
          else if (tree[i].val<small2 && tree[i].avail==1)
          {
              small2=tree[i].val;
              p2=i;
          }
      }
      if (p1!=-1 && p2!=-1)
      {
         tree[p1].Par=i;tree[p1].avail=0;
         tree[p2].Par=i;tree[p1].avail=0;
         tree[i].LChild=p1;
         tree[i].RChild=p2;
         tree[i].val=tree[p1].val+tree[p2].val;
      }

  }
      printf("NO.\tVal\tPar\tLChild\tRChild\n");
      for (i=n;i<2*n-1;i++)
        printf("%d\t%d\t%d\t%d\t%d\n",i,tree[i].val,tree[i].Par,tree[i].LChild,tree[i].RChild);


  return 0;
}
