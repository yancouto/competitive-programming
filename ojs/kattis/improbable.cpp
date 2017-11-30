#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 51234;

int seen[N];
int he[N], nx[N], to[N], fl[N];
int en;
int tempo;

bool dfs(int s, int t) {
	if(s == t) return true;
	if(seen[s] == tempo) return false;
	seen[s] = tempo;
	for(int e = he[s]; e; e = nx[e])
		if((e & 1) - fl[e] && dfs(to[e], t)) {
			fl[e]++;
			fl[e ^ 1]--;
			return true;
		}
	return false;
}

int max_flow(int s, int t) {
	int f = 0;
	tempo++;
	while(dfs(s, t))
		f++, tempo++;
	return f;
}

int n;

void clear(vector<int> &r, vector<int> &c) {
	en = 2;
	for(int rr : r) he[rr] = 0;
	for(int cc : c) he[cc + n] = 0;
	he[N - 1] = he[N - 2] = 0;
}

void add_edge(int a, int b) {
	to[en] = a; fl[en] = 0; nx[en] = he[b]; he[b] = en++;
	to[en] = b; fl[en] = 0; nx[en] = he[a]; he[a] = en++;
}

int a[112][112];

ll solve(vector<int> rows, vector<int> cols) {
	clear(rows, cols);
	for(int r : rows)
		for(int c : cols)
			if(a[r][c] != 0) {
				//printf("(%d, %d) ok\n", r, c);
				add_edge(r, n + c);
			}
	for(int r : rows)
		add_edge(N - 1, r);
	for(int c : cols)
		add_edge(c + n, N - 2);
	int ret = max_flow(N - 1, N - 2);
	//printf("solve:\n");
	//for(int r : rows) printf("%d ", r); putchar('\n');
	//for(int r : cols) printf("%d ", r); putchar('\n');
	//printf("= %d\n", ret);
	return ret;
}

ll mxr[N], mxc[N];

int main() {
	int m, i, j;
	scanf("%d %d", &n, &m);
	ll sum = 0;
	int nz = 0;
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++) {
			scanf("%d", &a[i][j]);
			nz += !!a[i][j];
			sum += a[i][j];
			mxr[i] = max<ll>(mxr[i], a[i][j]);
			mxc[j] = max<ll>(mxc[j], a[i][j]);
		}
	ll left = accumulate(mxr, mxr + n, 0ll) + accumulate(mxc, mxc + m, 0ll);
	int lnz = 0;
	map<int, pair<vector<int>, vector<int>>> mp;
	for(i = 0; i < n; i++)
		mp[mxr[i]].fst.pb(i), lnz += !!mxr[i];
	for(j = 0; j < m; j++)
		mp[mxc[j]].snd.pb(j), lnz += !!mxc[j];
	for(auto &e : mp) {
		if(e.fst == 0) continue;
		ll f = solve(e.snd.fst, e.snd.snd);
		lnz -= f;
		left -= f * e.fst;
	}
	printf("%lld\n", sum - (left + (nz - lnz)));
}
