#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

struct line {
	ll a, b;

	ll eval (ll x) {
		return a*x + b;
	}

	bool operator < (line & ot) {
		return a < ot.a;
	}
};

struct envelope {
	deque<line> qu;
	ll lo, hi;

	ll inter (line a, line b) {
		ll lo = this->lo; ll hi = this->hi + 1;
		while (hi - lo > 0) {
			ll md = lo + (hi - lo)/2;
			if (a.eval(md) <= b.eval(md))
				hi = md;
			else
				lo = md + 1;
		}

		return lo;
	}

	void push_back (line l) {
		if (!qu.empty() && qu.back().eval(hi) >= l.eval(hi))
			return;
		
		while (qu.size() > 1) {
			ll x = inter(qu.back(), l);
			if (qu[qu.size()-2].eval(x) >= qu[qu.size()-1].eval(x))
				qu.pop_back();
			else
				break;
		}

		qu.push_back(l);
	}

	line get (ll x) {
		int lo = 0, hi = qu.size() - 1;
		while (lo < hi) {
			int md = lo + (hi - lo)/2;
			if (qu[md].eval(x) >= qu[md+1].eval(x))
				hi = md;
			else
				lo = md+1;
		}

		return qu[lo];
	}
};

const int N = 2e3+7;

int n;
envelope env[N];
ll v[N];

int main () {
	scanf("%d", &n);

	ll res = 0;
	env[0].push_back(line({ 0, 0 }));
	env[0].lo = -2e6-2; env[0].hi = 2e6+2;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &v[i]);
		vector<line> lns;
		env[i].lo = -2e6-2; env[i].hi = 2e6+2;

		ll s = 0;
		for (int j = i; j > 0; j--) {
			s += v[j];
			ll loc = env[j-1].get(s).eval(s);
			lns.pb(line({ s, loc }));

			if (i == n)
				res = max(res, loc);
		}

		sort(lns.begin(), lns.end());
		for (line l : lns) {
			env[i].pb(l);
		}
	}

	printf("%lld\n", res);
}
