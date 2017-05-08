#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const ll B[2] = {263, 301};
const ll MOD[2] = {1000000007, 1000000009};

const int N = 300;
const int M = N + 2*N*N + 3;


namespace f {
	const int maxv = M;
	const int maxe = maxv * 4;
	typedef int num;
	num inf = INT_MAX;
	int n = maxv;

	int to[maxe], en, nx[maxe], es[maxe], lv[maxv], qu[maxv], cr[maxv];
	num cp[maxe], fl[maxe];

	bool bfs (int s, int t) {
		memset(lv, -1, sizeof(int) * n);
		lv[s] = 0;
		int a = 0, b= 0;
		qu[b++] = s; cr[s] = es[s];
		while (a<b) {
			for (int i = es[qu[a]]; i != -1; i = nx[i]) {
				if (cp[i] > fl[i] && lv[to[i]] == -1) {
					lv[to[i]] = lv[qu[a]] + 1;
					qu[b++] = to[i];
					cr[to[i]] = es[to[i]];
					if (to[i] == t) return true;
				}
			}
			a++;
		}
		return false;
	}

	num dfs (int u, int t, num mx) {
		if (u == t) return mx;
		for (int &i = cr[u]; i != -1; i = nx[i])
			if (cp[i] > fl[i] && lv[to[i]] == lv[u] + 1)
				if (num a = dfs(to[i], t, min(mx, cp[i] - fl[i]))) {
					fl[i] += a;
					fl[i^1] -= a;
					return a;
				}
		return 0;
	}

	num max_flow(int s, int t) {
		num fl = 0, a;
		while (bfs(s,t))
			while (a=dfs(s,t,inf))
				fl += a;
		return fl;
	}

	void reset_all(int n2=maxv) { n = n2; en = 0; memset(es, -1, sizeof(int) * n); }
	void reset_flow() { memset(fl, 0, sizeof(num) * en); }
	
	void add_edge(int a, int b, num c, num rc=0) {
		fl[en] = 0; to[en] = b; cp[en] = c;  nx[en] = es[a]; es[a] = en++;
		fl[en] = 0; to[en] = a; cp[en] = rc; nx[en] = es[b]; es[b] = en++;
	}
};

string str[N];
int n;

struct hsh {
	ll v[2], n, pot[2];

	hsh () {
		v[0] = v[1] = n = 0;
		pot[0] = pot[1] = 1;
	}

	inline void add (ll c) {
		for (int i = 0; i < 2; i++) {
			v[i] = (v[i]*B[i]+c)%MOD[i];
			//v[i] = (v[i] + c)%MOD[i];
			pot[i] = (pot[i]*B[i])%MOD[i];
		}
		n++;
	}

	inline void sub (ll c, ll d) {
		for (int i = 0; i < 2; i++) {
			v[i] = (v[i]*B[i])%MOD[i];
			v[i] = (v[i] - ((c*pot[i])%MOD[i])+MOD[i]+d)%MOD[i];
			//v[i] = (v[i] + MOD[i]+d)%MOD[i];
			//v[i] = (v[i] + d)%MOD[i];
		}
	}

	inline bool operator < (const hsh & ot) const {
		if (n != ot.n) return n < ot.n;
		for (int i = 0; i < 2; i++)
			if (v[i] != ot.v[i])
				return v[i] < ot.v[i];
		return 0;
	}
};

bool solve (int k) {
	map<hsh, int> mp;
	int res = 0;
	int qt = 0;

	// YAN COMECA O FLUXO n*n por n
	f::reset_all();
	for(int i = 0; i < n; i++)
		f::add_edge(M - 1, i, 1);
	for(int i = 0; i < n * n; i++)
		f::add_edge(202 + i, M - 2, 1);

	for (int i = 0; i < n; i++) {
		set<hsh> s;

		hsh h;
		int kk = min(k, int(str[i].size() / 2));
		for (int j = 0; j < kk; j++)
			h.add(str[i][j]);
		s.insert(h);

		for (int j = kk; j < str[i].size() && s.size() <= n; j++) {
			h.sub(str[i][j-kk], str[i][j]);
			s.insert(h);
		}

		if (s.size() > n)
			res++;
		else {
			for (hsh x : s) {
				int id = mp[x] - 1;
				if (id == -1) {
					mp[x] = ++qt;
					id = qt - 1;
				}

				// YAN conecta o i-ésimo da esquerda com o id-ésimo da direita
				f::add_edge(i, 202 + id, 1);
			}
		}
	}

	// YAN res += valor do fluxo
	res += f::max_flow(M - 1, M - 2);
	return (res == n);
}

int main () {
	cin.sync_with_stdio(0);

	cin >> n;
	int hi = 1;
	for (int i = 0; i < n; i++) {
		cin >> str[i];
		str[i] = (str[i] + str[i]);
		hi = max(hi, int(str[i].size()));
	}

	int lo = 1;
	while (lo < hi) {
		int mid = (lo + hi)/2;

		if (solve(mid))
			hi = mid;
		else
			lo = mid+1;
	}

	printf("%d\n", lo);
}
