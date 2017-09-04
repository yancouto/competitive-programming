#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; cin >> t; for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int a[200];
ll memo[100][200][200];
int seen[100][200][200], tempo;
int n;
ll solve(int i, int si, int si1) {
	int ai = a[i] + si;
	int ai1 = a[i + 1] + si1;
	if(i >= n && !ai && !ai1) return 1;
	ll &r = memo[i][si + 100][si1 + 100];
	if(seen[i][si + 100][si1 + 100] == tempo) return r;
	seen[i][si + 100][si1 + 100] = tempo;
	r = 0;
	for(int g = 0; g <= min(ai, ai1); g++)
		r += solve(i + 1, si1 - g, g);
	return r = mod(r);
}

int main() {
	int i;
	ios::sync_with_stdio(0); cin.tie(0);
	for_tests(tn, tt) {
		cin >> n;
		for(i = 0; i < n; i++)
			cin >> a[i];
		for(i = n; i <= 100; i++) a[i] = 0;
		tempo++;
		cout << solve(0, 0, 0) << endl;
	}
}
