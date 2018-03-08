#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

struct el {
	int i, j;
};

struct rect {
	int par;
	el tl, br;
	bool operator < (rect o) const {
		return tl.j > o.tl.j;
	}
};

const int N = 1123456;
struct seg_ {
	int tr[N], lz[N << 2];
	void unlaze(int i, int l, int r) {
		if(lz[i] == INT_MIN) return;
		if(l != r)
			lz[2 * i] = lz[2 * i + 1] = lz[i];
		else
			tr[l] = lz[i];
		lz[i] = INT_MIN;
	}
	void set(int i, int l, int r, int ql, int qr, int x) {
		//if(i == 1) printf("set (%d, %d) = %d\n", ql, qr, x);
		unlaze(i, l, r);
		if(l > qr || r < ql) return;
		if(l >= ql && r <= qr) {
			lz[i] = x;
			unlaze(i, l, r);
			return;
		}
		int m = (l + r) / 2;
		set(2 * i, l, m, ql, qr, x);
		set(2 * i + 1, m + 1, r, ql, qr, x);
	}
	int get(int i, int l, int r, int p) {
		unlaze(i, l, r);
		//if(l == r) printf("get(%d) = %d\n", p, tr[l]);
		if(l == r) return tr[l];
		int m = (l + r) / 2;
		if(p <= m) return get(2 * i, l, m, p);
		else return get(2 * i + 1, m + 1, r, p);
	}
};

const int M = 212345;
rect rs[N];

struct segp {
	int tr[M * 4 * 19], L[M * 19 * 4], R[M * 19 * 4], root[M], m, en;
	vector<int> ord, cns;
	int build(int l, int r) {
		assert(en < M * 4 * 19);
		int i = en++;
		tr[i] = 0;
		if(l == r) return i;
		int m = (l + r) / 2;
		L[i] = build(l, m);
		R[i] = build(m + 1, r);
		return i;
	}
	int set1(int oi, int l, int r, int p) {
		assert(en < M * 4 * 19);
		int i = en++; L[i] = L[oi]; R[i] = R[oi];
		tr[i] = tr[oi] + 1;
		if(l == r) return i;
		int m = (l + r) / 2;
		if(p <= m) L[i] = set1(L[i], l, m, p);
		else R[i] = set1(R[i], m + 1, r, p);
		return i;
	}
	void build(vector<int> cns) {
		m = cns.size(); en = 0;
		if(!m) return;
		ord = cns;
		for(int i = 0; i < m; i++) cns[i] = i;
		sort(cns.begin(), cns.end(), [this](int i, int j) { return rs[ord[i]].tl.i > rs[ord[j]].tl.i; });
		this->cns = cns;
		root[0] = build(0, m - 1);
		for(int i = 0; i < m; i++)
			root[i + 1] = set1(root[i], 0, m - 1, cns[i]);
	}
	int get(int i, int l, int r, int ql, int qr) {
		if(rs[ord[l]].tl.j > qr || rs[ord[r]].tl.j < ql) return 0;
		if(rs[ord[l]].tl.j >= ql && rs[ord[r]].tl.j <= qr) return tr[i];
		int m = (l + r) / 2;
		return get(L[i], l, m, ql, qr) + get(R[i], m + 1, r, ql, qr);
	}
	int geq(int l, int r, int x) {
		if(!m) return 0;
		int j = lower_bound(cns.begin(), cns.end(), -1, [x, this](int i, int j) { assert(j == -1); return rs[ord[i]].tl.i > x - 1; }) - cns.begin();
		return get(root[j], 0, m - 1, l, r);
	}
};

segp coins;

int n, m, f;
seg_ seg;

void process_parents() {
	vector<tuple<int, int, int>> evs;
	for(int i = 0; i < n + m + f; i++)
		evs.pb(make_tuple(rs[i].tl.j, rs[i].tl.i, i)),
		evs.pb(make_tuple(rs[i].br.j + 1, -1, -i));
	sort(evs.begin(), evs.end());
	seg.set(1, 0, N - 1, 0, N - 1, -1);
	for(tuple<int, int, int> t : evs) {
		int i, j, id;
		tie(j, i, id) = t;
		//printf("\nprocessing %d\n", id);
		if(i == -1) {
			id = -id;
			seg.set(1, 0, N - 1, rs[id].tl.i, rs[id].br.i, rs[id].par);
		} else {
			rs[id].par = seg.get(1, 0, N - 1, i);
			seg.set(1, 0, N - 1, i, rs[id].br.i, id);
		}
	}
}

vector<int> le, lt;

vector<int> adj[N];
int tot[N];

void solve(int u) {
	vector<int> crs, cns;
	for(int v : adj[u]) {
		if(v < f) {
			solve(v);
			crs.pb(v);
			rs[n + m + f + v].tl = {rs[v].br.i + 1, rs[v].tl.j};
			crs.pb(n + m + f + v); // fake cow
		}
		else if(v < f + m) cns.pb(v);
		else crs.pb(v);
	}
	sort(cns.begin(), cns.end(), [](int i, int j) { return rs[i].tl.j < rs[j].tl.j; });
	sort(crs.begin(), crs.end(), [](int i, int j) { return rs[i] < rs[j]; });
	coins.build(cns);
	seg.set(1, 0, N - 1, 0, N - 1, u);
	//printf("\n\nsolve(%d)", u);
	//printf(" (%d coins)\n", int(cns.size()));
	for(int i : crs) {
		if(i < f) { // fence
			//printf("%d is fence\n", i);
			seg.set(1, 0, N - 1, rs[i].tl.i, rs[i].br.i, i);
		} else { // cow
			tot[i] = coins.geq(rs[i].tl.j, rs[u].br.j, rs[i].tl.i);
			//printf("%d is cow (%d, %d) ", i - 1, rs[i].tl.i, rs[i].tl.j);
			int j = seg.get(1, 0, N - 1, rs[i].tl.i);
			//printf("(nx %d) ", j);
			if(j == u) {
				int till = rs[u].br.j;
				le[i] = coins.geq(rs[i].tl.j, till, rs[i].tl.i);
				lt[i] = coins.geq(rs[i].tl.j, till, rs[i].tl.i + 1);
			} else {
				int till = rs[j].tl.j - 1;
				le[i] = coins.geq(rs[i].tl.j, till, rs[i].tl.i) + le[n + m + f + j];
				lt[i] = coins.geq(rs[i].tl.j, till - 1, rs[i].tl.i - 1) + coins.geq(till, till, rs[j].br.i + 2) + lt[n + m + f + j];
			}
			//printf("le %d lt %d\n", le[i], lt[i]);
		}
	}
}

void solve() {
	le.clear(); lt.clear();
	le.resize(N); lt.resize(N);
	for(int &x : le) x = 0;
	for(int &x : lt) x = 0;
	solve(f - 1);
}

inline void mirror() {
	for(int i = 0; i < n + m + f; i++) {
		swap(rs[i].tl.i, rs[i].tl.j);
		swap(rs[i].br.i, rs[i].br.j);
	}
}

int main() {
	int i;
	while(scanf("%d", &f) != EOF) {
		for(i = 0; i < f; i++)
			scanf("%d %d %d %d", &rs[i].tl.i, &rs[i].tl.j, &rs[i].br.i, &rs[i].br.j);
		rs[f].tl = {0, 0};
		rs[f].br = {1000001, 1000001};
		f++;
		scanf("%d", &m);
		for(i = 0; i < m; i++) {
			scanf("%d %d", &rs[i + f].tl.i, &rs[i + f].tl.j);
			rs[i + f].br = rs[i + f].tl;
		}
		scanf("%d", &n);
		for(i = 0; i < n; i++) {
			scanf("%d %d", &rs[i + f + m].tl.i, &rs[i + f + m].tl.j);
			rs[i + f + m].br = rs[i + f + m].tl;
		}
		process_parents();
		for(i = 0; i < n + m + f; i++) adj[i].clear();
		for(i = 0; i < n + m + f; i++)
			if(i != f - 1)
				adj[rs[i].par].pb(i);
		solve();
		//for(i = f + m; i < n + m + f; i++)
		//	printf("[%d] le %d lt %d\n", i - 1, le[i], lt[i]);
		vector<int> up = le;
		mirror();
		solve();
		//for(i = f + m; i < n + m + f; i++)
		//	printf("[%d] le %d lt %d\n", i - 1, le[i], lt[i]);
		vector<int> right = le;
		for(i = 0; i < n; i++)
			printf("%d\n", up[i + f + m] + right[i + f + m] - tot[i + f + m]);
	}
}
