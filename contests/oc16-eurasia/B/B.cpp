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
const int N = 1123456;
vector<int> adj[N];
int p[N], t, d[N], f[N];

void dfs(int u) {
	d[u] = t++;
	for(int v : adj[u])
		dfs(v);
	f[u] = t++;
}

char s[N];
int main() {
	int i, j, n; char c;
	map<string, int> mp;
	scanf("%d", &n);
	for(i = 0; i < (1 << n); i++) {
		scanf("%s", s);
		mp[s] = i;
		p[i] = i;
	}
	int ls = -100;
	for(i = 0; i < n; i++) {
		for(j = 0; j < (1 << (n - i)); j += 2) {
			scanf(" %c", &c);
			if(c == 'W') {
				adj[p[j]].pb(p[j+1]);
				p[j>>1] = p[j];
				ls = p[j];
			} else {
				adj[p[j+1]].pb(p[j]);
				p[j>>1] = p[j+1];
				ls = p[j+1];
			}
		}
	}
	dfs(ls);
	for_tests(qn, qq) {
		scanf("%s", s);
		int a = mp[s];
		scanf("%s", s);
		int b = mp[s];
		if(d[a] <= d[b] && f[a] >= f[b]) puts("Win");
		else if(d[b] <= d[a] && f[b] >= f[a]) puts("Lose");
		else puts("Unknown");
	}
}
