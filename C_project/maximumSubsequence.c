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
	int record_i = 0 ,  record_j = 0; //��¼��������0��λ��
	int flag = 1; //�ò���Ϊ��־λ��1=> ����Ϊ��   ;   0=> ����Ϊ��

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

				if (increase > max) {  //����Ϊ����Ϊ��ǰ���
					max = increase;
					sub_i = record_i;
					sub_j = record_j;
			}
		}else{ //����С��0������0
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

