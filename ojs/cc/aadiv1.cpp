#include <cstdio> 
#include <algorithm>
typedef unsigned long long ull;

int B[103][103];
int Acol[103], Arow[103];

int main() {
	int n, m, i, j;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++) {
			scanf("%d", &B[i][j]);
			if(B[i][j] == 1)
				Acol[i] = Arow[j] = 1;
		}
	bool poss = true;
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			if(B[i][j] == 0 && Acol[i] && Arow[j])
				poss = false;
	printf("%s\n", poss? "YES" : "NO");
	return 0;
}