#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 50000;

int he[N], nx[N], cp[N], fl[N], to[N], en;
int seen[N], tempo;
bool dfs(int u, int t) {
	if(u == t) return true;
	if(seen[u] == tempo) return false;
	seen[u] = tempo;
	for(int e = he[u]; e != -1; e = nx[e])
		if(cp[e] - fl[e] && dfs(to[e], t)) {
			fl[e]++;
			fl[e ^ 1]--;
			return true;
		}
	return false;
}

int max_flow(int s, int t) {
	int f = 0; tempo++;
	while(dfs(s, t)) f++, tempo++;
	return f;
}

void add_edge(int a, int b) {
	fl[en] = 0; cp[en] = 1; to[en] = b; nx[en] = he[a]; he[a] = en++;
	fl[en] = 0; cp[en] = 0; to[en] = a; nx[en] = he[b]; he[b] = en++;
}

int a[N], b[N], c[N];
pii m[N], M[N], k[N], K[N];

int gcd(int a, int b) {
	if(b == 0) return a;
	return gcd(b, a % b);
}

int sign(int a) { return (a > 0) - (a < 0); }


int main() {
	int i, n;
	for_tests(t, tt) {
		en = 0;
		scanf("%d", &n);
		int hasA0 = 0, hasA00 = 0, ans = 0, ax;
		for(i = 0; i < n; i++) {
			he[2*i] = he[2*i+1] = -1;
			scanf("%d %d %d", &a[i], &b[i], &c[i]);
			swap(a[i], b[i]);
			if(a[i] == 0) hasA0++;
			if(a[i] == 0 && c[i] != 0) ax = i;
			if(a[i] == 0 && c[i] == 0) hasA00++;
		}
		he[N - 1] = he[N - 2] = -1;
		if(hasA00 == n) { printf("1\n1\n"); continue; }
		if(hasA0 > hasA00) ans++;
		int kn = 0;
		for(i = 0; i < n; i++) {
			if(a[i] == 0) continue;
			kn++;
			int sa = sign(a[i]), sb = sign(b[i]), sc = sign(c[i]);
			a[i] = abs(a[i]); b[i] = abs(b[i]); c[i] = abs(c[i]);
			m[i] = pii(b[i] / gcd(b[i], a[i]), a[i] / gcd(b[i], a[i]));
			if(sb * sa == -1) m[i].fst = -m[i].fst;
			M[i] = m[i];
			k[i] = pii(c[i] / gcd(c[i], a[i]), a[i] / gcd(c[i], a[i]));
			if(sc * sa == -1) k[i].fst = -k[i].fst;
			K[i] = k[i];
		}
		sort(M, M + kn);
		sort(K, K + kn);
		for(i = 0; i < n; i++) {
			if(a[i] == 0) { fl[en] = fl[en + 1] = 0; en += 2; continue; }
			add_edge(lower_bound(M, M + kn, m[i]) - M, lower_bound(K, K + kn, k[i]) - K + n);
		}
		for(i = 0; i < n; i++)
			add_edge(N - 2, i);
		for(i = 0; i < n; i++)
			add_edge(i + n, N - 1);
		printf("%d\n", max_flow(N - 2, N - 1) + ans);
		for(i = 0; i < n; i++)
			if(fl[2 * i])
				printf("%d ", i + 1);
		if(ans) printf("%d", ax + 1);
		putchar('\n');
	}
}
