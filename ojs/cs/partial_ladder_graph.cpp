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

//int S[1123], sz[1123];
//int find(int i) {
//	if(S[S[i]] != S[i]) S[i] = find(S[i]);
//	return S[i];
//}
//void join(int a, int b) {
//	if((a = find(a)) == (b = find(b))) return;
//	if(sz[a] < sz[b]) swap(a, b);
//	sz[a] += sz[b];
//	S[b] = a;
//}
//
//int main() {
//	vector<pii> adj;
//	int i, j, n;
//	scanf("%d", &n);
//	for(i = 0; i < n - 1; i++)
//		adj.pb(pii(i, i + 1)), adj.pb(pii(n + i, n + i + 1));
//	for(i = 0; i < n; i++)
//		adj.pb(pii(i, n + i));
//	int ct = 0;
//	for(j = 0; j < (1 << adj.size()); j++) {
//		for(i = 0; i < 2*n; i++) S[i] = i, sz[i] = 1;
//		for(i = 0; i < adj.size(); i++)
//			if((j >> i) & 1)
//				join(adj[i].fst, adj[i].snd);
//		ct += (sz[find(0)] == 2*n);
//	}
//	printf("%d\n", ct);
//}

int mult(ll a[2][2], ll b[2][2], ll c[2][2]) {
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++)
			c[i][j] = mod(a[i][0] * b[0][j] + a[i][1] * b[1][j]);
}

void cp(ll a[2][2], ll b[2][2]) {
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++)
			b[i][j] = a[i][j];
}

ll M[2][2] = {{3, 1}, {4, 2}};
ll r[2][2] = {{1, 0}, {0, 1}};
ll a[2][2];

void fexp(ll n) {
	for(; n; n >>= 1) {
		if(n & 1) { mult(M, r, a); cp(a, r); }
		mult(M, M, a);
		cp(a, M);
	}
}


int main() {
	ll n;
	scanf("%lld", &n);
	fexp(n-1);
	printf("%d\n", (int) mod(r[0][0] + r[0][1] * 2ll));
}
