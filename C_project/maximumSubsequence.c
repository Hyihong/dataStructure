#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <Windows.h>i
#include<stdlib.h>

void _main() {

	int k;
	scanf_s("%d", &k);
	int *arr = (int *)malloc(sizeof(int) * k );
	for (int i = 0; i < k; i++) {
		scanf_s("%d", &arr[i]);
	}

	int max = 0, increase = 0;
	int sub_i = 0,  sub_j = 0;
	int record_i = 0 ,  record_j = 0; //记录增量大于0的位置
	int flag = 1; //该参数为标志位，1=> 增量为正   ;   0=> 增量为负

	for (int i = 0; i < k; i++) {
		increase += arr[i];
		if (increase > 0) {
		    	if (flag == 0) {
					record_i = i;
				}
				else {
					record_j = i;
				}
				flag = 1;

				if (increase > max) {  //增量为正且为当前最大
					max = increase;
					sub_i = record_i;
					sub_j = record_j;
			}
		}else{ //增量小于0，则置0
			increase = 0;
			flag = 0;
		}
		
	}

	if (max == 0) {
		printf("%d %d %d", max, 0, k);
	}
	else {
		printf("%d %d %d", max, sub_i, sub_j);
	}

	system("pause");
}

