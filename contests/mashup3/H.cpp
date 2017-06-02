#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;
#define div asd

vector<pii> F;
vector<ll> div;

int solve(ll);
int b;

void go(vector<pii> &F2, ll o, int &r, int i, ll val) {
	if(i == F2.size()) {
		r = min(r, 1 + solve(o / val));
		return;
	}
	assert(i < F2.size());
	for(int j = 0; j <= F2[i].second; j++) {
		go(F2, o, r, i + 1, val);
		val *= ll(F2[i].first);
		if(val >= b) return;
	}
}

unordered_map<ll, int> memo;
int solve(ll val) {
	if(memo.count(val)) return memo[val];
	int &r = memo[val];
	if(val < b) return r = 1;
	//printf("cal %lld\n", val);
	r = 1e8;
	ll n = val;
	vector<pii> F2;
	for(pii p : F) {
		if(n % p.first) continue;
		pii f(p.first, 0);
		while(!(n % p.first)) {
			f.second++;
			n /= p.first;
		}
		F2.pb(f);
	}
	go(F2, val, r, 0, 1);
	return r;
}

ll num = 0;
void build(ll val) {
	if(val < b) {
		num = num * b + val;
		printf("%lld\n", num);
		return;
	}
	ll r = solve(val);
	for(ll d : div) {
		if((val % d) == 0 && r == 1 + solve(val / d)) {
			num = num * b + d;
			build(val / d);
			return;
		}
	}
}

int main() {
	int i; ll n;
	scanf("%d %lld", &b, &n);
	ll on = n;
	for(i = 2; i < b; i++) {
		if(n % i) continue;
		pii f(i, 0);
		while(!(n % i)) {
			f.second++;
			n /= i;
		}
		F.pb(f);
	}
	if(n > 1) {
		puts("impossible");
		return 0;
	}
	ll ct = 1;
	for(pii p : F) ct *= (p.second + 1);
	for(int i = 2; i < b; i++)
		if(!(on % i))
			div.pb(i);
	int dig = solve(on);
	build(on);
}
