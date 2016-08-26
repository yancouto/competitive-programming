#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
inline string bit(int x) { return bitset<8>(x).to_string();}
int memo2[1 << 9][1 << 9][9];
int join(int all, int row, int n) {
	int &r = memo2[all][row][n];
	if(r != -1) return r;
	r = row | all;
	for(int i = n - 2; i >= 0; i--)
		if(!(row & (1 << i)) && !(r & (1 << (i + 1))) && (r & (1 << i)))
			r ^= (1 << i);
	return r;
}

ll memo[9][1 << 9][69][10];
ll solve(int left, int bm, int k, int n) {
	if(k < 0) return 0;
	if(left == 0) return bm & 1;
	ll &r = memo[left][bm][k][n];
	if(r != -1) return r;
	r = 0;
	for(int i = 0; i < (1 << n); i++) {
		int bm2 = join(bm, i, n);
		r += solve(left - 1, bm2, k - __builtin_popcount(i), n);
	}
	return r = mod(r);
}

int main() {
	int n, m, k;
	memset(memo, -1, sizeof memo);
	memset(memo2, -1, sizeof memo2);
	for_tests(t, tt) {
		scanf("%d %d %d", &n, &m, &k);
		printf("Case #%d: %d\n", tt, int(solve(m, (1 << (n - 1)) - 1, k, n)));
	}
}
