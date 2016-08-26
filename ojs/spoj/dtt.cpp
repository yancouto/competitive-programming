#include <cstdio>
#include <algorithm>
using namespace std;
int d[2][16];
int perf[2], com[2];
int p3[15];
int tr[239][16];
int cnt(int config[16]) {
	int count = 0;
	for(int i = 1; i <= 13; i++)
		count += config[i];
	return count;
}

int solve(int i, int config[16]) {
	if(i == 239 || cnt(config) < 3) return 0;
	int bak[16];
	for(int j = 1; j <= 13; j++) bak[j] = config[j];
	int a = solve(i + 1, config);
	for(int j = 1; j <= 2; j++) {
		int k;
		for(k = 1; k <= 13 && tr[i][k] <= config[k]; k++)
			config[k] -= tr[i][k];
		if(k == 16) a = max(a, solve(i + 1, config) + j);
	}
	for(int j = 1; j <= 13; j++) config[j] = bak[j];
	return a;
}


int main() {
	int i, j, k; p3[0] = 1;
	for(i = 1; i <= 13; i++)	
		p3[i] = p3[i - 1] * 3;
	int count = 0;
	for(i = 1; i <= 13; i++)
		for(j = i; j <= 13; j++)
			for(k = j; k <= 13; k++)
				if((i != j || i != k) && (i + j) > k) {
					// count++;
					tr[count][i]++;
					tr[count][j]++;
					tr[count++][k]++;
				}
	// printf("%d\n", count);
	int n;
	while(true) {
		scanf("%d", &n);
		if(!n) return 0;
		for(i = 1; i <= 13; i++)
			d[0][i] = d[1][i] = 0;
		for(i = 0; i < n; i++) {
			int x;
			scanf("%d", &x);
			d[i & 1][x]++;
		}
		perf[0] = perf[1] = 0;
		for(j = 0; j < 2; j++) {
			for(i = 1; i <= 13; i++) {
				perf[j] += d[j][i] / 3;
				d[j][i] %= 3;
				// printf("%d ", d[j][i]);
			}
			// puts("");
		}
		// printf("ps %d %d\n", perf[0], perf[1]);
		if(perf[0] != perf[1]) { printf("%d\n", (perf[0] < perf[1]) + 1); continue; }
		com[0] = solve(0, d[0]);
		com[1] = solve(0, d[1]);
		// printf("cm %d %d\n", com[0], com[1]);
		if(com[0] == com[1]) puts("0");
		else printf("%d\n", (com[0] < com[1]) + 1);
	}
}