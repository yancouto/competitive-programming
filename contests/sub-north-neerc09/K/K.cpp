#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 11234;
int c[N], oky[N];
vector<int> adj[N], rev[N];
int A[N][26];

int okx[N];
char x, y;

void go(int u) {
	if(oky[u] == 0) return;
	oky[u] = 0;
	for(int v : rev[u])
		go(v);
}

void go2(int u) {
	if(okx[u]) return;
	okx[u] = 1;
	for(int v : rev[u])
		if(A[v][x - 'a'])
			go2(v);
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("kripke.in", "r", stdin);
	freopen("kripke.out", "w", stdout);
#endif
	int n, m, k, a, b, i, j;
	scanf("%d %d %d", &n, &m, &k);
	for(i = 0; i < n; i++) {
		scanf("%d", &c[i]);
		for(j = 0; j < c[i]; j++) {
			scanf(" %c", &x);
			A[i][x - 'a'] = 1;
		}
		oky[i] = 1;
	}
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b);
		rev[b].pb(a);
	}
	scanf(" %*c %*c %c %*c %*c %*c %*c %c", &x, &y);
	for(i = 0; i < n; i++)
		if(A[i][y - 'a'] == 0)
			go(i);
	for(i = 0; i < n; i++)
		if(oky[i])
			go2(i);
	printf("%d\n", accumulate(okx, okx + n, 0));
	for(i = 0; i < n; i++)
		if(okx[i])
			printf("%d\n", i + 1);
}

