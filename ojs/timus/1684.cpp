#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

const int MAX = 75009;
ull h[2][MAX];
ull pot[MAX];
char s[2][MAX];

void hash(int i) {
	ull p = 1, hs = 0; int j;
	for(j = 0; s[i][j]; j++) {
		pot[j] = p;
		h[i][j] = hs = mod(hs + p*s[i][j]);		
		p = mod(p * 267);
	}
	pot[j] = p;
}

bool eq(int i, int j, int x, int y) {
	int f = 0;
	if(i > x) { swap(i, x); swap(j, y); f = !f; }
	ull h1 = mod(h[f][j] - h[f][i-1] + modn), h2 = mod(h[!f][y] - h[!f][x-1] + modn);
	h1 = mod(h1 * pot[x - i]);
	return h1 == h2;
}


int main() {
	int i, j;
	scanf("%s %s", s[0], s[1]);
	hash(0); hash(1);
	int r = strlen(s[1]) - 1;
	int st[MAX], sn = 0; st[sn++] = r;
	for(i = r; i >= 0; i--) {
		if(eq(0, r - i, i, r))
			st[sn++] = r = i - 1;
	}
	if(r >= 0) puts("Yes");
	else {
		puts("No");
		for(i = sn - 1; i > 0; i--) {
			for(j = st[i] + 1; j <= st[i-1]; j++)
				putchar(s[0][j - st[i] - 1]);
			if(i > 1) putchar(' ');
		}
		putchar('\n');
	}
	
}
