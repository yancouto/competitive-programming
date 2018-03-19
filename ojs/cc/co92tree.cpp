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
int seen[N], tempo;
const int K = 17;
ll best = 0;
int S[N], sz[N];

void go(int i) {
	if(seen[i] == tempo) return;
	seen[i] = tempo;
	S[i] = i;
	sz[i] = 1;
}

ll cur;

int find(int a) {
	if(S[S[a]] != S[a]) S[a] = find(S[a]);
	return S[a];
}

void join(int a, int b) {
	go(a); go(b);
	a = find(a); b = find(b);
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
	best = max(best, ll(sz[a]) * cur);
}

vector<int> ed[N];
int a[N], b[N];


int main() {
	int i, n, j;
	for_tests(tn, tt) {
		scanf("%d", &n);
		for(i = 0; i <= n; i++) ed[i].clear();
		for(i = 0; i < n - 1; i++) {
			scanf("%d %d", &a[i], &b[i]);
			ed[a[i] & b[i]].pb(i);
		}
		best = n;
		for(i = 1; i <= n; i++) {
			cur = i;
			tempo++;
			for(j = i; j <= n; j = ((j + 1) | i))
				for(int e : ed[j])
					join(a[e], b[e]);
		}
		printf("%lld\n", best);
	}
}
