#include <bits/stdc++.h>
using namespace std;

int shift(int m, int d) {
	if(d >= 0) return m << d;
	else return m >> (-d);
}

bool ok(int bm, int tt[4], int m[3]) {
	int t[6] = {0, tt[0], tt[1], tt[2], tt[3], 0};
	int i, j, k;
	for(i = 1; i <= 4; i++)
		for(j = 0; j < 4; j++)
			if((1 << ((i-1) * 4 + j)) & bm)
				for(k = 0; k < 3; k++)
					t[i - 1 + k] ^= shift(m[k], j - 1);
	for(i = 1; i <= 4; i++)
		if(t[i] & 0xf)
			break;
	if(i > 4) return true;
	for(i = 1; i <= 4; i++)
		if((t[i] & 0xf) != 0xf)
			break;
	return i > 4;
}

int main() {
	int i, j; char c;
	int t[4] = {0, 0, 0, 0};
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			scanf(" %c", &c);
			t[i] |= ((c == 'B') << j);
		}
	}
	int m[3] = {0, 0, 0};
	for(i = 0; i < 3; i++) {
		int w = 0;
		for(j = 0; j < 3; j++) {
			scanf(" %c", &c);
			m[i] |= ((c == '1') << j);
		}
	}
	int mn = INT_MAX;
	for(i = 0; i < (1 << 16); i++)
		if(ok(i, t, m))
			mn = min(mn, __builtin_popcount(i));
	if(mn == INT_MAX) puts("Impossible");
	else printf("%d\n", mn);
}
