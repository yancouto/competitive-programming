#include <bits/stdc++.h>
using namespace std;
#define i first
#define j second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 512345;

int S[N], sz[N], r, c;
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

bool ok;
void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) {
		ok = true;
		return;
	}
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
}

inline bool bord(pii p) {
	return p.i == 0 || p.j == 0 || p.i == r || p.j == c;
}

map<pii, int> mp;
pii b[N];
int lst;
int get(pii p) {
	if(!mp.count(p)) {
		int i = mp[p] = mp.size() - 1;
		b[i] = p;
		S[i] = i; sz[i] = 1;
		if(lst != -1 && bord(p)) join(i, lst);
		if(bord(p)) lst = i;
	}
	return mp[p];
}
set<pair<pii, pii>> s, ar;
vector<pii> v[N];
int di[4] = {1, -1, 0, 0};
int dj[4] = {0, 0, 1, -1};

int main() {
	int i, w;
	for_tests(t, tt) {
		mp.clear(); s.clear(); ok = false; lst = -1; ar.clear();
		// CASO r ou c == 1 e ambos == 1
		scanf("%d %d %d", &r, &c, &w); 
		for(i = 0; i < w; i++) {
			pii p, q, a, b;
			scanf("%d %d %d %d", &p.i, &p.j, &q.i, &q.j); p.i--, p.j--, q.i--, q.j--;
			if(p > q) swap(p, q);
			if(s.count(make_pair(p, q))) continue;
			s.insert(make_pair(p, q));
			int ida, idb;
			if(p.i == q.i)
				a = pii(p.i + 1, p.j + 1), b = pii(p.i, p.j + 1);
			else
				a = pii(p.i + 1, p.j + 1), b = pii(p.i + 1, p.j);
			ar.insert(make_pair(a, b));
			ar.insert(make_pair(b, a));
			ida = get(a), idb = get(b);
			join(ida, idb);
		}
		if(r == c && r == 1) { puts("Chefland is doomed"); continue; }
		if(ok) { puts("0"); continue; }
		if(min(r, c) == 1) { puts("1"); continue; }
		for(i = 0; i < mp.size(); i++)
			v[find(i)].pb(b[i]);
		bool ok1 = false;
		for(i = 0; i < mp.size(); v[i++].clear())
			if(find(i) == i) {
				sort(v[i].begin(), v[i].end());
				bool any_bord = false;
				for(pii p : v[i]) any_bord |= bord(p);
				for(pii p : v[i]) {
					if(bord(p)) continue;
					for(int d = 0; d < 4; d++) {
						pii q(p.i + di[d], p.j + dj[d]);
						if(((any_bord && bord(q)) || binary_search(v[i].begin(), v[i].end(), q)) && !ar.count(make_pair(p, q)))
							ok1 = true;
					}
				}
			}
		if(ok1) puts("1");
		else puts("2");
	}
}
