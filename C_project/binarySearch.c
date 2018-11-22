#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0

typedef int ElementType;

typedef int Position;

struct LNode {
	ElementType Data[MAXSIZE];
	Position Last; /* 保存线性表中最后一个元素的位置 */
};

typedef struct LNode *List;

//函数声明
List ReadInput();
Position BinarySearch(List L, ElementType X);

int main_bina()
{
	List L;
	ElementType X;
	Position P;

	L = ReadInput();
	scanf_s("%d", &X);
	P = BinarySearch(L, X);
	printf("%d\n", P);

	return 0;
}


//函数定义1

List ReadInput() {
	int k;
	scanf_s("%d", &k);
	List L;
	L = malloc(sizeof(struct LNode));
	for (int i = 1; i <= k; i++) {
		scanf_s("%d", &(L->Data[i]));
	}
	L->Last = k;
	return  L;
}

/* 你的代码将被嵌在这里 */
Position BinarySearch(List p, ElementType X) {
	int left = 1;
	int right = p->Last;
	int mid, mid_value;

	while (right - left >= 0) {
		mid = left + (right - left) / 2;
		mid_value = p->Data[mid];
		if (X == mid_value) {
			return mid;
		}
		else if (X > mid_value) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	return NotFound;
}





