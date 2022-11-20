#ifndef PSEUDO_H
#define PSEUDO_H

double rdn() {
	return((rand() % 10000) / 10000.0);
}

int rdn_int(int lb, int ub) {
	return((rand() % ((ub-1) - lb + 1)) + lb);
}

#endif
