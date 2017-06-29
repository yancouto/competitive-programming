#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 1e6;

int n, m;
int ee[N][2];
int hd[N], to[N], nx[N], es;
int mrk[N];
int dpt[N];
int vs[N];
set<int> s[N];

int dfs (int u, int v) {
	vs[u] = 1;
	dpt[u] = dpt[v]+1;

	for (int ed = hd[u]; ed; ed = nx[ed]) {
		int w = to[ed];
		if (w == v) continue;

		if (vs[w] == 0) {
			dfs(w, u);

			if (s[w].size())
				mrk[ed|1] = 1;

			if (s[u].size() < s[w].size())
				swap(s[u], s[w]);
			while (s[w].size()) {
				s[u].insert(*s[w].begin());
				s[w].erase(s[w].begin());
			}
		}
	}

	s[u].erase(u);

	for (int ed = hd[u]; ed; ed = nx[ed]) {
		int w = to[ed];
		if (w == v) continue;
		if (vs[w] != 1) continue;

		if ((dpt[u] - dpt[w])%2 == 0) {
			mrk[ed|1] = 1;
			s[u].insert(w);
		}
	}

	int rr = s[u].size();
	for (int ed = hd[u]; ed; ed = nx[ed]) {
		int w = to[ed];
		if (w == v) continue;
		if (vs[w] != 1) continue;

		if (rr && (dpt[u] - dpt[w])%2) {
			mrk[ed|1] = 1;
			s[u].insert(w);
		}
	}

	vs[u] = 2;
}

ll qt[2];
int c[N];
ll res[2];
void go (int u, int cr) {
	if (c[u] != -1) {
		assert(c[u] == cr);
		return;
	}
	c[u] = cr;
	qt[cr]++;

	for (int ed = hd[u]; ed; ed = nx[ed]) {
		if (mrk[ed|1]) continue;
		go(to[ed], !cr);
	}
}

int main () {
	memset(c, -1, sizeof c);
	cin >> n >> m;

	es = 2;
	for (int i = 0; i < m; i++) {
		cin >> ee[i][0] >> ee[i][1];
		ee[i][0]--; ee[i][1]--;

		nx[es] = hd[ee[i][0]]; to[es] = ee[i][1]; hd[ee[i][0]] = es++;
		nx[es] = hd[ee[i][1]]; to[es] = ee[i][0]; hd[ee[i][1]] = es++;
	}

	dfs(0,0);

	for (int i = 0; i < n; i++) {
		qt[0] = qt[1] = 0;
		go(i, !!c[i]);
		//cout << i << ": " << qt[0] << " " << qt[1] << endl;

		res[0] += (qt[0])*(qt[0]-1)/2 + (qt[1])*(qt[1]-1)/2;
		res[1] += qt[0]*qt[1];
	}

	cout << res[0] << " " << res[1] << endl;
}
