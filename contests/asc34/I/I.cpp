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
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

template<class num> inline void read(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

const int N = 112345;

vector<int> adj[N];

int n;

pii go(int u, int p) {
	pii ans(0, 0);
	bool only = true;
	for(int v : adj[u])
		if(v != p) {
			pii q = go(v, u);
			ans.fst += q.fst;
			ans.snd += q.snd;
			only = false;
		}
	if(ans.snd >= 2) ans.fst += ans.snd - 1, ans.snd = 0;
	else if(ans.snd == 0) ans.snd = 1;
	return ans;
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("tour.in", "r", stdin);
	freopen("tour.out", "w", stdout);
#endif
	int i, j, a, b;
	read(n);
	for(i = 0; i < n - 1; i++) {
		read(a); read(b); a--; b--;
		adj[a].pb(b); adj[b].pb(a);
	}
	int ct = 0;
	for(i = 0; i < n; i++) ct += (adj[i].size() == 1);
	for(i = 0; adj[i].size() == 1; i++);
	pii q = go(i, -1);
	printf("%d\n", q.fst + q.snd);
}
