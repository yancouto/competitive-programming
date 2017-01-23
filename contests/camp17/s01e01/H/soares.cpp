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

int n;
const int N = 512345;
set<int> adj[N];
int S[N], seen[N], t, sz[N];

void go(int u, int val) {
	if(seen[u] == t) return;
	S[u] = val;
	sz[val]++;
	seen[u] = t;
	for(int v : adj[u])
		go(v, val);
}

int main() {
	int i, j, a, b; char op;
	read(n);
	for(i = 0; i < n; i++) S[i] = i;
	int lst = n;
	while(true) {
		scanf(" %c", &op);
		if(op == 'E') return 0;
		scanf(" %d %d", &a, &b); a--; b--;
		if(op == 'T') {
			puts(S[a] == S[b]? "YES" : "NO");
			fflush(stdout);
		} else if(op == 'C') {
			if(sz[S[a]] < sz[S[b]]) swap(a,b);
			t++;
			go(b, S[a]);
			adj[a].insert(b);
			adj[b].insert(a);
		} else {
			typedef pair<int, set<int>::iterator> pis;
			vector<pis> va, vb;
			t++;
			seen[a] = seen[b] = t;
			adj[a].erase(b); adj[b].erase(a);
			if(!adj[a].empty()) va.pb(pis(a, adj[a].begin()));
			if(!adj[b].empty()) vb.pb(pis(b, adj[b].begin()));
			while(!va.empty() && !vb.empty()) {
				int x = *va.back().snd;
				pis p = va.back();
				if(seen[x] != t && !adj[x].empty()) va.pb(pis(x, adj[x].begin()));
				seen[x] = t;
				++p.snd;
				if(p.snd != adj[p.fst].end()) va.pb(p);

				x = *vb.back().snd;
				p = vb.back();
				if(seen[x] != t && !adj[x].empty()) vb.pb(pis(x, adj[x].begin()));
				seen[x] = t;
				++p.snd;
				if(p.snd != adj[p.fst].end()) vb.pb(p);
			}
			t++;
			lst++;
			if(va.empty()) { go(a, lst); sz[S[b]] -= sz[lst]; }
			else { go(b, lst); sz[S[a]] -= sz[lst]; }
		}
	}
}
