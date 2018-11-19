#include <stdio.h>
int roll_n_dice(int dice, int sides);

static unsigned long int next = 1;

int roll_count = 0; //����ͳ��

unsigned int rand1(void) {
	next = 1103515245 *next   + 12345;
	return (unsigned int)(next / 65535) % 32768;
}

void srand1(unsigned int seed) {
	next = seed;
}

static int rollem(int sides) {
	int roll;
	roll = rand() % sides + 1;
	++roll_count; // ���㺯�����ô���
	return roll;
}

int roll_n_dice(int dice, int sides) { //ɸ������ÿ��ɸ�ӵ�����
	int d;
	int total = 0;
	if (sides < 2) {
		puts("����������������");
		return  -2;
	}

	for (d = 0; d < dice; d++) {
		total += rollem(sides);
	}

	return total;

}