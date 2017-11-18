#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef long long ll;
typedef pair<ll, ll> pii;

struct brick {
	int x, y;
};

int n;
map<int,vector<brick> > mp;
set<pii> s;
ll res;
ll ls = 1e-9;

ll c2 (ll x) {
	return x*(x-1)/2;
}

void pull (ll y) {
	set<pii> ns;
	//cout << "at " << ls << endl;
	for (pii cur : s) {
		//cout << cur.first << " " << cur.second << endl;
		ll w = cur.second - cur.first + 1;
		res += c2(w+1);
		ll dw = min(w,y-ls);
		w -= dw;
		res -= c2(w+1);
		if (w)
			ns.insert(pii(cur.first, cur.first + w - 1));
	}
	s = ns;
	ls = y;
}

bool contains (pii a, pii b) {
	if (a.first <= b.first && b.second <= a.second)
		return 1;
	return 0;
}

bool inters (pii a, pii b) {
	if (a.second < b.first || b.second < a.first)
		return 0;
	return 1;
}

pii unt (pii a, pii b) {
	return pii(min(a.first,b.first), max(a.second,b.second));
}

int main() {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		brick c;
		scanf("%d %d", &c.y, &c.x);
		c.x += 1e9;
		c.x -= c.y;
		c.x /= 2;
		mp[c.y].pb(c);
	}
	ls = -1e9+7;

	for (pair<int,vector<brick> > it : mp) {
		int & y = it.first;
		vector<brick> & v = it.second;
		sort(v.begin(), v.end(), [] (brick a, brick b) {
			return a.x < b.x;
		});

		pull(y);
		
		for (brick a : v) {
			pii cur(a.x,a.x);
			auto st = s.lower_bound(cur);
			if (st != s.end()) {
				if (contains(cur,*st))
					continue;
				if (inters(cur,*st)) {
					pii nw = *st;
					s.erase(st);
					cur = unt(cur,nw);
				} else if (cur.second + 1 == st->first) {
					pii nw = *st;
					s.erase(st);
					cur = pii(cur.first, nw.second);
				}
			}
			st = s.lower_bound(cur);
			if (st != s.begin()) {
				--st;
				if (contains(*st,cur))
					continue;
				if (inters(*st,cur)) {
					pii nw = *st;
					s.erase(st);
					cur = unt(nw,cur);
				} else if (st->second + 1 == cur.first) {
					pii nw = *st;
					s.erase(st);
					cur = pii(nw.first, cur.second);
				}
			}
			s.insert(cur);
		}
	}

	pull(2e9+7);

	printf("%lld\n", res);
}
