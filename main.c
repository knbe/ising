#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include "pseudo.h"

#define L 40
#define N (L*L)
#define J 1
//#define T 2.50

void prspins(int (*S)[L][L]) {
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < L; j++) {
			printf("%d,%d=%d   ", i, j, (*S)[i][j]); 
		}
		printf("\n");
	}
}

void showspins(int (*S)[L][L]) {
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < L; j++) {
			char *c;
			if ((*S)[i][j] > 0) {
				//c = "■";
				c = "██";
			}
			else if ((*S)[i][j] < 0) {
				//c = "□";
				c = "░░";
			}
			printf("%s", c);
		}
		printf("\n");
	}
	printf("\n");
}

void initialise(int (*S)[L][L], double T) {
	printf("\033[2J\033[1;1H");
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < L; j++) {
			if (rdn() < 0.5) {
				(*S)[i][j] = 1; 
			}
			else {
				(*S)[i][j] = -1; 
			}

		}
	}

	printf("T=%f, J=%d, L=%d, N=%d\n", T, J, L, N);
	showspins(S);
	sleep(5);
	
}

int get_ssflip_dE(int i, int j, int (*S)[L][L]) {
	// periodic bcs
	int S_up, S_dn, S_lf, S_rt; 

	// nn up
	if (j == (L-1)) {
		S_up = (*S)[i][0]; 
	}
	else {
		S_up = (*S)[i][j+1];
	}

	// nn dn
	if (j == 0) {
		S_dn = (*S)[i][L-1];
	}
	else {
		S_dn = (*S)[i][j-1];
	}

	// nn left
	if (i == 0) {
		S_lf = (*S)[L-1][j];
	}
	else {
		S_lf = (*S)[i-1][j];
	}

	// nn right
	if (i == (L-1)) {
		S_rt = (*S)[0][j];
	}
	else {
		S_rt = (*S)[i+1][j];
	}

	//printf("S_up=%d, S_dn=%d, S_lf=%d, S_rt=%d\n", S_up, S_dn, S_lf, S_rt);

	int dE = 2 * J * (*S)[i][j] * (S_up + S_dn + S_lf + S_rt);

	return dE;
}

int main() {
	srand(time(NULL));

	int S[L][L]; 

	double T = 5; //starting T
	double T_step = 0.01;
	int N_Tsteps = T/T_step;

	initialise(&S, T);

	//prspins(&S);
	//showspins(&S);

	int N_itr = 1000000;

	for (int t = 0; t < (N_Tsteps+1); t++) {

		for (int itr = 0; itr < N_itr; itr++) {
			int i = rdn_int(0, L);
			int j = rdn_int(0, L);

			int dE = get_ssflip_dE(i, j, &S);

			//prspins(&S);

			//printf("itr=%d, i=%d, j=%d, dE=%d\n", itr, i, j, dE);

			//printf("\033[2J\033[1;1H");
			//printf("itr=%d, dE=%d\n", itr, dE);
			//showspins(&S);

			if (dE <= 0) {
				S[i][j] *= -1;
				//printf("   flip spin %d,%d\n", i, j);
			}
			else {
				double r = rdn();
				if (r < exp(-dE / T)) {
					S[i][j] *= -1; 
					//printf("   >0 flip spin %d,%d\n", i, j);
				}
			}
		}

		printf("\033[2J\033[1;1H");
		printf("T=%f, J=%d, L=%d, N=%d\n", T, J, L, N);
		showspins(&S);

		T -= T_step;
	}
}
