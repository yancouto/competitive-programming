#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;
typedef pair<ll, ll> pii;
#define pb push_back

vector<ll> ps;
int cp[10001];
map<ll, ll> mp;
ll fat[1123];
int freq[64];
vector<int> p;
vector<pii> all[10001];

int ct;

void mult(int x, int sign, bool d=false) {
	for(; x > 1; x--)
		for(pii p : all[x]) {
			freq[p.first] += p.second * sign;
		}
}

ll calc(bool d = false) {
	memset(freq, 0, sizeof freq);
	int tot = accumulate(p.begin(), p.end(), 0ll);
	mult(tot, 1, d);
	for(int x : p)
		mult(x, -1, d);
	ll cur = 1;
	for(ll i = 2; i < 64; i++) {
		while(freq[i]--) {
			if(cur > ULLONG_MAX / ll(i)) return ULLONG_MAX;
			cur = cur * ll(i);
		}
	}
	return cur;
}

void go(int pi, int mx, ll num) {
	if(mx == 0) {
		ll tm = calc(num == 12);
		if(num == 1 || tm == ULLONG_MAX) return;
		if(!mp.count(tm))
			mp[tm] = num;
		else
			mp[tm] = min(mp[tm], num);
		return;
	}
	for(int i = 0; i <= mx; i++) {
		p.pb(i);
		go(pi + 1, i, num);
		p.pop_back();
		if(num > ULLONG_MAX / ps[pi]) break;
		num *= ps[pi];
	}
}

int main() {
	int i, j;
	for(i = 2; i <= 10000; i++)
		if(!cp[i]) {
			ps.pb(i);
			for(j = i; j <= 10000; j += i) {
				cp[j] = 1;
				int ct = 0;
				int x = j;
				while(!(x % i)) x /= i, ct++;
				all[j].pb(pii(i, ct));
			}
		}
	fat[0] = 1;
	for(i = 1; i <= 1000; i++) fat[i] = fat[i - 1] * ll(i);
	go(0, 70, 1);
	ll n;
	while(scanf("%llu", &n) != EOF) {
		printf("%llu %llu\n", n, mp[n]);
	}
}
