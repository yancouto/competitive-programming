#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

template<class num> inline void rd(num &x) {
	scanf("%lld", &x);
}

ll n, m, k;
const int N = 2123456;
ll c[N], mrk[N];
deque<int> v[40];
ll al[50];

int main() {
	int i, j;
	rd(n); rd(m); rd(k);
	for(i = 0; i < n; i++) rd(c[i]);
	ll a, x;
	rd(a);
	for(i = 0; i < a; i++) { rd(x); mrk[--x] |= 1; }
	rd(a);
	for(i = 0; i < a; i++) { rd(x); mrk[--x] |= 2; }
	for(i = 0; i < n; i++) v[mrk[i]].pb(c[i]);
	for(i = 0; i < 4; i++) sort(v[i].begin(), v[i].end());
	priority_queue<int> pq;
	ll all = 0;
	for(int x : v[0]) pq.push(x), all += x;
	for(int t = 1; t <= 2; t++)
		for(int x : v[t])
			al[t] += x;
	i = 0;
	ll ans = LLONG_MAX;
	ll al3 = 0;
	while(true) {
		for(int t = 1; t <= 2; t++)
			while(!v[t].empty() && v[t].size() + i > k) {
				all += v[t].back();
				pq.push(v[t].back());
				al[t] -= v[t].back();
				v[t].pop_back();
			}
		while(!pq.empty() && int(pq.size()) + i + int(v[1].size()) + int(v[2].size()) > m) {
			all -= pq.top();
			pq.pop();
		}
		if(v[1].size() + i >= k && v[2].size() + i >= k && pq.size() + i + v[1].size() + v[2].size() == m) ans = min(ans, all + al[1] + al[2] + al3);
		if(i == v[3].size() || i == m) break;
		al3 += v[3][i];
		i++;
	}
	if(ans == LLONG_MAX) puts("-1");
	else printf("%lld\n", ans);
}
