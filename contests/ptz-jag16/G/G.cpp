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

const int N = 4e6+16;

int m;

struct vert {
	int p[3];
	int id;
	bool rm;

	bool operator < (const vert & ot) const {
		for (int j = 0; j < 3; j++)
			if (p[j] != ot.p[j])
				return p[j] < ot.p[j];
		return 0;
	}
};

int n[3];
int q;
int uf[N], wf[N];
int qi, qf;
vert w[N];
set<vert> s;
int crit[3];

int find (int u) {
	if (u == uf[u]) return u;
	return uf[u] = find(uf[u]);
}

void join (int u, int v) {
	if ((v = find(v)) == (u = find(u))) return;
	if (wf[v] < wf[u]) swap(v, u);
	wf[v] += wf[u];
	uf[u] = v;
}

void expand (vert v) {
	for (int j = 0; j < 3; j++)
		if (v.p[j] < 0 || v.p[j] >= n[j])
			return;
	if (s.find(v) != s.end()) return;

	s.insert(v);
	v.id = m;
	w[m++] = v;


	for (int j = 0; j < 3; j++) {
		vert u = v;
		u.p[j] = 0;
		expand(u);

		u = v;
		u.p[j] = n[j]-1;
		expand(u);
	}
}

bool cmp_t (vert i, vert j) {
	for (int k = 0; k < 3; k++)
		if (i.p[crit[k]] != j.p[crit[k]])
			return i.p[crit[k]] < j.p[crit[k]];
	assert(false);
}

int main () {
	for (int i = 0; i < 3; i++)
		scanf("%d", &n[i]);
	m = 0;

	scanf("%d", &q);
	

	for (int i = 0; i < q; i++) {
		w[m].id = m;
		w[m].rm = 1;
		for (int j = 0; j < 3; j++) {
			scanf("%d", &w[m].p[j]);
		}
		s.insert(w[m]);
		m++;
	}

	for (int i = 0; i < q; i++) {
		vert v = w[i];
		vert u;
		u.rm = 0;
		
		for (u.p[0] = v.p[0]-1; u.p[0] <= v.p[0]+1; u.p[0]++)
			for (u.p[1] = v.p[1]-1; u.p[1] <= v.p[1]+1; u.p[1]++)
				for (u.p[2] = v.p[2]-1; u.p[2] <= v.p[2]+1; u.p[2]++)
					expand(u);
	}

	for (int i = 0; i < m; i++) {
		uf[i] = i;
		wf[i] = 1;
	}

	for (int j = 0; j < 3; j++)
		crit[j] = j;

	do {
		if (crit[0] > crit[1]) continue;
		sort(w, w+m, cmp_t);

		for (int i = 0; i < m-1; i++) {
			if (w[i].rm) continue;
			if (w[i+1].rm) continue;
			bool ok = 1;
			for (int j = 0; j < 2; j++)
				if (w[i].p[crit[j]] != w[i+1].p[crit[j]])
					ok = 0;
			if (!ok) continue;

			join(w[i].id, w[i+1].id);
		}
	} while (next_permutation(crit, crit+3));

	int res = 0;
	for (int i = 0; i < m; i++) {
		if (uf[w[i].id] == w[i].id) res++;
	}
	printf("%d\n", res-q);
}
