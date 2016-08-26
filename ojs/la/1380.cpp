#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

int memo[1002][1002], seen[1002][1002], tempo, a[1002];
int solve(int l, int r) {
	if(r - l == 1) return abs(a[r] - a[l]);
	int &m = memo[l][r];
	if(seen[l][r] == tempo) return m;
	seen[l][r] = tempo;
	if(a[l + 1] >= a[r]) m = solve(l + 2, r) + a[l] - a[l+1];
	else m = solve(l + 1, r - 1) + a[l] - a[r];
	if(a[l] >= a[r-1]) m = max(m, solve(l + 1, r - 1) + a[r] - a[l]);
	else m = max(m, solve(l, r - 2) + a[r] - a[r-1]);
	return m;
}

int main() {
	int i, n, t = 0;
	while(true) {
		scanf("%d", &n);
		if(!n) return 0;
		for(i = 0; i < n; i++)
			scanf("%d", &a[i]);
		tempo++;
		printf("In game %d, the greedy strategy might lose by as many as %d points.\n", ++t, solve(0, n - 1));
	}
}
