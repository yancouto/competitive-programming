#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 2e5+7;

int n; ll t[N], v[N];
ll dp[N];

bool domina (pii a, pii b) { return a.first <= b.first && a.second <= b.second; }

void apaga (multiset<ll> & r, pii a) { ll x = a.first + a.second; r.erase(r.find(x)); }
void add (set<pii> & s, multiset<ll> & r, pii v) {
	auto it = s.lower_bound(v);
	if (it != s.end() && domina(*it,v)) return;
	if (it != s.begin() && domina(*prev(it),v)) return;

	while (it != s.end() && domina(v,*it)) { it = next(it); apaga(r,*prev(it)); s.erase(prev(it)); }
	while (it != s.begin() && domina(v,*prev(it))) { apaga(r,*prev(it)); s.erase(prev(it)); }
	s.insert(v);
	r.insert(v.first + v.second);
}

int main () {
	while (scanf("%d", &n) != EOF) {
		set<pii> s;
		multiset<ll> r;
		
		add(s,r,pii(0,0));

		for (int i = 0; i < n; i++) {
			scanf("%lld %lld", &t[i], &v[i]);
			v[i] += v[i];

			vector<pii> cur;
			while (s.size() && s.begin()->first <= t[i]) {
				cur.pb(*s.begin());
				apaga(r, *s.begin());
				s.erase(s.begin());
			}
			while (s.size() && prev(s.end())->second <= v[i]) {
				cur.pb(*prev(s.end()));
				apaga(r, *prev(s.end()));
				s.erase(prev(s.end()));
			}

			for (pii q : cur) {
				q.first = max(q.first, t[i]);
				q.second = max(q.second, v[i]);
				add(s,r,q);
			}

			dp[i] = *r.begin();
			add(s,r,pii(dp[i],0));
		}
		

		printf("%lld\n", dp[n-1]);
	}
}
