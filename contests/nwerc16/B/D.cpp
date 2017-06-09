#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;
#define fst first
#define snd second

const int N = 5123;
vector<pii> adj[N];
int en;
int d[N][N];

void go(vector<int> I) {
	if(I.size() < 2) return;
	int a = I[0], b = I[1];
	for(int i = 0; i < I.size(); i++)
		for(int j = i + 1; j < I.size(); j++)
			if(d[a][b] > d[I[i]][I[j]])
				a = I[i], b = I[j];
	vector<int> A, B;
	map<int, vector<int>> mid;
	for(int x : I) {
		if(x == a || x == b) continue;
		if(d[x][a] == d[x][b] + d[a][b]) B.pb(x);
		else if(d[x][b] == d[x][a] + d[a][b]) A.pb(x);
		else {
			int dd = d[x][a] - d[x][b] + d[a][b];
			assert(!(dd & 1));
			dd /= 2;
			mid[dd].pb(x);
		}
	}
	A.pb(a);
	go(A);
	int mx = 0, lst = a;
	for(auto &e : mid) {
		int u = en++;
		adj[lst].pb(pii(u, e.fst - mx));
		adj[u].pb(pii(lst, e.fst - mx));
		mx = e.fst;
		lst = u;
		for(int y : e.snd)
			d[y][u] = d[u][y] = d[a][y] - e.fst;
		e.snd.pb(u);
		go(e.snd);
	}
	adj[lst].pb(pii(b, d[a][b] - mx));
	adj[b].pb(pii(lst, d[a][b] - mx));
	B.pb(b);
	go(B);
}

typedef long double ld;
ll qt[N], sum[N];

ll car = 0; ld car2;
void dfs(int u, int p) {
	car++;
	//printf("dfs(%d, %d)\n", u, p);
	qt[u] = 1;
	sum[u] = 0;
	for(pii e : adj[u])
		if(e.fst != p) {
			car += (e.snd - 1);
			dfs(e.fst, u);
			ll d = e.snd;
			ll v = e.fst;
			qt[u] += qt[v] + d - 1ll;
			sum[u] += sum[v] + (qt[v] * d) + ((d - 1ll) * d) / 2ll;
		}
	//printf("u %d qt %lld sum %lld\n", u, qt[u], sum[u]);
}

ll S[N];
ld tot = 0;
void dfs2(int u, int p, ll c) {
	if(p == -1) {
		S[u] = sum[u];
		tot += S[u] / car2;
	} else {
		ll qB = qt[u], sB = sum[u];
		//printf("car %lld\n", car);
		ll qA = car - qt[u] - (c - 1), sA = S[p] - sum[u] - qt[u] * c - ((c - 1ll) * c) / 2ll;
		//printf("u %d p %d qA %lld sA %lld qB %lld sB %lld\n", u, p, qA, sA, qB, sB);
		S[u] = sB + sA + qA * c + ((c - 1ll) * c) / 2ll;
		ld SS = S[u] / car2;
		tot += SS + ld(c - 1ll) * SS + ld((c * (c - 1ll)) / 2ll) * ld((qB - qA - c) / car2) + (ld(((c - 1ll) * c * (2ll * c - 1ll)) / 6ll) / car2);
	}
	//printf("S[%d] = %lld\n", u, S[u]);
	for(pii e : adj[u])
		if(e.fst != p)
			dfs2(e.fst, u, e.snd);
}

int main() {
	int i, j, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++)
			scanf("%d", &d[i][j]), d[j][i] = d[i][j];
	for(i = 0; i < n; i++) d[i][i] = 1e8;
	vector<int> v;
	for(i = 0; i < n; i++) v.pb(i);
	en = n;
	go(v);
	//for(i = 0; i < en; i++)
	//	for(pii e : adj[i])
	//		printf("%d->%d: %d\n", i, e.fst, e.snd);
	dfs(0, -1);
	car2 = (car * (car - 1ll));
	dfs2(0, -1, -1);
	printf("%.20f\n", double(tot));
}
