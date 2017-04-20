#include <bits/stdc++.h>
using namespace std;

const int N = 112345;
int a[N][4];
int seen[N][4];
int mrk[N];

int go(int f, int t) {
	int of = f, ot = t;
	int all = 0;
	//printf("start (%d, %d[%d])\n", f+1, t, a[f][t]+1);
	do {
		int nf = a[f][t];
		for(int i = 0; i < 4; i++)
			if(f == a[nf][i]) {
				//printf("%d == a[%d][%d]\n", f, nf, i);
				t = (i + 2) % 4;
				break;
			}
		mrk[f = nf]++;
		//printf("at (%d, %d[%d])/(%d, %d)\n", f+1, t, a[f][t]+1, of+1, ot);
		seen[f][t] = seen[f][(t + 2) % 4] = 1;
		//if(all++ > 20) exit(0);
	} while(f != of || t != ot);
}

int main() {
	int T, n, g, i;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &n, &g); g--;
		for(i = 0; i < n; i++) mrk[i] = 0;
		for(i = 0; i < n; i++) {
			scanf("%d %d %d %d", &a[i][0], &a[i][1], &a[i][2], &a[i][3]);
			for(int j = 0; j < 4; j++) a[i][j]--, seen[i][j] = 0;
		}
		go(g, 0);
		if(mrk[g] == 1) go(g, 1);
		int ct = 0;
		for(i = 0; i < n; i++)
			if(mrk[i] < 2) {
				if(!seen[i][0]) {
					go(i, 0);
					ct++;
				}
				if(!seen[i][1]) {
					go(i, 1);
					ct++;
				}
			}
		printf("%d\n", ct);
	}
}
