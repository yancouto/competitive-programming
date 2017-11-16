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

const int N = 1123456;
vector<int> adj[N];
int a[N];
bool seen[N];

int go(int i) {
	if(seen[i]) return 0;
	seen[i] = 1;
	int mx = i;
	for(int j : adj[i])
		mx = max(mx, go(j));
	return mx;
}

int main() {
	int i, n;
	while(scanf("%d", &n) != EOF && n) {
		for(i = 0; i < n; i++) scanf("%d", &a[i]);
		for(i = 0; i < n; i++) { adj[i].clear(); seen[i] = 0; }
		map<int, vector<int>> mp;
		for(i = n - 1; i >= 0; i--) {
			for(int j : mp[-a[i] - i])
				adj[i].pb(j), adj[j].pb(i);
			mp[a[i] - i].pb(i);
		}
		printf("%d\n", go(0));
	}
}
