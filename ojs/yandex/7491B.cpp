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

vector<int> a[1123];

int main() {
	int i, j, n;
	scanf("%d", &n);
	for(i = 0; i < 2 * n; i++) {
		a[i].resize(n);
		for(j = 0; j < n; j++)
			scanf("%d", &a[i][j]);
	}
	map<int, int> mp;
	for(i = 0; i < n; i++) mp[a[0][i]] = i;
	vector<pair<int, vector<int>>> vs;
	for(i = 1; i < 2 * n; i++) {
		for(j = 0; j < n && !mp.count(a[i][j]); j++);
		if(j < n) vs.pb({mp[a[i][j]], a[i]});
	}
	sort(vs.begin(), vs.end());
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			printf("%d ", vs[i].snd[j]);
	putchar('\n');
}
