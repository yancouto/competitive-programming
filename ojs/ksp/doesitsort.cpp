#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int n;
char op[1123][12];
int l[1123], r[1123];

bool sort(int vec) {
	int i;
	for(i = 0; i < n; i++)
		if(op[i][0] == 's') {
			int rl = (1 << (r[i] - l[i] + 1)) - 1;
			int ct = __builtin_popcount((vec >> l[i]) & rl);
			vec &= ~(rl << l[i]);
			vec |= ((1 << ct) - 1) << (l[i] + (r[i] - l[i] + 1) - ct);
		} else {
			if(((vec >> l[i]) & 1) && !((vec >> r[i]) & 1)) {
				vec ^= (1 << l[i]);
				vec ^= (1 << r[i]);
			}
		}
	int ct = __builtin_popcount(vec);
	return vec == (((1 << ct) - 1) << (20 - ct));
}

int main() {
	int i;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%s %d %d", op[i], &l[i], &r[i]);
		if(op[i][0] == 's') r[i]--;
	}
	for(i = 0; i < (1 << 20); i++)
		if(!sort(i)) {
			puts("incorrect");
			for(int j = 0; j < 20; j++)
				printf("%d ", (i >> j) & 1);
			putchar('\n');
			return 0;
		}
	puts("correct");
}
