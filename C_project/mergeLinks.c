#include <stdio.h>
#include<Windows.h>
#include <stdbool.h>

#define MAXSIZE 10 

typedef struct Node* PtrToNode;
struct Node {
	int Data;
	PtrToNode Next;
};
typedef PtrToNode List;

List Merge(List L1, List L2);//按非递减顺序合并链表，返回指向头结点的头指针
List createLink();
printfLink(List L );

int main_mergeLinks() {
   //后缀表达式
	List L1 = createLink();
	List L2 = createLink();
	List L = Merge(L1, L2);
	printfLink(L);
	printfLink(L1);
	printfLink(L2);
	system("pause");

}

List createLink() {
	List L =  malloc( sizeof( struct Node)  );
	PtrToNode temp = L ;
	int n;
	scanf_s("%d", &n);
	while (n) {
	    	PtrToNode p = malloc(sizeof(struct Node));
		    p->Data = n;
			temp->Next = p;
			p->Next = NULL;
			temp = temp->Next;
			scanf_s("%d", &n);
	}
	return L;
	
}

printfLink(List L) {
	PtrToNode temp = L;
	if (!temp->Next) {
		printf("NULL\n");
		return;
	}
	do {
		printf("%d ", temp->Next->Data);
		temp = temp->Next;
	} while (temp->Next);
	printf("\n\n");
}


List Merge(List L1, List L2) {

	//声明链表指针
	List L;
	//声明头结点
	PtrToNode p = malloc(sizeof(struct Node) ) ;
	L = p;
	PtrToNode p1 = L1, p2 = L2;

	//判断是否为第一个节点，用于处理头结点指针
	while ( p1->Next && p2->Next ) {

		if (p1->Next->Data <= p2->Next->Data) {
			    printf("进来L1操作\n");
				p->Next = p1->Next;
				p = p->Next;
				p1->Next = p1->Next->Next;
		}
		else {
			   printf("进来L2操作\n");
			   p->Next = p2->Next;
			   p = p->Next;
			   p2->Next = p2->Next->Next;
		}
	}

	if (p1->Next ) { 	//L2的节点全部处理完毕
		p->Next = p1->Next;
		p1->Next = NULL;
	}else {  //L1的节点全部处理完毕
	    	p->Next = p2->Next;
			p2->Next = NULL;
	}
	return L;
   
	
}