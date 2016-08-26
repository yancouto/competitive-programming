#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define lld I64d
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

ll cur, tot;
const int N = 1123;
int S[N*N], sz[N*N], ed[N*N];
int g[N][N]; pii p[N*N];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(ed[a] < ed[b]) swap(a, b);
	S[b] = a;
	sz[a] += sz[b];
	if(!ed[b] && ed[a]) cur -= sz[b];
}

int di[4] = {1, -1, 0, 0};
int dj[4] = {0, 0, -1, 1};
int on[N*N];

int main() {
	int i, j, n, m, pn = 0, k, d;
	scanf("%d %d", &n, &m);
	for(i = 0; i <= n + 1; i++)
		for(j = 0; j <= m + 1; j++) {
			int id = i * 600 + j;
			S[id] = id; sz[id] = 1;
			if(i && j && i < n + 1 && j < m + 1) {
				scanf("%d", &g[i][j]);
				p[pn++] = pii(i, j);
			} else {
				on[id] = ed[id] = 1;
				join(id, 0);
			}
		}
	sort(p, p + pn, [](pii a, pii b) { return g[a.fst][a.snd]  < g[b.fst][b.snd]; });
	for(k = 0; k < pn; k++) {
		i = p[k].fst, j = p[k].snd;
		int id = i * 600 + j;
		cur++;
		on[id] = 1;
		for(d = 0; d < 4; d++) {
			int ni = i + di[d], nj = j + dj[d];
			if(!on[ni*600 + nj]) continue;
			join(id, ni * 600 + nj);
		}
		if(k+1 < pn) tot += cur * ll(g[p[k+1].fst][p[k+1].snd] - g[p[k].fst][p[k].snd]);
	}
	printf("%lld\n", tot);
}
