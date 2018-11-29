#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>

typedef struct node {
	int data;
	struct node * next;
} Node;

typedef Node* Ptr;

Ptr createStack() {
	Ptr s = malloc(sizeof(Node));
	s->next = NULL;
	s->data = 0 ;
	return s;
}

Ptr Stack_pushElement( Ptr s, int data) {
	Ptr node = malloc(sizeof(Node));
	node->data = data;
	node->next = s->next;
	s->next = node;
	s->data++;
	return s;
}

int Stack_popElement(Ptr s) {
	if (s->data ) {
		Ptr node;
		int d = s->next->data;
		node = s->next;
		s->next = s->next->next;
		s->data--;
		free(node);
		return d;
	}
	else {
		return NULL;
	}
}

Ptr Stack_empty(Ptr s) {
	s->data = 0;
	s->next = NULL;
	return s;
}


//判断是否为合法序列
int judge(int M, int N , int* a ) {
	Ptr s = createStack();     //空栈
	int max = 0;
	for (int i = 0; i < N; i++) {
		if (a[i] > max) {
			//栈的剩余空间足够放入 将押进栈内数字的个数
			if (M - s->data >= a[i] - max) {
				while (max+1 < a[i] ) {
					max++;
					Stack_pushElement(s, max);
				}
				if (a[i] - max == 1) {
					max++;
				}
			}else {
				return 0;
			}
		}
		//当前数字比栈内最大数字小
		if (a[i]  < max) {
			//比较当前序列值与栈顶元素大小
			if (s->next->data == a[i]) {
				Stack_popElement(s);
			}
			else {
				return 0;
			}
		}
	}
	return 1;
}

int main()
{
	int M, N, K;
	scanf("%d %d %d", &M, &N, &K);

	int**arr = malloc( sizeof( int*)*K );
	for (int i = 0; i < K;  i++) {
		arr[i] = malloc(sizeof(int) * N);
	}
	for (int i = 0; i < K; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &arr[i][j] );
		}
	}

	for (int i = 0; i < K; i++) {
		if ( judge(M, N, arr[i] ) ) {
			printf("YES\n");
		}
		else {
			printf("NO\n");
		}
	}
	return 0;
}
