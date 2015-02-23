#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define LEN sizeof(struct PTNode)
struct PTNode
{
    int val;
    struct PTNode *next;
};

struct PTNode* CreateLinkTable(void)
{
    struct PTNode *p1,*p2,*head;
    p1=(struct PTNode*)malloc(LEN);

    int t,counts=0;
    do
    {
        scanf("%d",&t);
        if (t!=-1)
        {
            counts++;
            if (counts!=1) {
              p2=(struct PTNode*)malloc(LEN);
              p2->val=t;
              p2->next=NULL;
              p1->next=p2;
              p1=p2;
            }
            else
            {
                p1->val=t;
                p1->next=NULL;
                head=p1;
            }
        }
    }
    while (t!=-1);
    return head;
}

void PrintLinkTable(struct PTNode* p)
{
   while (p->next!=NULL)
   {
       printf("%d--->",p->val);
       p=p->next;

   }
   printf("%d\n",p->val);
}

int main()
{
    struct PTNode *head=NULL;
    head=CreateLinkTable();
    PrintLinkTable(head);
    return 0;
}
