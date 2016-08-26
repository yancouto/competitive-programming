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
int n, m;
const int MAX = 50009;
int x[MAX], y[MAX], nxt[MAX];

int memo[MAX];
int solve(int i) {
	if(memo[i] != -1) return memo[i];
	int ret = 0;
	for(int j = nxt[i]; j != -1; j = nxt[j])
		if(x[j] > x[i] && y[j] > y[i])
			ret = max(ret, 1 + solve(j));
	return memo[i] = ret;
}


int main() {
	int i, a, b;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) {
		scanf("%d %d", &x[i], &y[i]);
		memo[i] = nxt[i] = -1;
	}
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		nxt[a] = b;
	}
	int mx = 0;
	for(i = 0; i < n; i++)
		mx = max(mx, 1 + solve(i));
	printf("%d\n", mx);
}
