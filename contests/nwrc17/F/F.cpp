#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 112345;

inline int v0(int i) { return 2 * i; }
inline int v1(int i) { return v0(i) + 1; }

inline int UD(int i) { return i * 2; }
inline int LR(int i) { return UD(i) + 1; }

vector<int> adj[N];
#define pb push_back

int seen[N];
int d[N], low[N], st[N], sn, tempo = 1, C[N], cn = 1;

void dfs(int u) {
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	st[sn++] = u;
	for(int v : adj[u])
		if(seen[v])
			low[u] = min(low[u], d[v]);
		else {
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
	if(low[u] == d[u]) {
		cn++;
		int a = -1;
		while(a != u) {
			a = st[--sn];
			C[a] = cn;
			if(C[a ^ 1] == cn) { puts("NO"); exit(0); }
			d[a] = low[a] = INT_MAX;
		}
	}
}

void add_or(int a, int b) {
	adj[a ^ 1].pb(b);
	adj[b ^ 1].pb(a);
}


int r[1123], c[1123];
int main () {
	int i, j, R, n;
	scanf("%*d %d %d", &R, &n);
	for(i = 0; i < n; i++) {
		scanf("%d %d", &r[i], &c[i]);
		add_or(v0(UD(i)), v0(LR(i)));
		add_or(v1(UD(i)), v1(LR(i)));
	}
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++) {
			if(r[i] == r[j] && abs(c[i] - c[j]) <= 2 * R)
				add_or(v0(LR(i)), v0(LR(j)));
			if(c[i] == c[j] && abs(r[i] - r[j]) <= 2 * R)
				add_or(v0(UD(i)), v0(UD(j)));
		}
	for(i = 0; i < N; i++)
		if(!seen[i])
			dfs(i);
	puts("YES");
}
