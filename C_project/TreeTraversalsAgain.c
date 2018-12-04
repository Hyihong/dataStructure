#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Null -1

//树的遍历
//通过堆栈的方式通过中序遍历的方式生成一颗唯一的二叉树
//后续遍历该树

typedef struct record* PtrToRecord;
struct record {
	int operater; //1表示Push,0表示Pop 
	int data;
};
typedef struct Node* PtrToNode;

typedef struct Node {
	int data;
	PtrToNode left; //左结点下标
	PtrToNode right;//右结点下标
}Node1;

//left,right表示记录范围
//N表示总个数
PtrToNode generateTree( int start,int end, PtrToRecord record  ) {

	if (record[start].operater == 1) {
		   PtrToNode T = malloc(sizeof(Node1));
		   T->data = record[start].data ;
		   int left = -1 , right = -1, count=0; 

		   //查找左结点序号
		   if (record[start + 1].operater == 1) {
			   left = start + 1;
		   }
		   //查找右结点序号
		   while ( start <= end) {
			   if (record[start].operater) {
				   count++;
			   }
			   else {
				   count--;
			   }
			   if (count == 0 && start < end &&  record[start+1].operater !=0  ) {
				   right = start + 1;
				   break;
			   }
			   start++;
		   }
		   //递归生成二叉树
		   if (left != -1 && right != -1 ) {
			   T->left = generateTree(left, right - 1, record );
			   T->right = generateTree(right, end, record );
		   }
		   if (left != -1 && right == -1) {
			   T->left = generateTree(left, end, record );;
			   T->right = NULL;
		   }
		   if (left == -1 && right != -1) {
			   T->left = NULL;
			   T->right = generateTree(right, end, record);
		   }
		   if (left == -1 && right == -1) {
			   T->left = NULL;
			   T->right = NULL;
		   }
		   return T;
	  }
}

void postorder(PtrToNode T) {
	if (T->left) {
		postorder(T->left);
	 }
	if (T->right) {
		postorder(T->right);
	}
	printf("%d ",T->data);
}

int main()
{
	int N;
	scanf( "%d", &N );
	PtrToRecord record = malloc(sizeof(struct record)*N*2);

	char str[6] = "\0";
	//先得到中序序列（inorder ) 
	for ( int i = 0; i < 2*N; i++ ) {
		 scanf("%s", str);
		 if ( strcmp(str, "Push")) {//Pop
			 (record + i)->operater = 0;
		 }
		 else {
			 (record + i)->operater = 1;
			 scanf("%d", &((record + i)->data));
		 }
	}

	//模拟数据
	//int N = 6;
	//struct record record[12]= {{1,1},{1,2},{ 1,3 },{ 0,0 },{ 0,0 },{ 1,4 },{ 0,0 },{ 0,0 },{ 1,5 },{ 1,6 },{ 0,0 },{ 0,0 }};

    //采用二分法，每次找到左孩子和右孩子，左孩子和右孩子再作为一颗独立树的根
	PtrToNode T  = generateTree(0, 2*N-1, record  );
	//采用后续遍历打印出元素序列
	postorder(T);

	return 0;

}


