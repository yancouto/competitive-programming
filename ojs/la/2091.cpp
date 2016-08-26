#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<long long, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

char ln[2000009];
char name[2009];
map<string, int> mp;
vector<int> adj[100009];
int deg[100009];
int get() {
	string st(name);
	if(!mp.count(st)) {
		mp[st] = mp.size() - 1;
		deg[mp[st]] = 0;
		adj[mp[st]].clear();
	}
	return mp[st];
}
int skip(int &p) {
	while(isspace(ln[p])) p++;
	while(isalpha(ln[p])) p++;
}
pii& operator += (pii &a, const pii &b) {
	a.fst += b.fst;
	a.snd += b.snd;
	return a;
}

int s, f;
pii memo[100009][3];
pii solve(int i, int buy) {
	pii &r = memo[i][buy];
	if(r.fst != -1) return r;
	pii a = pii(buy * s, buy), b = pii(f, 1);
	for(int v : adj[i]) {
		a += solve(v, true);
		b += solve(v, false);
	}
	if(buy == 2) { a += pii(-buy * s, -buy); b = a; }
	return r = min(a, b);
}
int ns, nf;
void build(int i, int buy) {
	pii a = pii(buy * s, buy), b = pii(f, 1);
	for(int v : adj[i]) {
		a += solve(v, true);
		b += solve(v, false);
	}
	if(buy == 2) { a += pii(-buy * s, -buy); b = a; }
	if(solve(i, buy) == a) {
		if(buy == 1) ns++;
		for(int v : adj[i])
			build(v, true);
	} else {
		nf++;
		for(int v : adj[i])
			build(v, false);
	}
}

int main() {
	int i, ss, ff, t = 0;
	fgets(ln, sizeof ln, stdin);
	sscanf(ln, "%d %d", &ss, &ff);
	while(true) {
		s = ss; f = ff;
		if(!s) return 0;
		mp.clear();
		while(true) {
			fgets(ln, sizeof ln, stdin);
			if(sscanf(ln, "%d %d", &ss, &ff) == 2) break;
			sscanf(ln, "%s", name);
			int pi = get(), p = 0; skip(p);
			while(true) {
				if(sscanf(ln + p, "%s", name) != 1) break;
				adj[pi].pb(get()); deg[get()]++;
				skip(p);
			}
		}
		adj[mp.size()].clear();
		for(i = 0; i < mp.size(); i++){
			if(!deg[i])
				adj[mp.size()].pb(i);
			memo[i][0] = memo[i][1] = pii(-1, -1);
		}
		memo[mp.size()][0] = memo[mp.size()][1] = memo[mp.size()][2] = pii(-1, -1);
		ns = nf = 0;
		build(mp.size(), 2);
		printf("%d. %d %d %lld\n", ++t, ns, nf, solve(mp.size(), 2).fst);
	}
}
