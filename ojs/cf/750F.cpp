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

void end(int x) {
	printf("! %d\n", x); fflush(stdout);
}

int n;
map<int, set<int>> mp;
bool done = false;
set<int> query(int u) {
	if(mp.count(u)) return mp[u];
	printf("? %d\n", u); fflush(stdout);
	int k, x; set<int> ans;
	scanf("%d", &k);
	if(k == 0) exit(0);
	for(int i = 0; i < k; i++) {
		scanf("%d", &x);
		ans.insert(x);
	}
	mp[u] = ans;
	if(k == 2) {
		done = true;
		end(u);
	}
	return mp[u];
}

void solve() {
	int h;
	mp.clear(); done = false;
	scanf("%d", &h);
	if(h == 0) exit(0);
	set<int> adj = query(1);
	if(done) return;
	deque<int> path;
	path.pb(1);
	int cur = 1;
	while(adj.size() != 1) {
		for(int x : adj)
			if(!mp.count(x)) {
				cur = x;
				path.pb(x);
				adj = query(x);
				if(done) return;
				break;
			}
	}
	adj = query(1);
	if(done) return;
	cur = 1;
	do {
		for(int x : adj)
			if(!mp.count(x)) {
				cur = x;
				path.push_front(x);
				adj = query(x);
				if(done) return;
				break;
			}
	} while(adj.size() != 1);
	assert((path.size() & 1) && path.size() >= 3);
	int ch = h - (path.size() / 2);
	int v = path[path.size() / 2];
	while(ch > 4) {
		while(path.back() != v) path.pop_back();
		adj = query(v);
		cur = v;
		while(adj.size() != 1) {
			for(int x : adj)
				if(!mp.count(x)) {
					cur = x;
					path.pb(x);
					adj = query(x);
					if(done) return;
					break;
				}
		}
		assert(path.size() & 1);
		ch = h - (path.size() / 2);
		v = path[path.size() / 2];
	}
	adj = query(v);
	set<int> old = adj;
	for(int x : adj)
		if(!mp.count(x)) {
			if(ch == 2) {
				end(x);
				return;
			}
			v = x;
			adj = query(v);
			if(done) return;
		}
	for(int x : old) assert(mp.count(x));
	ch--;
	set<int> pos;
	if(ch == 2) {
		adj = query(v);
		for(int x : adj)
			if(!mp.count(x))
				pos.insert(x);
	} else {
		adj = query(v);
		for(int x : adj) {
			set<int> a2 = query(x);
			if(done) return;
			for(int y : a2)
				if(!mp.count(y))
					pos.insert(y);
		}
	}
	assert(!pos.empty());
	while(true) {
		if(pos.size() == 1) {
			end(*pos.begin());
			return;
		} else {
			query(*pos.begin());
			pos.erase(pos.begin());
			if(done) return;
		}
	}
}

int main() {
	int i, j, t;
	scanf("%d", &t);
	for(i = 0; i < t; i++) solve();
}
