#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

BinTree CreatBinTree(); /* 实现细节忽略 */
int GetHeight( BinTree BT );    /*求二叉树的高度*/
void PreorderPrintLeaves( BinTree BT )  /*先序输出叶结点*/
void InorderTraversal( BinTree BT );
void PreorderTraversal( BinTree BT );
void PostorderTraversal( BinTree BT );
void LevelorderTraversal( BinTree BT );

int main()
{
    BinTree BT = CreatBinTree();
    printf("%d\n", GetHeight(BT));
    return 0;
}
/* 你的代码将被嵌在这里 */
int GetHeight( BinTree BT )
{
  if(!BT){return 0;}
  else
  {
    int leftheight=GetHeight(BT->Left);
    int rightheight=GetHeight(BT->Right);
    
    return 1 + (leftheight>rightheight? leftheight:rightheight);
  }
}

void PreorderPrintLeaves( BinTree BT )
{
  if(BT)
  {
    if(!BT->Right && !BT->Left) {printf (" %c",BT->Data);}
    PreorderPrintLeaves(BT->Left);
    PreorderPrintLeaves(BT->Right);
  }
}

void InorderTraversal( BinTree BT )
{
  if(BT)
  {
    InorderTraversal(BT->Left);
    printf (" %c",BT->Data);
    InorderTraversal(BT->Right);
  }
}
void PreorderTraversal( BinTree BT )
{
  if(BT)
  {
    printf (" %c",BT->Data);
    PreorderTraversal(BT->Left);
    PreorderTraversal(BT->Right);
  }
}
void PostorderTraversal( BinTree BT )
{
  if(BT)
  {
    PostorderTraversal(BT->Left);
    PostorderTraversal(BT->Right);
    printf (" %c",BT->Data);
  }
}
void LevelorderTraversal( BinTree BT )
{
  if(!BT){return;}
  
#define MAXSIZE 1000
  BinTree queue[MAXSIZE]={BT};  //将根压入队列中
  int front=0, rear=MAXSIZE-1;
  
  BinTree move;
  while(rear!= front)    //队列不空
  {
    /*出队列*/
    rear=(rear+1)%MAXSIZE;
    move=queue[rear];
    
    /*访问*/
    printf (" %c",move->Data);
    
    /*左右孩子入队*/
    if(move->Left){front=(front+1)%MAXSIZE; queue[front]=move->Left;}
    if(move->Right){front=(front+1)%MAXSIZE; queue[front]=move->Right;}
  }
  
}
