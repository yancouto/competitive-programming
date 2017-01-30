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
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

int n;

struct num {
	map<int, int> mp;

	void div(const num &o) {
		for(auto e : o.mp)
			mp[e.fst] -= e.snd;
	}
	void mult(const num &o) {
		for(auto e : o.mp)
			mp[e.fst] += e.snd;
	}
	ll eval() {
		ll x = 1;
		for(auto e : mp) {
			assert(e.snd >= 0);
			while(e.snd--) x *= e.fst;
		}
		return x;
	}
};

num nms[40];
set<ll> s;
int d, h;
void gen(vector<int> pos, int sum) {
	if(pos.size() == d) {
		if(sum) return;
		num x;
		for(int i = 2; i <= h-1; i++) x.mult(nms[i]);
		for(int y : pos)
			for(int i = 2; i <= y; i++)
				x.div(nms[i]);
		s.insert(x.eval());
		return;
	}
	int mx = pos.empty()? sum : pos.back();
	for(int i = 0; i <= sum && i <= mx; i++) {
		vector<int> p = pos;
		p.pb(i);
		gen(p, sum - i);
	}
}


int main() {
	int i, j;
	for(i = 2; i <= 35; i++) {
		int x = i;
		for(j = 2; x > 1; j++)
			while((x % j) == 0)
				nms[i].mp[j]++, x /= j;
	}
	scanf("%d %d", &d, &h);
	gen(vector<int>(), h - 1);
	for(ll x : s) printf("%lld\n", x);
}

