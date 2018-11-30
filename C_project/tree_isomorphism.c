#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#define Null -1

typedef struct TreeNode {
	char c;
	int left;
	int right;
	int check; //标志着该节点是否有父节点，在求树根时需要用到
}TreeNode;
typedef TreeNode* PtrToTree;

//保存一棵树
PtrToTree createTree( int n ) {
	if (n == 0) {
		PtrToTree T = NULL;
		return T;
	}
	PtrToTree T = malloc( sizeof(TreeNode) * n );
	char ch, l , r ;
	for (int i = 0; i < n; i++) {
		while (  (ch = getchar() ) == '\n' ) {
			break;
		}	
		scanf("%c %c %c", &((T + i)->c), &l, &r );
		(T + i)->check = 0;
		if (l == '-') {   (T + i)->left = -1; } else { (T + i)->left = l -'0'; }
		if (r == '-') {   (T + i)->right = -1; } else { (T + i)->right = r -'0'; }
	}
	return T;
}

int findTreeRoot(PtrToTree T, int n) {
	if ( T ) {
		for (int i = 0; i < n; i++) {
			if ((T + i)->left != Null) {
				T[(T + i)->left].check = 1;
			}
			if ((T + i)->right != Null) {
				T[(T + i)->right].check = 1;
			}
		}
		for (int i = 0; i < n; i++) {
			if (T[i].check == 0) {
				return i;
			}
		}
	}
	else {
		return -1;
	}
	
}

void printTreeArr(PtrToTree T,int n ) {
	for (int i = 0; i <n; i++) {
		printf("%c ", (T + i)->c);
		printf("%2d ", (T + i)->left);
		printf("%2d ", (T + i)->right);
		printf("%2d \n", (T + i)->check);
	}
}

int isomorphism( int root1, int root2, PtrToTree T1, PtrToTree T2 ) {
	if (root1 == Null && root2 == Null) {
		return 1;
    }
	if ((root1 == Null && root2 != Null) || (root1 != Null && root2 == Null)) {
		return 0;
	}
	if (T1[root1].c != T2[root2].c) {
		return 0;
	}
	//以上两条保证了root一定不为Null,且两元素相等
	//以下判断该根拥有孩子的情况

	//T1没有孩子时，只有T2也没有孩子，两者才同构
	if (T1[root1].left == Null && T1[root1].right == Null) {
		if (T2[root2].left == Null && T2[root2].right == Null) {
			return 1;
		}
		else {
			return 0;
		}
	}

	//T1只有一个孩子时，T2也只有一个孩子才可能同构（对子树继续递归）
	//只有左孩子
	if (T1[root1].left != Null  && T1[root1].right == Null) {
		if (T2[root2].left != Null && T2[root2].right == Null) {
		    	return isomorphism(T1[root1].left, T2[root2].left, T1, T2);
		}
		if (T2[root2].left == Null && T2[root2].right != Null) {
			return isomorphism(T1[root1].left, T2[root2].right, T1, T2);
		}
		return 0;
	}

	//只有右孩子
	if (T1[root1].left == Null  && T1[root1].right != Null) {
		if (T2[root2].left != Null && T2[root2].right == Null) {
			return isomorphism(T1[root1].right, T2[root2].left, T1, T2);
		}
		if (T2[root2].left == Null && T2[root2].right != Null) {
			return isomorphism(T1[root1].right, T2[root2].right, T1, T2);
		}
		return 0;
	}

	//有两个孩子的情况，要判断是否需要互换
	if (T1[root1].left != Null  && T1[root1].right != Null ) {
		if (T2[root2].left != Null && T2[root2].right != Null) {
			if (  T1[T1[root1].left].c == T2[T2[root2].left].c  && T1[T1[root1].right].c == T2[T2[root2].right].c) {
			 	  int r =  ( isomorphism( T1[root1].left, T2[root2].left, T1, T2) && isomorphism(T1[root1].right, T2[root2].right, T1, T2) );
				  return r;
			}
			if (T1[T1[root1].left].c == T2[T2[root2].right].c  && T1[T1[root1].right].c == T2[T2[root2].left].c) {
				int r =  ( isomorphism(T1[root1].left, T2[root2].right, T1, T2) && isomorphism(T1[root1].right, T2[root2].left, T1, T2) );
				return r;
			}
			return 0;
		 }
		return 0;
	}
    
}

int main_isomorphism()
{
	 /*******树的同构******/
	//输入并保存树
	int N,M;
	scanf("%d", &N);
	PtrToTree T1 = createTree(N);
	scanf("%d", &M);
	PtrToTree T2 = createTree(M);
	//printTreeArr(T1, N);
	//printTreeArr(T2, M);
	

	//模拟
	//int N = 8, M = 8;
	//TreeNode tree1[8] = {  { 'A', 1, 2,0 },{ 'B', 3, 4 ,0},{ 'C', 5, -1 ,0},{ 'D', -1, -1,0 },{ 'E', 6, -1,0 },{ 'G', 7, -1,0 },{ 'F', -1, -1,0 },{ 'H', -1, -1 ,0} };
	//TreeNode tree2[8] = {  { 'G', -1, 4 ,0},{ 'B', 7, 6 ,0},{ 'F', -1, -1,0 },{ 'A', 5, 1 ,0},{ 'H', -1, -1,0 },{ 'C', 0, -1,0 },{ 'D', -1, -1,0 },{ 'E', 2, -1, 0 } } ;
	//TreeNode tree1[8] = { { 'B', 5, 7,0 },{ 'F', -1, -1 ,0 },{ 'A', 0, 3 ,0 },{ 'C', 6, -1,0 },{ 'H', -1, -1,0 },{ 'D', -1, -1,0 },{ 'G', 4, -1,0 },{ 'E', 1, -1 ,0 } };
	//TreeNode tree2[8] = { { 'D', 6, -1 ,0 },{ 'B', 5, -1 ,0 },{ 'E', -1, -1,0 },{ 'H', -1, -1 ,0 },{ 'C', 0, 2,0 },{ 'G', -1, 3,0 },{ 'F', -1, -1,0 },{ 'A', 1, 4, 0 } };
	//int tree1_root = findTreeRoot(tree1, N);
	//int tree2_root = findTreeRoot(tree2, M);

	if (M != N) {
		printf("No");
		return 0;
	}
	else {
		//判断两树是否同构
		int tree1_root = findTreeRoot(T1, N);
		int tree2_root = findTreeRoot(T2, M);
		int result = isomorphism(tree1_root, tree2_root, T1,T2 );
		if (result) {
		printf("Yes");
		}
		else {
		printf("No");
		}
	}
	

	return 0;

}