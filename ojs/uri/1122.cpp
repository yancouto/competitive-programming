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


int seen[43][81234], t;
int memo[43][81234], F, n, a[50];
const int D = 40909;
int ok(int i, int sum) {
	if(i == n) return sum == F;
	int &r = memo[i][sum + D];
	if(seen[i][sum + D] == t) return r;
	seen[i][sum + D] = t;
	r = ok(i + 1, sum + a[i]) || ok(i + 1, sum - a[i]);
	return r;
}

set<char> pos[43];
int seen2[43][81234], t2;
void dfs(int i, int sum) {
	if(i == n) return;
	if(seen2[i][sum + D] == t2) return;
	seen2[i][sum + D] = t2;
	if(ok(i + 1, sum + a[i])) pos[i].insert('+'), dfs(i + 1, sum + a[i]);
	if(ok(i + 1, sum - a[i])) pos[i].insert('-'), dfs(i + 1, sum - a[i]);
}

int main() {
	int i;
	while(scanf("%d %d", &n, &F) != EOF && n) {
		for(i = 0; i < n; i++)
			scanf("%d", &a[i]), pos[i].clear();
		t++;
		if(ok(0, 0)) {
			t2++;
			dfs(0, 0);
			for(i = 0; i < n; i++)
				putchar(pos[i].size() == 2? '?' : *pos[i].begin());
			putchar('\n');
		} else {
			puts("*");
		}
	}
}
