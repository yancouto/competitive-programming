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

const int N = 212, P = 509;

vector<int> adj[4*N];

ll mb[N][P];
int sb[N][P], val[N];
ll beg(int u, int t) {
	if(t == 0) return u? LLONG_MIN : 0;
	ll &r = mb[u][t];
	if(sb[u][t]) return r;
	sb[u][t] = 1;
	r = LLONG_MIN;
	for(int v : adj[u]) {
		r = max(r, beg(v, t - 1) + ll(val[u]));
		//if(u == 10) printf("%d->%d\n", u, v);
	}
	//printf("beg(%d, %d) = %lld [%d]\n", u, t, r, val[u]);
	return r;
}
int L, en = 1;

int tr[4*N][26], vx[4*N][26], f[4*N], a[N];
#define end asjasasdas
ll me[N][P];
int se[N][P];
ll end(int u, int t) {
	if(t == 0) return val[u];
	ll &r = me[u][t];
	if(se[u][t]) return r;
	se[u][t] = 1;
	r = LLONG_MIN;
	for(int i = 0; i < 26; i++)
		r = max(r, end(vx[u][i], t - 1) + ll(val[u]));
	return r;
}

ll memo[N][N][N];
int seen[N][N][N];
ll cyc(int u, int st, int t) {
	if(t == 0) return u == st? 0 : LLONG_MIN;
	ll &r = memo[u][st][t];
	if(seen[u][st][t]) return r;
	seen[u][st][t] = 1;
	r = LLONG_MIN;
	for(int i = 0; i < 26; i++)
		r = max(r, cyc(vx[u][i], st, t - 1) + ll(val[u]));
	return r;
}

void go() {
	int i, j, k;
	ll mx = LLONG_MIN;
	if(L < P) {
		printf("%lld\n", end(0, L));
		exit(0);
	}
	for(i = 0; i < en; i++)
		for(j = 0; j < P; j++) {
			if(beg(i, j) < 0) continue;
			for(k = 1; k < en && j + k <= L; k++) {
				ll c = cyc(i, i, k);
				if(c < 0) continue;
				ll left;
				if(k) left = (L - j) / k;
				else left = (L - j);
				ll ans = beg(i, j) + c * left + end(i, (L - ll(j)) - ll(k) * c);
				mx = max(mx, ans);
			}
		}
	printf("%lld\n", mx);
}

char s[N];
int main() {
	int i, j, n;
	scanf("%d %lld", &n, &L);
	for(i = 0; i < n; i++) scanf("%d", &a[i]);
	for(i = 0; i < n; i++) {
		scanf("%s", s);
		int v = 0;
		for(j = 0; s[j]; j++) {
			int &x = tr[v][s[j] - 'a'];
			if(!x) x = en++;
			v = x;
		}
		val[v] = a[i];
	}
	queue<int> q;
	for(i = 0; i < 26; i++)
		if(tr[0][i])
			q.push(tr[0][i]);
	vector<int> ord;
	ord.pb(0);
	while(!q.empty()) {
		int x = q.front(); q.pop();
		ord.pb(x);
		for(i = 0; i < 26; i++) {
			if(!tr[x][i]) continue;
			int v = tr[x][i];
			q.push(v);
			f[v] = f[x];
			while(f[v] && !tr[f[v]][i])
				f[v] = f[f[v]];
			if(tr[f[v]][i]) f[v] = tr[f[v]][i];
			//printf("val[%d] = %d\n", v, val[v]);
			val[v] += val[f[v]];
			//printf("val[%d] = %d\n", v, val[v]);
			//printf("%d->%d\n", v, f[v]);
		}
	}
	for(int i : ord)
		for(j = 0; j < 26; j++) {
			if(tr[i][j]) vx[i][j] = tr[i][j];
			else if(i) vx[i][j] = vx[f[i]][j];
			adj[vx[i][j]].pb(i);
		}
	go();
}
