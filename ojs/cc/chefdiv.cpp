#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<int, ll> pil;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#define left asdasd

ll a, b;
const int N = 1000000;
int dv[N];
deque<pli> ps[N];
ll left[N];

deque<pli> D;

unordered_map<ll, ll> mp;
ll solve(ll x) {
	if(x == 1) return 1;
	if(mp.count(x)) return mp[x];
	ll r = 0;
	ll ct = 1;
	for(int i = 0; i < (int) D.size(); i++) {
		pli p = D.front();
		if(p.snd == 0) continue;
		ll d = p.fst;
		ct *= p.snd + 1;
		p.snd--;
		D.pop_front();
		if(p.snd) D.pb(p);
		r = max(r, solve(x / d));
		if(!p.snd) D.pb(p);
		D.back().snd++;
	}
	r += 1 + (ct - 1);
	//printf("solve(%lld) = %lld\n", x, r);
	return mp[x] = r;
}

int main() {
	scanf("%lld %lld", &a, &b);
	for(ll j = a; j <= b; j++) left[j - a] = j;
	for(ll i = 2; i < N; i++)
		if(!dv[i]) {
			for(ll j = i * i; j < N; j += i)
				dv[j] = i;
			for(ll j = ll(b / i) * ll(i); j >= a; j -= i) {
				ll x = j; int C = 0;
				while(!(x % i)) x /= i, C++, left[j - a] /= i;
				ps[j - a].pb(pli(i, C));
			}
		}
	ll tot = 0;
	for(ll j = a; j <= b; j++) {
		if(left[j - a] != 1)
			ps[j - a].pb(pli(left[j - a], 1));
		D = ps[j - a];
		//tot += solve(j) - 1ll;
		priority_queue<pil> s;
		int ct = 1;
		for(pli p : D) s.push(pli(p.snd, p.fst)), ct *= p.snd + 1;
		ll ans = 0;
		while(!s.empty()) {
			pli p = s.top(); s.pop();
			ans += ct;
			ct /= p.fst + 1;
			ct *= p.fst;
			if(p.fst - 1) s.push(pli(p.fst - 1, p.snd));
		}
		tot += ans;
	}
	printf("%lld\n", tot);
}
