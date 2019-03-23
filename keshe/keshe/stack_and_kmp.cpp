#include "stack_and_kmp.h"

int * buildNext(string P)
{
	int m = P.size(), j = 0;
	int *N = new int[m];
	int t = N[0] = -1;
	while (j < m - 1)
		if (0 > t || P[j] == P[t]) {
			j++; t++;
			if (P[j] == P[t])N[j] = N[t];
			else N[j] = t;
			//N[j] = (P[++j] != P[++t] ? t : N[t]);
		}
		else t = N[t];
	return N;
}

int kmp(string P, string T)
{
	int *next = buildNext(P);
	int n = T.size(), i = 0;
	int m = P.size(), j = 0;
	while (j < m  && i < n)
		if (0 > j || T[i] == P[j])
		{
			i++;  j++;
		}
		else
			j = next[j];
	delete[] next;
	return i - j;
}

