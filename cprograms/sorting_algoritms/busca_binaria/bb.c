#include <stdio.h>
#include <math.h>

int bb (int v[20], int x) {
	
	int mid = 10, fim = 20, ini = 1;
	
	while(ini <= fim) {
		if(v[mid] == x) {
			return mid;
		} else if (v[mid] > x) {
			fim = (mid-1);
		} else {
			ini = (mid+1);
		}
		mid = floor((ini+fim)/2);	
	}
	return -1;
}

int main(int argc, char const *argv[])
{
	int v[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
	int x;

	scanf("%d", &x);

	if (bb(v, x) > 0) {
		printf("achou\n");
	} else {
		printf("nao achou\n");
	}
	return 0;
}