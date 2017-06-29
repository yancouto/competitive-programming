#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 6e5+3;

map<ll, multiset<ll> > mp;
ll ac;
ll rs[N], a[N], v[N];
ll l, r;
int n;

inline ll sgn (ll x) {
	return (x > 0) - (x < 0);
}

int main () {
	cin >> n >> l >> r;

	for (int i = 0; i < n; i++) {
		cin >> v[i];
		ac += v[i];
		if (l <= i+1 && i+1 <= r)
			rs[i] = sgn(ac);
		else
			rs[i] = -n-n;
		a[i] = ac;
		if (i - l >= 0)
			mp[rs[i-l]].insert(a[i-l]);

		auto it = mp.rbegin();
		int k = 3;
		while (k && it != mp.rend()) {
			if (it->first == -n-n) break;
			rs[i] = max(rs[i], it->first + sgn(ac - *(it->second.begin())));
			++it; k--;
		}

		if (i - r >= 0) {
			mp[rs[i-r]].erase(mp[rs[i-r]].find(a[i-r]));
			if (mp[rs[i-r]].empty())
				mp.erase(rs[i-r]);
		}
	}

	if (rs[n-1] == -n-n)
		cout << "Impossible" << endl;
	else
		cout << rs[n-1] << endl;
}
