#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
typedef long long int ll;

const int N = 1e5+7;

int n, m;
int a, b;
bool inv[N], sel[N];
vector<int> adj[N];
int qt, deg[N];
set<pii> s;

int main () {
	scanf("%d %d %d %d", &n, &m, &a, &b);

	qt = n;

	for (int i = 0; i < m; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		x--; y--;

		adj[x].push_back(y);
		adj[y].push_back(x);
	}

	for (int i = 0; i < n; i++) {
		deg[i] = adj[i].size();
		s.insert(pii(deg[i], i));
	}

	bool turn = 0;
	int rnd = 0;
	while (rnd < 3 && !s.empty()) {
		turn = !turn;
		int u;
		if (turn)
			u = s.begin()->second;
		else
			u = s.rbegin()->second;


		if (deg[u] >= a && qt - deg[u] - 1 >= b) {
			rnd++;
			continue;
		}

		rnd = 0;
		s.erase(pii(deg[u], u));
		inv[u] = 1;
		qt--;
		for (int i : adj[u]) {
			if (inv[i]) continue;
			s.erase(pii(deg[i], i));
			deg[i]--;
			s.insert(pii(deg[i], i));
		}
	}

	printf("%d\n", qt);
}
