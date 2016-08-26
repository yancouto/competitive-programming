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

char S[1123456];
const int N = 1123456;

map<char, int> tr[N];
vector<int> mrk[N];
vector<pii> ps;
int en = 1, ans = 0;

int dfs(int u, int h) {
	for(auto e : tr[u]) {
		int k = dfs(e.snd, h + 1);
		if(k != -1) mrk[u].pb(k);
	}
	while(mrk[u].size() >= 2) {
		int a = mrk[u].back(); mrk[u].pop_back();
		int b = mrk[u].back(); mrk[u].pop_back();
		ps.pb(pii(a, b)); ans += h;
	}
	if(!mrk[u].empty()) return mrk[u][0];
	return -1;
}

int main() {
	int i, n, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%s", S);
		int v = 0;
		for(j = 0; S[j]; j++) {
			if(!tr[v].count(S[j])) tr[v][S[j]] = en++;
			v = tr[v][S[j]];
		}
		mrk[v].pb(i);
	}
	dfs(0, 0);
	printf("%d\n", ans);
	for(pii p : ps)
		printf("%d %d\n", p.fst + 1, p.snd + 1);
}
