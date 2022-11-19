#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define L 10
#define N (L*L)
#define J 1
#define T 2.5

// int *s[L][L];

double rdn() {
	return((rand() % 10000) / 10000.0);
}

int rdn_int(int lb, int ub) {
	return((rand() % ((ub-1) - lb + 1)) + lb);
}

void initialise(int (*S)[L][L]) {
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
	
}

void prspins(int (*S)[L][L]) {
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < L; j++) {
			printf("%d,%d=%d   ", i, j, (*S)[i][j]); 
		}
		printf("\n");
	}

}

int deltaE(int i, int j, int (*S)[L][L]) {
	// periodic bcs
	int S_up, S_dn, S_lf, S_rt; 
	//printf("%d,%d\n", i, j);

	// up
	if (j == (L-1)) {
		S_up = (*S)[i][0]; 
		//printf("edge\n"); 
	}
	else {
		S_up = (*S)[i][j+1];
	}

	// dn
	if (j == 0) {
		S_dn = (*S)[i][L-1];
		//printf("edge\n"); 
	}
	else {
		S_dn = (*S)[i][j-1];
	}

	// left
	if (i == 0) {
		S_lf = (*S)[L-1][j];
		//printf("edge\n"); 
	}
	else {
		S_lf = (*S)[i-1][j];
	}

	// right
	if (i == (L-1)) {
		S_rt = (*S)[0][j];
		//printf("edge\n"); 
	}
	else {
		S_rt = (*S)[i+1][j];
	}

	//printf("S_up=%d, S_dn=%d, S_lf=%d, S_rt=%d\n", S_up, S_dn, S_lf, S_rt);

	int dE = 2 * J * (*S)[i][j] * (S_up + S_dn + S_lf + S_rt);

	return dE;

}

int main() {
	int S[L][L]; 
	initialise(&S);
	//prspins(&S);

	srand(time(NULL));

	for (int itr = 0; itr < 5; itr++) {
		int i = rdn_int(0, L);
		int j = rdn_int(0, L);

		int dE = deltaE(i, j, &S);

		//prspins(&S);

		//printf("itr=%d, i=%d, j=%d, dE=%d\n", itr, i, j, dE);

		if (dE <= 0) {
			S[i][j] *= -1;
			//printf("   flip spin %d,%d\n", i, j);
		}
		else {
			double r = rdn();
			if (r < exp(-dE / T)) {
				S[i][j] *= -1; 
				//printf("   >0 flip, r=%f, exp(-dE/T)=%f\n", 
						r, exp(-dE/T));
				//printf("   flip spin %d,%d\n", i, j);
				//prspins(&S);
			}
		}
		
	}
}
