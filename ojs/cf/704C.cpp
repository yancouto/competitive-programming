#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define lld I64d
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif
const int N = 112345;

ll memo[N][2][2][2][2];
int seen[N][2][2][2][2], t;
int a[N][2], k[N];

vector<int> v;
ll solve(int i, bool prev0, bool f0, bool f1, bool need) {
	if(i == v.size()) return need == 0;
	ll &r = memo[i][prev0][f0][f1][need];
	if(seen[i][prev0][f0][f1][need] == t) return r;
	seen[i][prev0][f0][f1][need] = t;
	if(i == 0) {
		if(k[v[i]] == 1) return r = mod(solve(1, 0, 0, 0, need ^ (a[v[0]][0] < 0)) + solve(1, 1, 1, 0, need ^ (a[v[0]][0] > 0)));
		if(abs(a[v[i]][0]) == abs(a[v[i]][1])) {
			if(need == 0) return r = (a[v[i]][0] == a[v[i]][1]);
			return r = 1 + (a[v[i]][0] != a[v[i]][1]);
		}
		r = 0;
		for(int b = 0; b < 4; b++) {
			bool F0 = b & 1, F1 = (b >> 1) & 1;
			r += solve(1, F0, F0, F1, need ^ (((a[v[i]][0] < 0) ^ F0) || ((a[v[i]][1] < 0) ^ F1)));
		}
		return r = mod(r);
	} else if(i != v.size() - 1) {
		if(i) assert(k[v[i]] == 2);
		if(i) assert(abs(a[v[i-1]][0]) == abs(a[v[i]][1]));
		int val = prev0 ^ (a[v[i]][1] < 0);
		return r = mod(solve(i + 1, true, f0, f1, need ^ (val | (a[v[i]][0] > 0))) + solve(i + 1, false, f0, f1, need ^ (val | (a[v[i]][0] < 0))));
	} else {
		if(k[v[i]] == 1) return r = (need == (prev0 ^ (a[v[i]][0] < 0)));
		if(abs(a[v[i]][1]) == abs(a[v[i-1]][0])) swap(a[v[i]][0], a[v[i]][1]);
		if(v.size() == 2 && k[v[0]] == 2 && abs(a[v[i]][1]) == abs(a[v[0]][1]))
			return r = (need == (((a[v[i]][0] < 0) ^ f0) | ((a[v[i]][1] < 0) ^ f1)));
		if(abs(a[v[i]][1]) == abs(a[v[0]][0]))
			return r = (need == (((a[v[i]][0] < 0) ^ prev0) | ((a[v[i]][1] < 0) ^ f0)));
		if(k[v[0]] == 2 && abs(a[v[i]][1]) == abs(a[v[0]][1]))
			return r = (need == (((a[v[i]][0] < 0) ^ prev0) | ((a[v[i]][1] < 0) ^ f1)));
		return r = need + (need == ((a[v[i]][0] < 0) ^ prev0));
	}
}

pii proc(vector<int> v) {
	::v = v;
	t++;
	return pii(solve(0, 0, 0, 0, 0), solve(0, 0, 0, 0, 1));
}

vector<pii> V;
ll memo2[N][2];
int seen2[N][2];

ll solve2(int i, bool need) {
	if(i == V.size()) return need == 0;
	ll &r = memo2[i][need];
	if(seen2[i][need] == t) return r;
	seen2[i][need] = t;
	return r = mod(solve2(i + 1, need) * V[i].fst + solve2(i + 1, !need) * V[i].snd);
}

ll proc2(vector<pii> v) {
	V = v; t++;
	return solve2(0, 1);
}

set<int> oc[N];
int mrk[N];

int main() {
	int i, j, n, m;
	scanf("%d %d", &n, &m);
	set<int> s;
	for(i = 0; i < n; i++) {
		scanf("%d", &k[i]);
		for(j = 0; j < k[i]; j++) {
			scanf("%d", &a[i][j]);
			oc[abs(a[i][j])].insert(i);
			mrk[abs(a[i][j])] = 1;
		}
		s.insert(i);
	}
	vector<pii> all;
	while(!s.empty()) {
		vector<int> v;
		v.pb(*s.begin());
		while(true) {
			int x = v.back();
			s.erase(x);
			for(j = 0; j < k[x]; j++)
				oc[abs(a[x][j])].erase(x);
			if(k[x] == 2 && !oc[abs(a[x][1])].empty()) swap(a[x][0], a[x][1]);
			//printf(">>> %3d %3d\n", a[x][0], a[x][1]);
			if(oc[abs(a[x][0])].empty()) break;
			v.pb(*oc[abs(a[x][0])].begin());
		}
		all.pb(proc(v));
		//printf("%lld %lld\n", all.back().fst, all.back().snd);
		//puts("=========");
	}
	ll ans = proc2(all);
	for(i = 1; i <= m; i++)
		if(!mrk[i])
			ans = mod(ans + ans);
	printf("%lld\n", ans);
}
