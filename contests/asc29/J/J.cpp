#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

#define pb push_back
#define fst first
#define snd second

const int N = 600;

vector<int> adj[N];
vector<int> nodes[N];
int compt[N];
int ns;

bool rm[N];
int to[N];
int n, m;
int pre[N], low[N], ord;
int vs[N], turn;

int outed[N];
bool inst[N];
stack<int> st;

int crt (int u) {
	if (vs[u] == turn)
		return pre[u];
	if (vs[u] == turn+1)
		return N;

	vs[u] = turn;
	pre[u] = low[u] = ord++;

	st.push(u);
	inst[u] = 1;

	for (int ed : adj[u]) {
		if (rm[ed]) continue;
		int v = to[ed];
		low[u] = min(low[u], crt(v));
	}

	vs[u] = turn+1;

	if (pre[u] == low[u]) {
		while (inst[u]) {
			int v = st.top();
			st.pop();
			inst[v] = 0;
			nodes[ns].pb(v);
			compt[v] = ns;
		}
		ns++;
	}

	return low[u];
}

void ident (int lvl) {
	return;
	for (int qt = 0; qt < lvl; qt++)
		printf("  ");
}

void go (int g, int lvl) {
	for (int u : nodes[g])
		compt[u] = -1;
	int init = ns;
	int cnt = 0;
	for (int u : nodes[g]) for (int i : adj[u]) {
		if (rm[i]) continue;
		cnt++;
		rm[i] = 1;
		
		ord = 0;
		turn += 2;

		crt(to[i]);

		// checa se a decomposicao e boa
		bool ok = 1;
		for (int j = ns - 1; ok && j >= init; j--) {
			int edg = -1;
			int sni = 0;
			for (int v : nodes[j]) {
				for (int ed : adj[v]) {
					if (ed == i)
						sni = 1;
					if (rm[ed]) continue;
					if (compt[to[ed]] == j)
						continue;
					if (edg != -1)
						ok = 0;
					edg = ed;
				}
			}

			if (j == init) {
				if (!sni)
					ok = 0;
				if (edg != -1)
					ok = 0;
				outed[j] = i;
			} else {
				if (sni)
					ok = 0;
				if (edg == -1)
					ok = 0;
				if (compt[to[edg]] != j - 1)
					ok = 0;
				outed[j] = edg;
			}
		}

		if (compt[to[i]] != ns - 1)
			ok = 0;

		if (ok) {
			for (int j = ns - 1; j >= init; j--)
				rm[outed[j]] = 1;

			ident(lvl);
			printf("wheel %d\n", ns - init);
			for (int j = ns - 1; j >= init; j--) {
				go(j,lvl+1);
				ident(lvl+1);
				printf("edge %d\n", outed[j] + 1);
			}
			return;
		} else {
			for (int j = ns - 1; j >= init; j--) {
				for (int v : nodes[j])
					compt[v] = -1;
				nodes[j].clear();
			}
			ns = init;
			rm[i] = 0;
		}
	}

	//assert(cnt == 0);
	ident(lvl);
	printf("vertex %d\n", nodes[g][0] + 1);
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("wheels.in", "r", stdin);
	freopen("wheels.out", "w", stdout);
#endif

	scanf("%d %d", &n, &m);

	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;

		adj[a].pb(i);
		to[i] = b;
	}

	for (int i = 0; i < n; i++)
		nodes[0].pb(i);

	ns = 1;
	go(0, 0);
}
