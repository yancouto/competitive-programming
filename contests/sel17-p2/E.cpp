#include <bits/stdc++.h>
using namespace std;

char g[1000][1000];
int di[] = {0, 1,  0, -1};
int dj[] = {1, 0, -1,  0};
char s[112345];

int main() {
	int T;
	scanf("%d", &T);
	printf("%d\n", T);
	for(int i = 0; i < 1000; i++)
		for(int j = 0; j < 1000; j++)
			g[i][j] = '#';
	while(T--) {
		scanf("%s", s);
		int i = 400, j = 400;
		int d = 0;
		g[i][j] = '.';
		int mni = i, mxi = i, mxj = j;
		for(int k = 0; s[k]; k++) {
			if(s[k] == 'F');
			else if(s[k] == 'R') d = (d + 1) % 4;
			else if(s[k] == 'B') d = (d + 2) % 4;
			else if(s[k] == 'L') d = (d + 3) % 4;
			i += di[d]; j += dj[d];
			g[i][j] = '.';
			mni = min(mni, i);
			mxi = max(mxi, i);
			mxj = max(mxj, j);
		}
		mni--; mxi++; mxj++;
		printf("%d %d\n", mxi - mni + 1, mxj - 400 + 1);
		for(i = mni; i <= mxi; i++) {
			for(j = 400; j <= mxj; j++) {
				putchar(g[i][j]);
				g[i][j] = '#';
			}
			putchar('\n');
		}

	}
}
