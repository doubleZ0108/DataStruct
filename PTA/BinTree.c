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
