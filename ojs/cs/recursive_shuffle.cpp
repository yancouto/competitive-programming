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
const int N = 112345;
int a[N], p[N];

int solve(int i, int n) {
	if(n == 1) { assert(i == 1); return 1; }
	if(i & 1) {
		return (n / 2) + solve((i + 1) / 2, (n + 1) / 2);
	} else {
		return solve(i / 2, n / 2);
	}
}

int main() {
	int i, n, m;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		scanf("%d", &a[i]);
		p[i] = solve(a[i], n);
	}
	for(i = 1; i < m; i++)
		if(p[i] != p[i - 1] + 1)
			break;
	printf("%d\n", i == m);
}
