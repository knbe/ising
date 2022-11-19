#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define L 10
#define N (L*L)

int s[L][L];

double rdn() {
	return((rand() % 10000) / 10000.0);
}

void initialise() {
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < L; j++) {
			if (rdn() < 0.5) {
				s[i][j] = 1; 
			}
			else {
				s[i][j] = -1; 
			}

		}
	}
}

int main() {
	printf("jolly\n"); 
	initialise; 
	printf("%d\n", s[1][1]); 
//	for (int i = 0; i < L; i++)
//		for (int j = 0; j < L; j++)
//			printf("%d\n", s[i][j]); 
}
