#include <stdio.h>
#include <string.h>
#include <malloc.h>

void main() {

	int k;
	scanf_s("%d", &k);
	int *arr = (int *)malloc(sizeof(int));
	for (int i = 0; i < k; i++) {
		scanf_s("%d", &arr[i]);
	}

	int max = 0, increase = 0;
	for (int i = 0; i < k; i++) {
		increase += arr[i];
		if (increase > max) {
			max = increase;
		}
		else if (increase < 0) {
			increase = 0;
		}
	}

	printf("%d", max);
}