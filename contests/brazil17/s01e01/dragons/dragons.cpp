#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;
#define s first
#define g second
const int N = 1123;

int S[N], sz[N];

int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

vector<int> all[N];


inline void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	S[b] = a;
	sz[a] += sz[b];
	for(int x : all[b]) all[a].pb(x);
}

vector<pii> dgs[N];

int main() {
	int i, j, n, f, d, a, b, s, g;
	scanf("%d %d %d", &n, &f, &d);
	for(i = 0; i < n; i++) S[i] = i, sz[i] = 1, all[i].pb(i);
	for(i = 0; i < f; i++) {
		scanf("%d %d", &a, &b);
		join(a, b);
	}
	for(i = 0; i < d; i++) {
		scanf("%d %d %d", &j, &s, &g);
		dgs[j].pb(pii(s, g));
	}
	ll ans = 0;
	for(i = 0; i < n; i++) {
		if(find(i) != i) continue;
		vector<pii> D;
		ll sum = 0;
		for(int x : all[i])
			for(pii dg : dgs[x])
				D.pb(dg), sum += dg.s;
		if(D.empty()) continue;
		sort(D.begin(), D.end(), [](pii a, pii b) { return a.g > b.g; });
		ll best = min<ll>(sum, D.front().g + 1);
		sum = 0;
		for(j = 0; j < int(D.size()) - 1; j++) {
			sum += D[j].s;
			best = min<ll>(best, max<ll>(sum, D[j + 1].g + 1));
		}
		ans += best;
	}
	printf("%lld\n", ans);
}
