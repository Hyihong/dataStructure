#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#define Null -1

typedef struct TreeNode {
	int left;
	int right;
	int check; //标志着该节点是否有父节点，在求树根时需要用到
}TreeNode;
typedef TreeNode* PtrToTree;

int findroot( PtrToTree T, int N ) {
	for (int i = 0; i < N; i++) {
		if ((T + i)->check == 0) {
			return i;
		}
	}
}

//层序遍历
void printfLeaf(PtrToTree T, int  root,int N) {
	int a[10];
	int i = 0, j=0;

	while (j < N) {
		if (T[root].left != -1) {
			a[i] = T[root].left;
			i++;
		}
		if(T[root].right != -1)  {
			a[i] = T[root].right;
			i++;
		};	
		if (T[root].left == -1 && T[root].left == -1) {
			printf("%d ", root);
		}
		root = a[j];
		j++;
	}

}

int main_tree_base()
{
	/*******建树并打印出所有的叶子(从上到下，从左到右)******/
	//int N;
	//int root;
	//scanf("%d", &N);
	//char ch;
	//char l, r;
	//PtrToTree T = malloc(sizeof(TreeNode) * N);
	//for (int i = 0; i < N; i++) {	(T + i)->check = 0; }
	//for (int i = 0; i < N; i++) {
	//	getchar();
	//	scanf("%c %c", &l, &r);
	//	if (l == '-') { 
	//		 (T + i )->left = -1; 
	//	}  else { 
	//		  (T + i)->left = l - '0' ;
	//		  (T + l - '0')->check = 1;
	//	} ; 
	//	if (r == '-') { 
	//		(T + i)->right = -1; 
	//	} else { 
	//		(T + i)->right = r - '0';
	//		(T + r - '0')->check = 1;
	//	};
	//}

	//模拟数据
	int N = 8;
	int root =1;
	TreeNode T[8] = {
		{1,-1, 1 },{-1,-1,1},{0,-1,1},{ 2,7,0},{-1,-1,1},{-1,-1,1},{ 5,-1,1},{4,6,1} 
	};
	root = findroot(T, N);
	printfLeaf(T, root, N);
	

	return 0;

}



//03 - 树2 List Leaves （25 分）
//Given a tree, you are supposed to list all the leaves in the order of top down, and left to right.
//
//Input Specification :
//Each input file contains one test case.For each case, the first line gives a positive integer N(≤10) which is the total number of nodes in the tree-- and hence the nodes are numbered from 0 to N−1.Then N lines follow, each corresponds to a node, and gives the indices of the left and right children of the node.If the child does not exist, a "-" will be put at the position.Any pair of children are separated by a space.
//
//Output Specification :
//For each test case, print in one line all the leaves' indices in the order of top down, and left to right. There must be exactly one space between any adjacent numbers, and no extra space at the end of the line.
//
//Sample Input :
//8
//1 -
//--
//0 -
//2 7
//- -
//--
//5 -
//4 6
//Sample Output :
//4 1 5