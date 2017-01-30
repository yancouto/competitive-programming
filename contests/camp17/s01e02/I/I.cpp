#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const int modn = 13;
inline int mod(int x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;

const int N = 1123;

int a[N][N];
int ans[N];
int inv[1212];
int t;

// sum(a[i][j] * x_j) = a[i][n] para 0 <= i < n
void solve(int n) {
	for(int i = 0; i < n; i++) {
		int mx = i;
		for(int j = i + 1; j < t; j++)
			if((a[j][i]) > (a[mx][i]))
				mx = j;
		swap_ranges(a[i], a[i] + n + 1, a[mx]);
		assert(a[i][i]);
		for(int j = i + 1; j < t; j++) {
			for(int k = i + 1; k <= n; k++)
				a[j][k] = mod(a[j][k] - mod((a[j][i] * inv[a[i][i]]) * a[i][k]) + modn);
			a[j][i] = 0;
		}
	}
	for(int i = n - 1; i >= 0; i--) {
		ans[i] = a[i][n];
		for(int j = i + 1; j < n; j++)
			ans[i] = mod(ans[i] - mod(a[i][j] * ans[j]) + modn);
		ans[i] = mod(ans[i] * inv[a[i][i]]);
	}
}

map<pii, int> mp;
pii ed[1212];
int seen[2121];
int b[1212];
vector<pii> adj[1212];

int main() {
	int i, j;
	int n, al, r, p;
	scanf("%d %d %d %d", &n, &al, &r, &t);
	for(i = 1; i < 13; i++)
		for(j = 1; j < 13; j++)
			if(mod(i * j) == 1)
				inv[i] = j;
	int en = 0;
	for(i = 0; i < t; i++) {
		pii e;
		scanf("%d %d %d", &b[i], &p, &e.fst); p--;
		while(p--) {
			scanf("%d", &e.snd);
			if(!mp.count(e)) {
				//printf("%d->%d\n", e.fst, e.snd);
				mp[e] = mp[pii(e.snd, e.fst)] = en++;
				ed[mp[e]] = e;
			}
			a[i][mp[e]] = mod(a[i][mp[e]] + 1);
			swap(e.fst, e.snd);
		}
	}
	for(i = 0; i < t; i++)
		a[i][en] = b[i];
	//for(i = 0; i < t; i++)
	//	for(j = 0; j <= en; j++)
	//		printf("%d%c", a[i][j], " \n"[j == en]);
	solve(en);
	for(i = 0; i < en; i++) {
		pii e = ed[i];
		//printf("%d->%d : %d\n", e.fst, e.snd, ans[i]);
		assert(ans[i]);
		adj[e.fst].pb(pii(e.snd, ans[i]));
		adj[e.snd].pb(pii(e.fst, ans[i]));
	}
	priority_queue<pii> pq;
	pq.push(pii(0, al));
	while(true) {
		pii x = pq.top(); pq.pop();
		if(x.snd == r) { printf("%d\n", -x.fst); return 0; }
		if(seen[x.snd]) continue;
		seen[x.snd] = true;
		for(pii e : adj[x.snd])
			pq.push(pii(x.fst - e.snd, e.fst));
	}
}
