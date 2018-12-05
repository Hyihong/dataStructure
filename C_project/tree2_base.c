#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode {
	ElementType Data;
	BinTree Left;
	BinTree Right;
};

/* 先序遍历，由裁判实现，细节不表 */
void PreorderTraversal(BinTree BT) {
	if (BT) {
		printf("%d ", BT->Data);
		if (BT->Left) {
			PreorderTraversal(BT->Left);
		}
		if (BT->Right) {
			PreorderTraversal(BT->Right);
		}
	}
}; 
void InorderTraversal(BinTree BT) {/* 中序遍历，由裁判实现，细节不表 */
	if (BT) {
		if (BT->Left) {
			InorderTraversal(BT->Left);
		}
		printf("%d ", BT->Data);
		if (BT->Right) {
			InorderTraversal(BT->Right);
		}
	}
}  

BinTree Insert(BinTree BST, ElementType X);
BinTree Delete(BinTree BST, ElementType X);
Position Find(BinTree BST, ElementType X);
Position FindMin(BinTree BST);
Position FindMax(BinTree BST);



int main__tree2_bst()
{
	BinTree BST, MinP, MaxP, Tmp;
	ElementType X;
	int N, i;

	BST = NULL;
	scanf("%d", &N);
	for (i = 0; i<N; i++) {
		scanf("%d", &X);
		BST = Insert(BST, X);
	}
	printf("Preorder:"); PreorderTraversal(BST); printf("\n");
	MinP = FindMin(BST);
	MaxP = FindMax(BST);

	scanf("%d", &N);
	for (i = 0; i<N; i++) {
		scanf("%d", &X);
		Tmp = Find(BST, X);
		if (Tmp == NULL) printf("%d is not found\n", X);
		else {
			printf("%d is found\n", Tmp->Data);
			if (Tmp == MinP) printf("%d is the smallest key\n", Tmp->Data);
			if (Tmp == MaxP) printf("%d is the largest key\n", Tmp->Data);
		}
	}

    scanf("%d", &N);
	for (i = 0; i<N; i++) {
		scanf("%d", &X);
		BST = Delete(BST, X);
		printf("Inorder:"); InorderTraversal(BST); printf("\n");
	}
	/*printf("Inorder:"); InorderTraversal(BST); printf("\n");*/

	return 0;
}
/* 你的代码将被嵌在这里 */
//函数Insert将X插入二叉搜索树BST并返回结果树的根结点指针；
BinTree Insert(BinTree BST, ElementType X) {

	if ( !BST) {
		BST = malloc(sizeof(struct TNode));
		BST->Data = X;
		BST->Left = BST->Right = NULL;
	}
	else {
		if (X < BST->Data) {
			BST->Left = Insert(BST->Left, X);
		}
		else if (X > BST->Data) {
			BST->Right = Insert(BST->Right, X);
		}
	}
	return BST;
}

//函数FindMin返回二叉搜索树BST中最小元结点的指针；
int i = 0;
Position FindMin(BinTree BST) {
	if (BST) {
		if (!BST->Left) {
			return BST;
		}
		else {
			return  FindMin(BST->Left);
		}
	}
	else {
		return NULL;
	}
	
}


//函数FindMax返回二叉搜索树BST中最大元结点的指针。
Position FindMax(BinTree BST) {
	if (BST) {
		if (!BST->Right) {
			return BST;
		}
		else {
			FindMax(BST->Right);

		}
	}
	else {
		return NULL;
	}

}

//函数Find在二叉搜索树BST中找到X，返回该结点的指针；如果找不到则返回空指针；
Position Find(BinTree BST, ElementType X) {
	Position p = NULL;
	if (BST) {
		if (X < BST->Data) {
			return Find(BST->Left, X);
		}
		if (X > BST->Data) {
			return Find(BST->Right, X);
		}
		if (X == BST->Data) {
			p = BST;
		}
	}
	return p;
}


//函数Delete将X从二叉搜索树BST中删除，并返回结果树的根结点指针；如果X不在树中，则打印一行Not Found并返回原树的根结点指针；
/*
      找到结点后，有三种情况需要考虑
	  1、该结点是叶子结点
	  2、该节点只有一个孩子
	  3、该节点有两个孩子
*/
BinTree Delete(BinTree BST, ElementType X) {
	Position tmp = BST;
	if (BST) {
		if ( X < BST->Data) {
			BST->Left = Delete(BST->Left, X);
		  }
		if (X > BST->Data) {
			BST->Right = Delete(BST->Right, X);
		}
		if (X == BST->Data) {
			if (BST->Left && BST->Right) { //有左右两孩子
				tmp = FindMin(BST->Right);
				BST->Data = tmp->Data;
			    BST->Right = Delete(BST->Right, tmp->Data);
			}
			else {
				tmp = BST;
				if ( !BST->Left ) {  //没有左孩子（没有孩子或只有右孩子）
					BST = BST->Right;
				}
				else { //只有左孩子
					  BST = BST->Left; 
				}
				free( tmp );
			}
		}

	}
	else {
		printf("要删除的元素未找到");
	}
	
	return BST;
}