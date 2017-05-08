#include <bits/stdc++.h>
using namespace std;

const int M = (212 * 212 + 212) * 3;

int tempo, seen[M];

int fl[M], nx[M], he[M], to[M], en = 2;

bool dfs(int s, int t) {
	seen[s] = tempo;
	if(t == s) return true;
	for(int e = he[s]; e != -1; e = nx[e])
		if((e & 1) - fl[e] && seen[to[e]] != tempo && dfs(to[e], t)) {
			fl[e]++;
			fl[e ^ 1]--;
			return true;
		}
	return false;
}

inline int max_flow(int s, int t) {
	int f = 0; tempo++;
	while(dfs(s, t)) f++, tempo++;
	return f;
}

void add_edge(int a, int b, int cp) {
	nx[en] = he[b]; fl[en] = 0; to[en] = a; he[b] = en++;
	nx[en] = he[a]; fl[en] = 0; to[en] = b; he[a] = en++;
}

void start() {
	memset(he, -1, sizeof he);
}

typedef long long ll;
typedef pair<ll,ll> pii;

const ll B[2] = {263, 301};
const ll MOD[2] = {1000000007, 1000000009};

const int N = 203;

string str[N];
int n;

struct hsh {
	ll v[2], n, pot[2];

	hsh () {
		v[0] = v[1] = n = 0;
		pot[0] = pot[1] = 1;
	}

	void add (ll c) {
		for (int i = 0; i < 2; i++) {
			v[i] = (v[i]*B[i]+c)%MOD[i];
			//v[i] = (v[i] + c)%MOD[i];
			pot[i] = (pot[i]*B[i])%MOD[i];
		}
		n++;
	}

	void sub (ll c, ll d) {
		for (int i = 0; i < 2; i++) {
			v[i] = (v[i]*B[i])%MOD[i];
			v[i] = (v[i] - ((c*pot[i])%MOD[i])+MOD[i]+d)%MOD[i];
			//v[i] = (v[i] + MOD[i]+d)%MOD[i];
			//v[i] = (v[i] + d)%MOD[i];
		}
	}

	bool operator < (const hsh & ot) const {
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
	start();
	for(int i = 0; i < n; i++)
		add_edge(M - 1, i, 1);
	for(int i = 0; i < n * n; i++)
		add_edge(202 + i, M - 2, 1);

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
				add_edge(i, 202 + id, 1);
			}
		}
	}

	// YAN res += valor do fluxo
	res += max_flow(M - 1, M - 2);
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
