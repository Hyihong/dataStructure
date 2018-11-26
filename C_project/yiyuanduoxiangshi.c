#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 

typedef struct node* PtrToNode;
typedef struct node {
	int coef;
	int expon;
	PtrToNode next;
} Node;
typedef PtrToNode List;

typedef struct findResult* PtrToResult;

typedef struct findResult {
	int flag; //flag == 1 ,表示找到
	PtrToNode p;//p表示指针，当flag为1时，表示需要修改的结点； flag 为0时，表示新增结点应该改结点后插入
} FindResult;

List getLink();//获取多项式的链表表示法 
void printLink(List L);// 打印链表
PtrToNode createLinkNode(int coef, int expon, PtrToNode next);//创建节点
PtrToResult findNodeByExpon(List L, int e);
List Polynomial_add(List L1, List L2);
List Polynomial_multip(List L1, List L2);
List DeleteInvalid(List L);

int main() {

	List L1 = getLink();
	List L2 = getLink();

	List multipResult_L = Polynomial_multip(L1, L2);
	List addResult_L = Polynomial_add(L1, L2);

	printLink(multipResult_L);
	printf("\n");
	printLink(addResult_L);


	return 0;
}


List getLink() {
	int len;
	List L;
	PtrToNode temp;
	scanf("%d", &len);
	L = malloc(sizeof(Node));
	temp = L;

	int i = 0;
	while (i < len) {
		PtrToNode p = malloc(sizeof(Node));
		scanf("%d", &(p->coef));
		scanf("%d", &(p->expon));
		temp->next = p;
		temp = temp->next;
		i++;
	}
	temp->next = NULL;

	return L;
}

void printLink(List L) {
	PtrToNode p = L;
	if (!p->next) {
		printf("0 0");
		return;
	};
	while (p->next) {
		printf("%d ", p->next->coef);
		printf("%d ", p->next->expon);
		p = p->next;
	};
	printf("%c", 8);

}

//创建Node节点的指针，并赋值
PtrToNode createLinkNode( int coef, int expon, PtrToNode next) {
	PtrToNode  p = malloc(sizeof(Node));
	p->coef = coef;
	p->expon = expon;
	p->next = next;
	return p;
}

//查找指数相同的节点，若找到，返回需要修改的节点地址。如找不到，则返回一个指针，指数为e的项 应该在该节点之后插入
// return 1: 找到
//            2:没找到，表中插入
//            3:没找到，表末插入
PtrToResult findNodeByExpon( List L, int e ) {
	PtrToNode p = L;
	PtrToResult  r = malloc( sizeof( FindResult )) ;
	while (p->next) {

		if ( e < p->next->expon  ) { //e小于当前指数域,继续向后找
			p = p->next;

		}
		else if ( e > p->next->expon ) {//e大于当前指数域, 表示e将在当前p指向的节点后面插入
			  (*r).flag = 2 ;
			  (*r).p = p;
		      return r;
		}
		else { //相等，即找到节点
			(*r).flag = 1;
			(*r).p = p->next;
			 return r;
		}
	}
	(*r).flag = 3;
	(*r).p = p;
	return r;
}

//删除链表中系数为0的项
List DeleteInvalid( List L ) {
	PtrToNode p = L;
	PtrToNode temp ;
	while (p->next) {
		if (!p->next->coef) {
			temp = p->next;
			p->next = p->next->next;
			free(temp);
		}
		else {
			p = p->next;
		}
	}
	return L;
}

//多项式相加
List Polynomial_add(List L1, List L2) {
	PtrToNode p1 = L1;
	PtrToNode p2 = L2;
	List L = malloc(sizeof(Node));
	L->next = NULL;
	PtrToNode p = L;

	while (p1->next && p2->next) {
		if (p1->next->expon > p2->next->expon) { //p1所指数据域大的情况 

			PtrToNode  node = createLinkNode(p1->next->coef, p1->next->expon, NULL);
			p->next = node;
			p = p->next;
			p1 = p1->next;
		}
		else if (p1->next->expon < p2->next->expon) {
			PtrToNode  node = createLinkNode(p2->next->coef, p2->next->expon, NULL);
			p->next = node;
			p = p->next;
			p2 = p2->next;
		}
		else {//两指数相等的情况
			if (p1->next->coef + p2->next->coef) {
				PtrToNode  node = createLinkNode(p1->next->coef + p2->next->coef, p1->next->expon, NULL);
				p->next = node;
				p = p->next;
			}
			p1 = p1->next;
			p2 = p2->next;

		}
	}

	if (p1->next ) {
		p->next = p1->next;
	}else {
		p->next = p2->next;
	}
	return L;
}


//多项式相乘
List Polynomial_multip(List L1, List L2) {
	PtrToNode p1 = L1;
	PtrToNode p2 = L2;
	List L = malloc(sizeof(Node));
	L->next = NULL;
	PtrToNode p = L;
	//思路：结果链表按照降序顺序排列
	//每一项相乘，与链表中的节点对比（链表为空则直接插入），若指数相同，则合并。
	// 指数不同，则在链表中找到指数小于前一个节点，同时指数大于后一个节点的位置，在前者后面插入
	//要注意指数相同两个项目相加为0时，需要将该节点删掉（全部加完再删更佳）

	while (p1->next) {
		p2 = L2;
	  	while (p2->next) {
			if (L->next) { //非空链表
				int _c = p1->next->coef * p2->next->coef;
				int _e = p1->next->expon + p2->next->expon;
				//在链表中查找指数域为_e的项，若存在，合并系数，若不存在，返回0；

				PtrToResult  r  =  findNodeByExpon(L, _e);

				switch (r->flag) {
					   //链表中含有指数相同的项目，则将系数相加
						case 1:
								r->p->coef = r->p->coef + _c;
								break;
						//没找到，表中插入 
						case 2: {
							PtrToNode temp = createLinkNode(  _c, _e, NULL );
							temp->next = r->p->next;
							r->p->next = temp;
							break;
						}
						// 没找到，表末插入
						case 3: {

							PtrToNode temp = createLinkNode( _c,	_e, NULL);
							r->p->next = temp;
							break;
            			}
				}
			}
			else { //空链表
				 L ->next = createLinkNode( 
					    p1->next->coef * p2->next->coef, 
					    p1->next->expon + p2->next->expon,
					   NULL
				 );
			}
			p2 = p2->next;
		}
		p1 = p1->next;
	}

	//得到了节点中的系数域可能为0的链表，对系数为0的项进行删除

	return DeleteInvalid(L);
	
}