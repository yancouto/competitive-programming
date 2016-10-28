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
const int N = 11234;
int S[N], sz[N], ct[N];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	S[b] = a;
	sz[a] += sz[b];
	ct[a] += ct[b];
}

int main() {
	int i, n, m, r, e, a, b;
	while(scanf("%d %d %d %d", &n, &m, &r, &e) != EOF) {
		for(i = 0; i < n; i++) S[i] = i, sz[i] = 1, ct[i] = 0;
		for(i = 0; i < m; i++) {
			scanf("%d %d", &a, &b); a--; b--;
			join(a, b);
			ct[find(a)]++;
		}
		int ans = 0;
		for(i = 0; i < n; i++) {
			if(S[i] != i) continue;
			int all = (sz[i] * (sz[i] - 1)) / 2;
			ans += min((all - ct[i]) * r, e * sz[i]);
		}
		printf("%d\n", ans);
	}
}
