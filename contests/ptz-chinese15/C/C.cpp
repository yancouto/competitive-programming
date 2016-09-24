#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 5123;
int S[N][60], k[N];
ll A[N >> 6][60][60];
ll C[N];

int main() {
	int i, n, j, g, l, r;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &k[i]);
		for(j = 0; j < k[i]; j++)
			scanf("%d", &S[i][j]);
		S[i][k[i]++] = 0;
		sort(S[i], S[i] + k[i]);
	}
	for(i = 0; i < n; i++)
		for(l = 0; l <= 50; l++) {
			ll x = 0;
			for(r = l + 1; r <= 50; r++) {
				if(binary_search(S[i], S[i] + k[i], r)) x = 1;
				A[i >> 6][l][r] |= (ll(x) << (i & 63));
			}
		}
	int ans = 0;
	for(i = 1; i < n; i++) {
		for(j = 0; j < i; j += 64)
			C[j >> 6] = 0;
		for(g = 1; g < k[i]; g++)
			for(j = 0; j < i; j += 64)
				C[j >> 6] ^= A[j >> 6][S[i][g-1]][S[i][g]];
		for(j = 0; j + 64 < i; j += 64)
			ans += __builtin_popcountll(C[j >> 6]);
		for(; j < i; j++)
			ans += ((C[j >> 6] >> (j & 63)) & 1);
	}
	printf("%d\n", ans);
}
