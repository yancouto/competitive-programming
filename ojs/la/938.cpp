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

const int N = 112345;

int S[N], sz[N];
int find(int i) { return S[S[i]] == S[i]? S[i] : S[i] = find(S[i]); }
void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	S[b] = a;
	sz[a] += sz[b];
}

int dd[N], din[N], dout[N];

int he[N], nx[N], to[N], fl[N], cp[N], en = 2;

int seen[N], tempo;
int dfs(int s, int t, int f) {
	if(seen[s] == tempo) return 0;
	if(s == t) return f;
	seen[s] = tempo;
	for(int e = he[s]; e; e = nx[e])
		if(cp[e] - fl[e] > 0 && seen[to[e]] != tempo)
			if(int a = dfs(to[e], t, min(f, cp[e] - fl[e]))) {
				fl[e] += a;
				fl[e ^ 1] -= a;
				return a;
			}
	return 0;
}


int max_flow(int s, int t) {
	int f = 0;
	tempo++;
	while(int a = dfs(s, t, INT_MAX))
		f += a, tempo++;
	return f;
}

void add_edge(int a, int b, int c) {
	to[en] = b; fl[en] = 0; cp[en] = c; nx[en] = he[a]; he[a] = en++;
	to[en] = a; fl[en] = 0; cp[en] = 0; nx[en] = he[b]; he[b] = en++;
}

void reset(int n) {
	memset(he, 0, (sizeof(int) * n));
	en = 2;
}

int main() {
	int i, n, m, a, b, c;
	for_tests(tn, tt) {
		scanf("%d %d", &n, &m);
		for(i = 0; i < n; i++) dd[i] = din[i] = dout[i] = 0, S[i] = i, sz[i] = 1;
		reset(n + m + 2);
		for(i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &c); a--; b--;
			if(c == 1) dout[a]++, din[b]++;
			else {
				add_edge(m + n, i, 1);
				add_edge(i, m + a, 1);
				add_edge(i, m + b, 1);
				dd[a]++; dd[b]++;
			}
			join(a, b);
		}
		if(sz[find(0)] != n) { puts("impossible"); continue; }
		int all = 0;
		for(i = 0; i < n; i++) {
			int dmx = max(din[i], dout[i]), dmn = min(din[i], dout[i]);
			if(abs(din[i] - dout[i]) > dd[i]) { puts("impossible"); break; }
			int need = 0;
			if(dout[i] > din[i]) need = dout[i] - din[i];
			if((dd[i] - abs(dout[i] - din[i])) & 1) { puts("impossible"); break; }
			need += (dd[i] - abs(dout[i] - din[i])) / 2;
			if(need) add_edge(m + i, m + n + 1, need);
			all += need;
		}
		if(i < n) continue;
		if(max_flow(m + n, m + n + 1) != all) puts("impossible");
		else puts("possible");
	}
}
