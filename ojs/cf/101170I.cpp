#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

const int N = 112345;
vector<int> adj[2][N];

template<class num> inline void rd(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

int n;

vector<int> go(vector<int> &o, bool b) {
	vector<int> d(n, 1e8);
	queue<int> q;
	for(int x : o) d[x] = 0, q.push(x);
	while(!q.empty()) {
		int x = q.front(); q.pop();
		for(int y : adj[b][x])
			if(d[y] > d[x] + 1) {
				d[y] = d[x] + 1;
				q.push(y);
			}
	}
	return d;
}

int main() {
	int i, j;
	int m, k, b, a;
	rd(n); rd(m); rd(k);
	vector<int> o, c;
	for(i = 0; i < m; i++) { rd(b); o.pb(b - 1); }
	for(i = 0; i < k; i++) { rd(b); c.pb(b - 1); }
	for(i = 0; i < n; i++) {
		rd(a);
		while(a--) {
			rd(b); b--;
			adj[0][i].pb(b);
			adj[1][b].pb(i);
		}
	}
	vector<int> x;
	x.pb(0);
	vector<int> od = go(o, 1), cd = go(c, 1), xd = go(x, 0);
	int best = INT_MAX;
	for(i = 0; i < n; i++)
		best = min(best, xd[i] + od[i] + cd[i]);
	if(best > .8e8) puts("impossible");
	else printf("%d\n", best);
}
