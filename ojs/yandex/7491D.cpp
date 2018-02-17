#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<ll, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 312345;
ll a[N];

int main() {
	int n, q, l, r, i;
	scanf("%d %d", &n, &q);
	for(i = 0; i < n; i++)
		scanf("%lld", &a[i]);
	while(q--) {
		scanf("%d %d", &l, &r); l--; r--;
		if(r - l + 1 < 3) { puts("-1"); continue; }
		r = min(r, l + 90);
		vector<pii> v;
		for(i = l; i <= r; i++) v.pb(pii(a[i], i + 1));
		sort(v.begin(), v.end());
		for(i = 0; i + 2 < v.size(); i++)
			if(v[i].fst + v[i + 1].fst > v[i + 2].fst) {
				printf("%d %d %d\n", v[i].snd, v[i + 1].snd, v[i + 2].snd);
				break;
			}
		if(i + 2 >= v.size()) puts("-1");
	}

}
