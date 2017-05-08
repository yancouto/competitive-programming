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

const int N = 112345;
vector<int> v;
vector<int> adj[N];
ll y[N], x[N];
int ans[N];
int n;

bool rem(int a, int b, int c) {
	ll x1 = x[b] - x[a], y1 = y[b] - y[a];
	ll x2 = x[c] - x[a], y2 = y[c] - y[a];
	return x1 * y2 - x2 * y1 >= 0;
}

void go(int u, int h) {
	x[u] = h;
	deque<int> bk;
	while(v.size() > 1 && rem(u, v.back(), v[v.size() - 2]))
		bk.push_front(v.back()), v.pop_back();
	if(u) ans[u] = v.back();
	v.pb(u);
	for(int v : adj[u])
		go(v, h + 1);
	v.pop_back();
	for(int x : bk) v.pb(x);
}

int main() {
	int i, x;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%lld", &y[i]);
	for(i = 1; i < n; i++) {
		scanf("%d", &x); x--;
		adj[x].pb(i);
	}
	go(0, 1);
	for(i = 1; i < n; i++)
		printf("%d\n", ans[i] + 1);
}
